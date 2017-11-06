#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

void main()
{
	int sockfd,confd;
	char msg[20],msg1[20];
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
	{
		printf("Socket created successfully  \n");
	}
	
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 6066;
	
	int sin_size = sizeof(struct sockaddr_in);
	
	if((confd = connect(sockfd,(struct sockaddr *)&serveraddr,sin_size))>0)
	{
		printf("connect successfully  \n");
	}
	
	while(1)
	{
		scanf("%s",msg);
		write(sockfd,msg,sizeof(msg));
		
		read(sockfd,&msg1,sizeof(msg1));
		printf("Server says : %s",msg1);
		printf("\n");
	}
}
