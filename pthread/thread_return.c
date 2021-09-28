#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *my_thread(void *ptr)
{
	int *n=(int*)ptr;
	int data=*n;
	for(int i=0;i<data;i++)
	printf("val:%d\n",i);
	pthread_exit(NULL);
	return (void*)20;
}

int main()
{
	pthread_t tid;
	int ret,var;
	void *rval;
	printf("enter the limit");
	scanf("%d",&var);
	ret=pthread_create(&tid,NULL,&my_thread,&var);
	if(ret!=0)
	{
		printf("thread is not created\n");
	}
	
	printf("inside the main\n");
	//sleep(10);
	pthread_join(tid,rval);
	printf("back to main :%d\n",*(int*)rval);
	
	
	pthread_exit(NULL);
	
	//return 0;
	
}