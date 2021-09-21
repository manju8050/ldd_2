#include <stdio.h>
#include <unistd.h>  //standard symbol constant and types -getpid
#include <fcntl.h>   // it is use for file control operation
#include <string.h>
#include <stdlib.h>   //for exit function
#include <sys/types.h>   //we need it for open system call
#include<sys/ioctl.h>   //ioctl functions
#include <errno.h>
extern int errno;
#define MY_MAGIC 'a'
#define WR_VALUE _IOW(MY_MAGIC,'a',int32_t*)
#define RD_VALUE _IOR(MY_MAGIC,'b',int32_t*)
#define MY_IOCTL_MAX_CMD 2

int main()
{
	int fd;
    int32_t value, number;	
	
	printf("[%d] - Opening device my_cdrv\n", getpid() );
	
	fd = open( "/dev/my_Ioctl_driv", O_RDWR );
	if( fd < 0 ) 
	{
		
		int er = errno;
		printf("error number is :%d\n",er);
		printf("\n\nDevice could not be opened\n\n");
		perror("Error is ");
		
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);
	
	   
	printf("Enter the Value to send\n");
	scanf("%d",&number);
	printf("Writing Value to Driver\n");
	ioctl(fd, WR_VALUE, (int32_t*) &number); 

	printf("Reading Value from Driver\n");
	ioctl(fd, RD_VALUE, (int32_t*) &value);
	printf("Value is %d\n", value);

	printf("Closing Driver\n");
	close(fd);
	
	
	
	exit(0);
}


