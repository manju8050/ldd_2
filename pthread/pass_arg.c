#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
struct scl
{
	int boys;
	char girls;
};
int arr[5];	
pthread_t tid;

void* add_num(void *ptr)
{    
       
	 struct scl *data_ptr = (struct scl*)ptr;//type casting the pointer to structure data type
	 printf("boys=%d,girl=%c",data_ptr->boys,data_ptr->girls);
	 
	/*for(int i=0;i<5;i++)
       {
       //int *data_ptr = (int*)ptr;//here the base adress of array is passed 
       printf("\n%d\n",*data_ptr);
       *data_ptr++;
       }*/
   
    
	
 }

int main()
{
    int data, ret=0;
   
    struct scl var;
   // printf("\n Enter a number:: ");
    //scanf("%d",&data);
    //printf("enter values\n");
    //for(int i=0;i<5;i++) 
    //scanf("%d",&arr[i]);
    printf("\n Enter a boy and girl:: ");
    scanf("%d %c",&var.boys,&var.girls);
    ret = pthread_create(&tid,0,&add_num,&var);
   // ret = pthread_create(&tid,0,&add_num,&arr);
    if (ret) {
            printf("ERORR; return code from pthread_create() is %d\n", ret);
            return -1;
    }
    //sleep(2);
    printf("in main");
    pthread_join(tid,NULL);
     //pthread_exit(NULL);
    return 0;
}



/*EOC*/
