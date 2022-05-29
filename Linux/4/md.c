#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>
#include<linux/slab.h>
#include<linux/vmalloc.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fortune Cookie Kernel Module");

#define COOKIE_BUF_SIZE PAGE_SIZE
#define TEMP_BUF_SIZE 256


ssize_t fortune_read(struct file *file, char *buf, size_t count, loff_t *f_pos);
ssize_t fortune_write(struct file *file, const char *buf, size_t count, loff_t *f_pos);
int fortune_release(struct inode *node, struct file *file);
int fortune_open(struct inode *node, struct file *file);

int fortune_init(void);
void fortune_exit(void);

static const struct proc_ops pops = {
    .proc_read = fortune_read,
    .proc_write = fortune_write,
    .proc_release = fortune_release, 
    .proc_open = fortune_open,
};

static char *cookie_buf;
static struct proc_dir_entry *proc_entry;
static unsigned read_index;
static unsigned write_index;

char temp[TEMP_BUF_SIZE];

struct task_struct *task = &init_task;

int len, t_len;


int fortune_init(void)
{
    cookie_buf = (char *) vmalloc(COOKIE_BUF_SIZE);
    if (!cookie_buf)
    {
        printk(KERN_INFO "not enough memory\n");
        return -ENOMEM;
    }
    memset(cookie_buf, 0, COOKIE_BUF_SIZE);
    proc_entry = proc_create("fortune", 0666, NULL, &pops);
    if (!proc_entry)
    {
        vfree(cookie_buf);
        printk(KERN_INFO "Couldn't create proc entry\n");
        return -ENOMEM;
    }
    read_index = 0;
    write_index = 0;
    proc_mkdir("my_dir_fortune", NULL);
    proc_symlink("my_symbolic_fortune", NULL, "/proc/fortune");
    printk(KERN_INFO "fortune module loaded.\n");
    return 0;
}


ssize_t fortune_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
    if (*f_pos > 0 || write_index == 0)
        return 0;

    if (read_index >= write_index)
        read_index = 0;
    
    len = sprintf(buf, "%s\n", &cookie_buf[read_index]);
    read_index += len;
    *f_pos += len;

    printk(KERN_INFO "proc called read \n");
    return len;
}


int fortune_release(struct inode *node, struct file *file)
{
    printk(KERN_INFO "proc called release \n");
    return 0;
}


int fortune_open(struct inode *node, struct file *file)
{
    printk(KERN_INFO "proc called open \n");
    return 0;
}


ssize_t fortune_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
    int space_available = (COOKIE_BUF_SIZE - write_index) + 1;

    if (count > space_available)
    {
        printk(KERN_INFO "+_+ buf is full\n");
        return -ENOSPC;
    }

    if (copy_from_user(&cookie_buf[write_index], buf, count))
        return -EFAULT;

    write_index += count;
    cookie_buf[write_index - 1] = 0;
    printk(KERN_INFO "proc called write \n");
    return count;
}


void fortune_exit(void)
{
    remove_proc_entry("fortune", NULL);

    if (cookie_buf)
        vfree(cookie_buf);

    printk(KERN_INFO "fortune module unloaded.\n");
}

module_init(fortune_init);
module_exit(fortune_exit);