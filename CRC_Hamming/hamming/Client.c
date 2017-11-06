#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

void main()
{
	int sockfd,confd;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created successfully \n");
		
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 9999;
	
	int sin_size = sizeof(serveraddr);
	
	if((confd = connect(sockfd,(struct sockaddr*)&serveraddr,sin_size))>=0)
		printf("Connect successfully \n");
		
	int data[11],i;
	printf("Enter 7 bit data : \n");
	scanf("%d",&data[10]);
	scanf("%d",&data[9]);
	scanf("%d",&data[8]);
	scanf("%d",&data[6]);
	scanf("%d",&data[5]);
	scanf("%d",&data[4]);
	scanf("%d",&data[2]);
	
	data[0] = data[2]^data[4]^data[6]^data[8]^data[10];
	
	data[1] = data[2]^data[5]^data[6]^data[9]^data[10];
	
	data[3] = data[4]^data[5]^data[6];
	
	data[7] = data[8]^data[9]^data[10];
	
	printf("Data to Transfer : ");
	for(i=10;i>=0;i--)
	{
		printf("%d",data[i]);
	}
	data[10] = 0;
	for(i=0;i<11;i++)
	{
		write(sockfd,&data[i],sizeof(int));
	}
	printf("\n");
}
