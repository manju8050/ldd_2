#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *my_thread(void *ptr)
{
	for(int i=0;i<100;i++)
	printf("val:%d\n",i);
	
}

int main()
{
	pthread_t tid;
	int ret;
	ret=pthread_create(&tid,NULL,&my_thread,NULL);
	if(ret!=0)
	{
		printf("thread is not created\n");
	}
	
	printf("inside the main\n");
	//sleep(10);
	//pthread_join(tid,NULL);
	return 0;
	
}


//gcc pthread.c -lpthread
