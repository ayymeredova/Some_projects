#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>
#include<linux/slab.h>
#include<linux/vmalloc.h>

MODULE_LICENSE("GPL");
static char *str = NULL;

unsigned int write_index;
unsigned int read_index;
 
#define COOKIE_POT_SIZE PAGE_SIZE  

static struct proc_dir_entry *proc_entry, *proc_dir, *proc_sym;

ssize_t my_write(struct file* file, const char __user *buffer, size_t count, loff_t *f_pos);
int my_release(struct inode *node, struct file *file);
int my_open(struct inode *inode, struct file *file);

static const struct proc_ops pops = {
    .proc_read = seq_read,
    .proc_write = my_write,
    .proc_release = my_release, 
    .proc_open = my_open,
};


static int __init fortune_init(void)
{
	printk(KERN_INFO "fortune init\n");
	write_index = 0;
	read_index = 0;
    str = vmalloc(COOKIE_POT_SIZE);
    if (!str)
    {
        printk(KERN_INFO "Error: can't malloc cookie buffer\n");
        return -ENOMEM;
    }
    memset(str, 0, COOKIE_POT_SIZE); 
	proc_entry = proc_create("fortune", S_IRUGO | S_IWUGO, NULL, &pops); 
	if(!proc_entry)
	{
		vfree(str);
		printk(KERN_INFO "Error: can't create fortune file\n");
        return -ENOMEM;
	}	
    proc_dir = proc_mkdir("fortune_dir", NULL);
    if(!proc_dir)
	{
		vfree(str);
		printk(KERN_INFO "Error: can't create fortune file\n");
        return -ENOMEM;
	}	
    proc_sym = proc_symlink("fortune_symlink", NULL, "/proc/fortune");  
    if(!proc_sym)
	{
		vfree(str);
		printk(KERN_INFO "Error: can't create fortune file\n");
        return -ENOMEM;
	}	
	printk(KERN_INFO "fortune: Fortune module loaded successfully\n");
	return 0;
}

 
static int my_show(struct seq_file *m, void *v)
{
	printk(KERN_INFO "fortune called my_show\n");
	seq_printf(m, "%s", str + read_index); // seq_printf = sprintf = copy_to_user
	int len = strlen(str + read_index);
	if (len)
		read_index += len + 1;
	return 0;
}


ssize_t my_write(struct file* file, const char __user *buffer, size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "fortune called my_write\n");
	if (copy_from_user(&str[write_index], buffer, count)) // (куда, откуда, сколько байт)
        return -EFAULT; 
    write_index += count;
    str[write_index-1] = 0;
    return count;
}

 
int my_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "fortune called my_open\n");
	return single_open(file, my_show, NULL);  
}
 
 
int my_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "fortune called my_release\n");
	return single_release(inode, file);  
}

 
static void __exit fortune_exit(void)
{
	printk(KERN_INFO "fortune exit\n");
    if (proc_entry)
	    remove_proc_entry("fortune", NULL);
    if (proc_dir)
	    remove_proc_entry("fortune_dir", NULL);
    if (proc_sym)
	    remove_proc_entry("fortune_symlink", NULL);
    if (str)
        vfree(str);
    printk(KERN_INFO "fortune: Fortune module unloaded\n"); 
}
 
module_init(fortune_init);
module_exit(fortune_exit);
 
 
