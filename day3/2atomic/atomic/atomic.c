#include <linux/module.h>
#include <linux/kernel.h>


#include <linux/kthread.h> // therad 
#include <linux/delay.h>   // sleep 
//#include <linux/sched.h>               //task_struct
 
atomic_t my_global_variable = ATOMIC_INIT(0); // creating atomic variable

MODULE_AUTHOR("abcd");
MODULE_LICENSE("GPL");

static struct task_struct *char_thread;
static struct task_struct *char_thread1;

int mydata =0;
int my_thread_fun(void *p);



int my_thread_fun(void *p)
{
	while(!kthread_should_stop())   //bool kthread_should_stop(void);
	{
	
		printk(KERN_INFO "*****************ATOMIC OPERATORS ON INTEGERS *************");		
		//Atomically add one to v
		atomic_inc(&my_global_variable); // single operation ; no much overhead 
		printk(KERN_INFO "my_thread_fun after inc  %lu\n", atomic_read(&my_global_variable));
		
			
		//atomic_read(&my_global_variable)
		atomic_add(14, &my_global_variable);
		printk(KERN_INFO "my_thread_fun after add   %lu\n", atomic_read(&my_global_variable));

		//Atomically subtract i from v
		atomic_sub(2,&my_global_variable);
		printk(KERN_INFO "my_thread_fun after sub   %lu\n", atomic_read(&my_global_variable));

		//Atomically subtract one from v
		atomic_dec(&my_global_variable);
		printk(KERN_INFO "my_thread_fun after dec   %lu\n", atomic_read(&my_global_variable));
		
		//Atomically set v equal to i
		atomic_set(&my_global_variable, 14);			
		printk(KERN_INFO "my_thread_fun after set    %lu\n", atomic_read(&my_global_variable));
		
		// Function Atomically subtract i from v and return true if the result is zero; otherwise false 
		int res = atomic_sub_and_test(3, &my_global_variable);
		printk(KERN_INFO "my_thread_fun after sub and test    %lu\n", res);

		// Function Atomically dec one from v and return true(1) if the result is zero; otherwise false (0)
		res = atomic_dec_and_test(&my_global_variable);
		printk(KERN_INFO "my_thread_fun after dec and test    %lu\n", res);
		printk(KERN_INFO "my_thread_fun after dec and test    %lu\n", atomic_read(&my_global_variable));
			
		//Atomically add i to v and return true if the result is negative; otherwise false
		res = atomic_add_negative(8,&my_global_variable);
		printk(KERN_INFO "my_thread_fun after add neg    %lu\n", res);
		printk(KERN_INFO "my_thread_fun after add neg     %lu\n", atomic_read(&my_global_variable));

		//Atomically increment v by one and return true if the result is zero; false otherwise
		res = atomic_inc_and_test(&my_global_variable);
		printk(KERN_INFO "my_thread_fun after inc and test     %lu\n", res);
		printk(KERN_INFO "my_thread_fun after inc and test      %lu\n", atomic_read(&my_global_variable));
		
		//This function atomically adds the value to the atomic variable and returns the value.
		printk(KERN_INFO "my_thread_fun after add and return     %lu\n", atomic_add_return(6, &my_global_variable));
		printk(KERN_INFO "my_thread_fun after add and return       %lu\n", atomic_read(&my_global_variable));
		
		//This function atomically adds value to the atomic variable unless the number is a given value. atomic_add_unless (atomic_t *v, int a, int u);

		res = atomic_add_unless (&my_global_variable, 5, 20);
		printk(KERN_INFO "my_thread_fun after atomic_add_unless    %lu\n", res);
		printk(KERN_INFO "my_thread_fun after atomic_add_unless      %lu\n", atomic_read(&my_global_variable));
		//It returns non-zero if v was not u, and zero otherwise.
		
		//if both are same it return 0 and wont add the number
		//if both are not same it return 1 and add the number

		printk(KERN_INFO "*****************ATOMIC BIT WSIE OPERATORS *************");
		
		unsigned long word = 0;

		set_bit(0, &word);       /* bit zero is now set (atomically) */
		printk(KERN_INFO "SET BIT      %x\n", word);

		set_bit(1, &word);        /* bit one is now set (atomically) */
		printk(KERN_INFO "SET BIT      %x\n", word);

		set_bit(2, &word);        /* bit two is now set (atomically) */
		printk(KERN_INFO "SET BIT      %x\n", word);

		clear_bit(1, &word);     /* bit one is now unset (atomically) */
		printk(KERN_INFO "CLEAR BIT      %x\n", word);

		change_bit(0, &word);    /* bit zero is flipped; now it is unset (atomically) */
		printk(KERN_INFO "CHANGE BIT      %x\n", word);

		//Atomically set the nr-th bit starting from addr and return the previous value
		res = test_and_set_bit(1, &word);
		printk(KERN_INFO "TEST AND SET    %lu\n", res);
		printk(KERN_INFO "TEST AND SET      %x\n", word);

		//Atomically clear the nr-th bit starting from addr and return the previous value
		res = test_and_clear_bit(1,&word);
		printk(KERN_INFO "TEST AND CLEAR    %lu\n", res);
		printk(KERN_INFO "TEST AND CLEAR      %x\n", word);
		
		
		//Atomically flip the nr-th bit starting from addr and return the previous value
		res=test_and_change_bit(0,&word);
		printk(KERN_INFO "TEST AND CHANGE    %lu\n", res);
		printk(KERN_INFO "TEST AND CHANGE    %x\n", word);
		
		//Atomically returns the bit-number of the first zero bit, not the number of the byte containing a bit
		res=find_first_zero_bit(&word,8);
		printk(KERN_INFO "find_first_zero_bit    %lu\n", res);
		printk(KERN_INFO "find_first_zero_bit    %x\n", word);
		
		//Atomically returns the bit-number of the first set bit, not the number of the byte containing a bit.     int find_first_bit(unsigned long *addr, unsigned int size)
		res=find_first_bit(&word,8);
		printk(KERN_INFO "find_first_bit    %lu\n", res);
		printk(KERN_INFO "find_first_bit    %x\n", word);
		
		
		
		//Atomically return the value of the nr-th bit starting from addr
		res = test_bit(2,&word);
		printk(KERN_INFO "TEST BIT    %lu\n", res);  

		msleep(1000);
		
	}
	return 0;	
}

int my_thread_fun1(void *p)
{
	while(!kthread_should_stop())
	{
		
		atomic_inc(&my_global_variable);
		printk(KERN_INFO "my_thread_fun2  %lu\n", atomic_read(&my_global_variable));
		
		msleep(1000);
	}
	return 0;
}


static int __init my_simpledriver_init(void)
{
	printk(KERN_INFO"My sample driver start");

	
	char_thread = kthread_run(my_thread_fun,NULL,"my char thread");
	if(char_thread)
	{
		printk(KERN_INFO" create the thread");
	}
	else 
	{
		printk(KERN_INFO"unable to create the thread");
		
	}
#if 0     //  they are effectively commenting out the code so it will never be compiled.
	char_thread1 = kthread_run(my_thread_fun1,NULL,"my char thread1");
	if(char_thread1)
	{
		printk(KERN_INFO" create the thread1");
	}
	else 
	{
		printk(KERN_INFO"unable to create the thread");
		
	}
#endif
	return 0;

}


static void __exit my_simpledriver_exit(void)
{
	printk(KERN_INFO"My samle driver exit\n");

	kthread_stop(char_thread);
	//kthread_stop(char_thread1);

}
module_init(my_simpledriver_init);
module_exit(my_simpledriver_exit);
