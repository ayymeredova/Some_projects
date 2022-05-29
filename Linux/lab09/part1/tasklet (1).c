#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/lockdep.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/unistd.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/sched.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/seq_file.h>
#include<linux/slab.h>
#include<linux/vmalloc.h>

#define SHARED_IRQ 1 

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Kazakova");

static int my_dev_id;
char tasklet_data[] = "tasklet data"; 

void tasklet_handler(unsigned long data);

DECLARE_TASKLET(my_tasklet, tasklet_handler, (unsigned long) &tasklet_data);


static int my_proc_show(struct seq_file *m, void *v)
{
  // pending - выяснить, приостановлен ли эл-т work (еще не обработан обработчиком))
  seq_printf(m, "=== In user mode tasklet: state - %ld, count - %d, data - %s\n",
		my_tasklet.state, my_tasklet.count, my_tasklet.data);
  return 0;
}

static int my_proc_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "=== Called my_proc_open\n");
  return single_open(file, my_proc_show, NULL);
}

static struct file_operations props={
	.open = my_proc_open,
	.release = single_release,
	.read = seq_read,
};

void tasklet_handler(unsigned long data) 
{
	printk(KERN_INFO "Tasklet: state - %ld, count - %d, data - %s\n",
		my_tasklet.state, my_tasklet.count, my_tasklet.data);
}

// Обработчик прерывания
static irqreturn_t my_interrupt(int irq, void *dev_id) 
{
	if (irq == SHARED_IRQ) 
	{
		printk(KERN_INFO "Tasklet scheduled\n"); 
		tasklet_schedule(&my_tasklet); 
		return IRQ_HANDLED;
	} 
	else 
		return IRQ_NONE;
}

static int __init my_tasklet_init(void)
{
  struct proc_dir_entry *entry;
  entry = proc_create("tasklet", S_IRUGO | S_IWUGO, NULL, &props);
  if (!entry)
  {
    printk(KERN_INFO "=== Error: can't create seq file\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "=== Seq file created\n");

	if (request_irq(SHARED_IRQ, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id))
	{
		printk(KERN_ERR "Error on request_irq\n"); 
		return -1;
	}
	printk(KERN_INFO "Module loaded!\n");
	return 0;
}

static void __exit my_tasklet_exit(void) 
{
	tasklet_kill(&my_tasklet);
	free_irq(SHARED_IRQ, &my_dev_id); // Освобождение линии прерывания
	printk(KERN_INFO "Module unloaded!\n");
}

module_init(my_tasklet_init);
module_exit(my_tasklet_exit); 
