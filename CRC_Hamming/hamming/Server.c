#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main()
{
	int sockfd,confd;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created successfully \n");
		
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 9999;
	
	if((bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==0)
		printf("Bind successful \n");
		
	if((listen(sockfd,5))==0)
		printf("Listen successful \n");
		
	int sin_size = sizeof(serveraddr);
	if((confd = accept(sockfd,(struct sockaddr*)&clientaddr,&sin_size))>=0)
		printf("Accept successful \n");
	
	int data[11],i;
	int c0,c1,c3,c7,er;
	
	for(i=0;i<11;i++)
	{
		read(confd,&data[i],sizeof(int));
	}
	
	c0 = data[2] ^ data[4] ^ data[6] ^ data[8] ^ data[10];
	if(c0 == data[0])
		c0=0;
	else
		c0=1;
	
	c1 = data[2] ^ data[5] ^ data[6] ^ data[9] ^ data[10];
	if(c1 == data[1])
		c1=0;
	else
		c1=1;
	
	c3 = data[4] ^ data[5] ^ data[6];
	if(c3 == data[3])
		c3=0;
	else
		c3=1;
	
	c7 = data[8] ^ data[9] ^ data[10];
	if(c7 == data[7])
		c7=0;
	else
		c7=1;
	
	if( c0==0 && c1 == 0 && c3 == 0 && c7 == 0)
	{
		printf("\nNo error in frame \n");
		printf("Data Received: ");
		for(i=10;i>=0;i--)
		{
			printf("%d",data[i]);
		}
	}
	else
	{
		printf("\nError in frame ");
		er = c7*8 + c3*4 + c1*2 + c0;
		printf("\nError at position : %d \n",er-1);
		if(data[er-1]==0)
			data[er-1]=1;
		else
			data[er-1]=0;
			
		printf("Corrected Data : ");
		for(i=10;i>=0;i--)
		{
			printf("%d",data[i]);
		}
	}
	printf("\n");
}
