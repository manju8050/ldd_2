#include <linux/module.h> 
#include <linux/kthread.h>	//thread
//#include <linux/kernel.h> 

#include <linux/delay.h> 


MODULE_AUTHOR("abcd");
MODULE_LICENSE("GPL");

static struct task_struct *char_thread; 
static struct task_struct *char_thread1;

/*
struct task_struct {
	u64 curr_chain_key;
	int lockdep_depth;
	unsigned int lockdep_recursion;
	struct held_lock held_locks[MAX_LOCK_DEPTH];
	gfp_t lockdep_reclaim_gfp;
	int pid;
	int state;
	char comm[17];
};
*/
//int mydata=0;

int my_thread_fun(void *p);
int my_thread_fun(void *p)
{
	while(!kthread_should_stop())        //bool kthread_should_stop(void); Similar to kthread_should_stop(), but this keeps the thread alive and in a park position.
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
	
	//printk("%d",get_pid(void));
	
	char_thread = kthread_run(my_thread_fun,NULL,"my char thread");
	
	/*Upon successful completion, kthread_create() returns char (task_struct).  Otherwise, the following error values are returned:

     [EAGAIN]  The limit on the total number of system processes would be exceeded.
*/

	if(char_thread){
	
		printk("%d",char_thread->pid);
		printk("%u",char_thread->flags);
		printk("%ld",char_thread->state);   //0 runnable
		/* -1 unrunnable, 0 runnable, >0 stopped: */
		
		/*
		root        8679       2  0 17:57 ?        00:00:00 [my char thread]
root        8680       2  0 17:57 ?        00:00:00 [my char thread ]
manju       8682    3798  0 17:57 pts/0    00:00:00 ps -Af
*/
		printk(KERN_INFO"kthread created successfully\n");
		//wake_up_process(char_thread);
	}
	else{
		printk(KERN_INFO"COuldnt create thread\n");
	}
	
	char_thread1 = kthread_run(my_thread_fun1,NULL,"my char thread 1");   // same name in thread 1 and 2
	if(char_thread1){
		printk("%d",char_thread1->pid);
		printk("%u",char_thread1->flags);
		printk("%ld",char_thread1->state);  //0 runnable
		
		
		
		printk(KERN_INFO"thread 1 Flags:%ld",char_thread1->thread_info.flags);
		printk(KERN_INFO"thread 1 status:%d",char_thread1->thread_info.status);
		
		
		printk(KERN_INFO"kthread created successfully\n");
		//wake_up_process(char_thread);
	}
	else
	{	
		
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
