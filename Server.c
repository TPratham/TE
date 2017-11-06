#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */

int open_port()
{
	int fd;
	
	fd = open("/dev/ttys0", O_RDWR | O_NOCTTY | O_NDELAY);  /* O_NOCTTY If you don't specify this then any input (such as 	keyboard abort signals and so forth) will affect your process*/ 
		
	if(fd == -1)
		printf("Error in opening serial port \n");
	else
		printf("Port opened successfully \n");
	
	return fd;
}

void main()
{
	int mainfd;
	char ch;
	struct termios options;
	mainfd = open_port();
	
	fcntl(mainfd,F_SETFL,FNDELAY);
	/*The FNDELAY option causes the read function to return 0 if no characters are available on the port*/ 
	/*F_SETFL : Set the file status flags to the value specified*/
	
	tcgetattr(mainfd,&options);
	cfsetispeed(&options,B9600);
	cfsetospeed(&options,B9600);
	
	options.c_cflag |= (CLOCAL | CREAD); /*These will ensure that your program does not become the 'owner' of the port*/
	options.c_cflag &= ~PARENB;	    /*Disable parity bit*/
	options.c_cflag &= ~CSTOPB;  	    /*Disable stop bits*/
	options.c_cflag &= ~CSIZE; 	    /*Mask the character size*/
	options.c_cflag |= CS8;		    /* 8 data bits*/
	options.c_cflag &= ~CRTSCTS;	    /*Enable hardware flow control*/
	
	options.c_lflag &= ~(ICANON | ECHO | ISIG);	 /* Enable data to be processed as raw input */
	/*ICANON : Enable canonical input */
	/*ECHO : Enable echoing of input characters*/
	/*ISIG : Enable SIGINTR, SIGSUSP, SIGDSUSP, and SIGQUIT signals*/
	
	tcsetattr(mainfd,TCSANOW,&options);		/* Set the new options for the port */
	/*The TCSANOW constant specifies that all changes should occur immediately without waiting*/
}
