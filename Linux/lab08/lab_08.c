#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/time.h>

#include <asm/atomic.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Meredova");

#define MY_VFS_MAGIC_NUM 0x99977766
#define SLAB_NAME "my_vfs_cache"

struct kmem_cache *cache = NULL;
static void **cache_mem_area = NULL;

// Конструктор вызывается при размещении каждого элемента
static void co(void *p)
{
  *(int *)p = (int)p;
  printk(KERN_INFO "+ SLAB CACHE element was created!\n");
}

// для кэширования inode
static struct my_vfs_inode
{
  int i_mode;
  unsigned long i_ino;
} my_vfs_inode;

static struct inode *my_vfs_make_inode(struct super_block *sb, int mode)
{
  // новая структура inode
  struct inode *ret = new_inode(sb);
  if (ret)
  {
    inode_init_owner(ret, NULL, mode);
    ret->i_size = PAGE_SIZE;
    ret->i_atime = ret->i_mtime = ret->i_ctime = current_time(ret);
    ret->i_private = &my_vfs_inode;
  }

  printk(KERN_INFO "+ VFS root inode was created!\n");
  return ret;
}

// деструктор суперблока
static void my_vfs_put_super(struct super_block *sb)
{
  printk(KERN_INFO "+ VFS super block was destroyed!\n");
}

// Операции структуры суперблок
static struct super_operations const my_vfs_sup_ops = {
    .put_super = my_vfs_put_super,
    .statfs = simple_statfs,
    .drop_inode = generic_delete_inode,
};

// инициализация суперблока
static int my_vfs_fill_sb(struct super_block *sb, void *data, int silent)
{
  // инициализировать поля структуры суперблока
  sb->s_blocksize = PAGE_SIZE;
  sb->s_blocksize_bits = PAGE_SHIFT;
  sb->s_magic = MY_VFS_MAGIC_NUM;
  sb->s_op = &my_vfs_sup_ops;

  // создать inode каталога ФС
  struct inode *root_inode = my_vfs_make_inode(sb, S_IFDIR | 0755); // mode, который задает разрешения на создаваемый файл и его тип (маска S_IFDIR говорит функции, что мы создаем каталог
  if (!root_inode)
  {
    printk(KERN_ERR "+ ERROR: Failed to create inode for VFS root!\n");
    return -ENOMEM;
  }

  // файловые и inode-операции определенные над созданным inode-ом
  // рпедоставляются ядром
  root_inode->i_op = &simple_dir_inode_operations;
  root_inode->i_fop = &simple_dir_operations;

  // cоздаем dentry для представления корневого каталога ФС в ядре
  // __d_alloc (аллоцирует дентри в дентри кеше?)
  //      dentry = kmem_cache_alloc(dentry_cache, GFP_KERNEL);
  // d_instantiate -> __d_set_inode_and_type
  //      dentry->d_inode = inode;
  sb->s_root = d_make_root(root_inode);
  if (!sb->s_root)
  {
    printk(KERN_ERR "+ ERROR: Failed to create VFS root!\n");
    iput(root_inode);
    return -ENOMEM;
  }
  else
    printk(KERN_INFO "+ VFS root dentry was created!\n");

  printk(KERN_INFO "+ VFS superblock was initialized!\n");
  return 0;
}

// вызывается при монтировании ФС:
// должна вернуть структуру, описывающую корневой каталог ФС
static struct dentry *my_vfs_mount(struct file_system_type *type, int flags, const char *dev, void *data)
{
  // создается виртуальная ФС, несвязанная с устройстовом
  // my_vfs_fill_sb - указатель на функцию, которая будет вызвана из mount_nodev
  // чтобы проинициализировать суперблок
  struct dentry *const root_dentry = mount_nodev(type, flags, data, my_vfs_fill_sb);

  if (IS_ERR(root_dentry))
    printk(KERN_ERR "+ ERROR: Failed mounting VFS!\n");
  else
    printk(KERN_INFO "+ VFS was mounted!\n");

  // вернуть корневой каталог
  return root_dentry;
}

// Описание создаваемой ФС
static struct file_system_type my_vfs_type = {
    .owner = THIS_MODULE,         // счетчик ссылок на модуль чтобы модуль
                                  // нельзя было случайно выгрузить
                                  // (если выгрузить модуль, пока система подмонтирована, будет ошибка)
    .name = "my_vfs",             // название файловой системы
    .mount = my_vfs_mount,        // вызывается при монтировании ФС
    .kill_sb = kill_litter_super, // вызывается при размонтировании ФС
};

// Инициализация модуля
static int __init my_vfs_md_init(void)
{
  // Регистрация файловой ситемы
  int ret = register_filesystem(&my_vfs_type);
  if (ret != 0)
  {
    printk(KERN_ERR "+ ERROR: Failed to register VFS!\n");
    return ret;
  }

  // Выделение непр области в физической памяти
  cache_mem_area = (void **)kmalloc(sizeof(void *), GFP_KERNEL);
  if (!cache_mem_area)
  {
    printk(KERN_ERR "+ ERROR: Failed to allocated memory in init!\n");
    kfree(cache_mem_area);
    return -ENOMEM;
  }

  // создание слаб кеша
  cache = kmem_cache_create(SLAB_NAME, sizeof(void *), 0, SLAB_HWCACHE_ALIGN, co);
  if (!cache)
  {
    printk(KERN_ERR "+ ERROR: Failed to create cache!\n");
    kmem_cache_destroy(cache);
    kfree(cache_mem_area);
    return -ENOMEM;
  }

  // тк циклы запрещены создадим один объект
  if (NULL == ((*cache_mem_area) = kmem_cache_alloc(cache, GFP_KERNEL)))
  {
    printk(KERN_ERR "+ ERROR: Failed to alloc cache cell!\n");
    kmem_cache_free(cache, *cache_mem_area);
    kmem_cache_destroy(cache);
    kfree(cache_mem_area);
    return -ENOMEM;
  }

  printk(KERN_INFO "+ VFS MODULE was loaded!\n");
  return 0;
}

static void __exit my_vfs_md_exit(void)
{
  kmem_cache_free(cache, *cache_mem_area);
  kmem_cache_destroy(cache);
  kfree(cache_mem_area);

  if (unregister_filesystem(&my_vfs_type) != 0)
  {
    printk(KERN_ERR "+ ERROR: Failed to unregister VFS!\n");
  }

  printk(KERN_INFO "+ VFS MODULE was unloaded!\n");
}

module_init(my_vfs_md_init);
module_exit(my_vfs_md_exit);