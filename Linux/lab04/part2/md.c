#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lab 4 Cookie Kernel Module");
MODULE_AUTHOR("Meredova Ayjahan");

#define MAX_COOKIE_LENGTH PAGE_SIZE

static struct proc_dir_entry *proc_entry;
static char *data; // Space for fortune strings
static int write_index; // Index to write next fortune
static int next_index; // Index to read next fortune

ssize_t proc_write(struct file *file, const char __user *buf,
                             size_t len, loff_t *ppos)
{
    int space_available = (MAX_COOKIE_LENGTH - write_index) + 1;
    if (len > space_available)
    {
        printk(KERN_INFO "Lab 4: cookie pot is full!\n");
        return -ENOSPC;
    }
    if (copy_from_user(&data[write_index], buf, len))
    {
        return -EFAULT;
    }
    write_index += len;
    data[write_index-1] = 0;
    printk(KERN_INFO "Lab 4: call proc_write");
    seq_write(file, )

    return len;
}

int proc_show(struct seq_file *f, void *v)
{
    if (next_index >= write_index)
        next_index = 0;

    seq_printf(f, "%s\n", &data[next_index]);
    printk(KERN_INFO "Lab 4: call proc_show");


    int l = strlen(&data[next_index]) + 1;
    next_index += l;

    return 0;
}

int	proc_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Lab 4: call proc_open");
    return single_open(file, proc_show, NULL);
}

int	proc_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Lab 4: call proc_release");
    return single_release(inode, file);
}

ssize_t proc_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
    printk(KERN_INFO "Lab 4: call proc_read");
    return seq_read(file, buf, len, ppos);
}


struct proc_ops proc_fops = {
    // .owner = THIS_MODULE,
    .proc_open = proc_open,
    .proc_release = proc_release,
    .proc_read = proc_read,
    .proc_write = proc_write,
};

int proc_init(void)
{
    int ret = 0;
    data = (char *)vmalloc(MAX_COOKIE_LENGTH);
    if (!data)
    {
        ret = -ENOMEM;
    }
    else
    {
        memset(data, 0, MAX_COOKIE_LENGTH);

        proc_entry = proc_create("fortune", 0666, NULL, &proc_fops);
        if (proc_entry == NULL)
        {
            ret = -ENOMEM;
            vfree(data);
            printk(KERN_INFO "Lab 4: Couldn't create proc entry\n");
        }
        else
        {
            write_index = 0;
            next_index = 0;
            printk(KERN_INFO "Lab 4: Module loaded.\n");
        }
    }
    return ret;
}

void proc_exit(void)
{
    proc_remove(proc_entry);
    vfree(data);
    printk(KERN_INFO "Lab 4: Module unloaded.\n\n\n");
}

module_init(proc_init);
module_exit(proc_exit);

// https://developer.ibm.com/articles/l-proc/
// https://www.admin-magazine.com/layout/set/print/Archive/2014/23/Kernel-and-driver-development-for-the-Linux-kernel