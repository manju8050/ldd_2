#include <linux/module.h>
#include <linux/kthread.h>	//thread
#include <linux/kernel.h> 

#include <linux/delay.h> 


MODULE_AUTHOR("abcd");
MODULE_LICENSE("GPL");

static struct task_struct *char_thread;
static struct task_struct *char_thread1;

//int mydata=0;

int my_thread_fun(void *p);
int my_thread_fun(void *p)
{
	while(!kthread_should_stop())        //bool kthread_should_stop(void);
	{
	printk(KERN_INFO"my thread 1 is started");
	msleep(1000);
	}
	return 0;
}

int my_thread_fun1(void *p);
int my_thread_fun1(void *p)
{
	while(!kthread_should_stop())       //bool kthread_should_stop(void);
	{
	printk(KERN_INFO"my thread 2 is started");
	msleep(1000);
	}
	return 0;
}


static int __init my_simpledriver_init(void)
{

	printk(KERN_INFO"my sample driver start");
	
	char_thread = kthread_run(my_thread_fun,NULL,"my char thread");
	
	/*Upon successful completion, kthread_create() returns 0.  Otherwise, the following error values are returned:

     [EAGAIN]  The limit on the total number of system processes would be exceeded.
*/

	if(char_thread){
		printk(KERN_INFO"kthread created successfully\n");
		//wake_up_process(char_thread);
	}
	else{
		printk(KERN_INFO"COuldnt create thread\n");
	}
	
	char_thread1 = kthread_run(my_thread_fun1,NULL,"my char thread 1");
	if(char_thread1){
		printk(KERN_INFO"kthread created successfully\n");
		//wake_up_process(char_thread);
	}
	else{
		printk(KERN_INFO"COuldnt create thread\n");
	}
	
	return 0;

}

module_init(my_simpledriver_init);

static void  __exit my_simpledriver_exit(void){

	printk(KERN_INFO"my sample driver exit");
	kthread_stop(char_thread);
	kthread_stop(char_thread1);

}

module_exit(my_simpledriver_exit);
