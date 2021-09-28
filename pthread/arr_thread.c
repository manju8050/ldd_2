#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *my_thread(void *ptr)
{
	int *n=(int*)ptr;
	for(int i=0;i<5;i++)
	{
		printf("%d\n",*n);
		*n++;
	}
	
}

int main()
{
	pthread_t tid;
	int ret;
	int arr[]={1,2,3,4,5};
	
	ret=pthread_create(&tid,NULL,&my_thread,&arr);
	if(ret!=0)
	{
		printf("thread is not created\n");
	}
	
	printf("inside the main\n");
	//sleep(10);
	pthread_join(tid,NULL);
	return 0;
	
}


//gcc pthread.c -lpthread
