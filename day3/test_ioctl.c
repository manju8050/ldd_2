#include <stdio.h>   //printf scanf
#include <unistd.h>   // standard symbol constant and types -getpid
#include <fcntl.h>   // it is use for file control operation //open

#include <stdlib.h>   //for exit function
#include <sys/types.h>  //open close
#include<sys/ioctl.h>   // ioctl
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
	
	fd = open( "/dev/my_Ioctl_driver", O_RDWR );  //return the new file descriptor (a nonnegative integer).  On error, -1 is returned
		
	
	
	if( fd < 0 ) 
	{
		if(errno==EFAULT)
		{
			printf("error number is -%d\n",EFAULT);
			printf("Error is EFAULT");
			printf("\n\nDevice could not be opened\n\n");
			perror("Error is ");
			return -EFAULT;
			
			/*
			fd = open( NULL, O_RDWR ); //null address
			error number is -14
			Error is EFAULT
			Device could not be opened
			Error is : Bad address

			*/	
		}
		if(errno==ENOENT)
		{
			printf("error number is -%d\n",ENOENT);
			printf("Error is ENOENT");
			printf("\n\nDevice could not be opened\n\n");
			perror("Error is ");
			return -ENOENT;
			/*
			fd = open( "/dev/my_Ioctl_driv", O_RDWR );  // wrong address // file with read only permission
			fd = open( "", O_RDWR );   // no file
			error number is -2
			Error is ENOENT
			Device could not be opened
			Error is : No such file or directory
			*/
			
		}
		if(errno==EISDIR)
		{
			printf("error number is -%d\n",EISDIR);
			printf("Error is EISDIR");
			printf("\n\nDevice could not be opened\n\n");
			perror("Error is ");
			return -EISDIR;
			
			/*
			fd = open( "/dev", O_RDWR );
			error number is -21
			Error is EISDIR
			Device could not be opened
			Error is : Is a directory
			*/	
		}
		
		//int er = errno;  printf("%d\n",er); perror("Error\n");
		
		
		printf("\n\nDevice could not be opened\n\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);
	
	   
	printf("Enter the Value to send\n");
	scanf("%d",&number);
	printf("Writing Value to Driver\n");
	
	int wr=ioctl(fd, WR_VALUE, (int32_t*) &number);  //return a nonnegative value on success.  On error, -1 is returned, 
	
	if(wr<0)
	{
		if(errno==ENOTTY)
		{
			printf("error number is -%d\n",ENOTTY);
			printf("Error is ENOTTY");
			perror("Error is ");
			return -ENOTTY;
			
			/*
			fd = open( "aa.bin", O_RDWR |O_CREAT);
			error number is -25
			Error is ENOTTY
			Error is : Inappropriate ioctl for device
			
			*/	
		}
	}
	


	printf("Reading Value from Driver\n");
	int rd=ioctl(fd, RD_VALUE, (int32_t*) &value);
	if(rd<0)
	{
		int er = errno;
		printf("%d\n",er);
		perror("Error\n");
	
	}
	
	printf("Value is %d\n", value);

	printf("Closing Driver\n");
	
	//fd=-1020;
	int c = close(fd);    //close() returns zero on success.  On error, -1 is returned, and errno is set to indicate the error.
	 //c = close(fd); 
	if(c<0)
	{
		if(errno==EBADF)
		{
			printf("error number is -%d\n",EBADF);
			printf("Error is EBADF");
			perror("[close fail] Error is ");
			return -EBADF;
			/*
			fd=-1020;
			error number is -9
			Error is EBADF
			[close fail] Error is : Bad file descriptor
			*/
			
			//c = close(fd); 
			
		}
		
	}
	
	
	exit(0);
}


