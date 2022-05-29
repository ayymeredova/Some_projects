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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kazakova");

#define IRQ_NUM 1
#define IRQ_NAME "keyboard"
#define WQ_NAME "keyboard_wq"
#define ITER_COUNT 1000000

// Структура, описывающая очередь работ
static struct workqueue_struct *my_wq;

typedef struct
{
  struct work_struct work;
  int work_num; // номер работы
} my_work_t;

// Структуры, описывающие две работы
// (обработчики нижней половины прерывания в очереди работ)
static my_work_t *work_1;
static my_work_t *work_2;

// Разделяемая переменная
static int shared_counter = 0;

// Mutex
struct mutex my_mutex;


static int my_proc_show(struct seq_file *m, void *v)
{
  // pending - выяснить, приостановлен ли эл-т work (еще не обработан обработчиком))
  seq_printf(m, "=== In user mode: is work_1 pending - %d, is work_2 pending - %d, shared counter - %d\n",
             work_pending(&(work_1->work)), work_pending(&(work_2->work)), shared_counter);

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

void my_bottom_half(struct work_struct *work)
{
	// блокирует объект мьютекса, на который ссылается my_mutex
  mutex_lock(&my_mutex);
  printk(KERN_INFO "=== MUTEX LOCKED ===\n");

  my_work_t *my_work = (my_work_t *)work;

  // какая работа вошла в критческую секцию?
  printk(KERN_INFO "=== worker_%d, status = %d\n", my_work->work_num, work_pending(&(my_work->work)));

  // другая работа заблокированав это время?
  if (my_work->work_num == 1) //
    printk(KERN_INFO "=== work_2, status = %d\n", work_pending(&(work_2->work)));
  else
    printk(KERN_INFO "=== work_1, status = %d\n", work_pending(&(work_1->work)));

  int sum = 0, i = 0;
  for (; i < ITER_COUNT; i++)
    sum += i;
  shared_counter++;
  
  printk(KERN_INFO "Sum: %d\n", sum);

  printk(KERN_INFO "Workqueue: counter %d\n", ++shared_counter);

  mutex_unlock(&my_mutex);
  printk(KERN_INFO "=== MUTEX UNLOCKED ===\n");
  
  printk(KERN_INFO "=== AFTER UNLOCK ===: worker_%d, status = %d\n", my_work->work_num, work_pending(&(my_work->work)));
}

// в верхней половине выполняется
// динамическая инициализация и поставновка работ в очередь работ
irqreturn_t my_irq_handler(int irq_num, void *dev_id)
{
	// Проверка, что произошло именно нужное 1-е прерывание
  if (irq_num == IRQ_NUM)
  {
    if (work_1)
	 // Помещаем задачу в очередь работ (назначает работу текущему процессору)
      queue_work(my_wq, (struct work_struct *)work_1);
    if (work_2)
      queue_work(my_wq, (struct work_struct *)work_2);

    return IRQ_HANDLED; // прерывание обработано
  }
  return IRQ_NONE; // прерывание не обработано
}

static int __init my_module_init(void)
{
  struct proc_dir_entry *entry;
  entry = proc_create("wqueue", S_IRUGO | S_IWUGO, NULL, &props);
  if (!entry)
  {
    printk(KERN_INFO "=== Error: can't create seq file\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "=== Seq file created\n");

  // номер irq
  // указ-ль на наш обработчик прерывания
  // флаг разделение(совместное использование) линии IRQ с другими устройствами
  // имя устройства, связ. с прерыванием
  // идентификатор устройства, нужен для для разделения линии прер-я, отключения с линии прерваний с помощью free_irq
  // === регистрация обработчика прерывания ===
  if (request_irq(IRQ_NUM, my_irq_handler, IRQF_SHARED, IRQ_NAME, my_irq_handler))
  {
    printk(KERN_ERR "=== **ERROR** Failed to register IRQ handler\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "=== IRQ handler registered\n");

  // kmalloc() — выделение в ядре участков памяти размером в заданное количество байтов
  work_1 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
  work_2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);

  if (work_1)
  {
    // Инициализация структуры work12 (динамическое задание work_struct)
	// func – функция, которая вызывается из workqueue – обработчик нижней половины
    INIT_WORK((struct work_struct *)work_1, my_bottom_half);
    work_1->work_num = 1;
  }
  else
  {
    printk(KERN_ERR "=== **ERROR** Failed kalloc\n");
    return -ENOMEM;
  }

  if (work_2)
  {
    INIT_WORK((struct work_struct *)work_2, my_bottom_half);
    work_2->work_num = 2;
  }
  else
  {
    printk(KERN_ERR "=== **ERROR** Failed kalloc\n");
  }

	// ==== Cоздание очереди работ ====
  // Флаг UNBOUND - по умолчанию - непривязанная к конкретному процессору очередь
  // внутри вызов alloc_workqueue(name, flags, max_active)
  // name - имя очереди, flags - флаги определяют как очередь работ будет выполняться
  // max_active - ограничивает число задач из данной очереди, которые могут одновременно выполняться на одном CPU.
  my_wq = create_workqueue(WQ_NAME);
  if (!my_wq)
  {
    free_irq(IRQ_NUM, my_irq_handler);
    printk(KERN_ERR "=== **ERROR** Failed to create work queue\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "=== Workqueue created\n");
  mutex_init(&my_mutex);

  printk(KERN_INFO "=== Module loaded!\n");
  return 0;
}

// Выход загружаемого модуля
static void __exit my_module_exit(void)
{
  // Освобождение линии прерывания
  free_irq(IRQ_NUM, my_irq_handler);

  // Удаление очереди работ
  flush_workqueue(my_wq); // Все работы в данной очереди работ принудительно завершены
  destroy_workqueue(my_wq); // удаление очереди работ
  mutex_destroy(&my_mutex);

  if (work_1)
    kfree(work_1);

  if (work_2)
    kfree(work_2);

  remove_proc_entry("wqueue", NULL);
  printk(KERN_INFO "=== Module unloaded!\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
