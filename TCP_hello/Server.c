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
	struct sockaddr_in clientaddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 6066;
	
	if((bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)))==0)
	{
		printf("Bind successful  \n");
	}

	if((listen(sockfd,5))==0)
	{
		printf("Listen successful  \n");
	}
	
	int sin_addr = sizeof(struct sockaddr_in);
	
	if((confd = accept(sockfd,(struct sockaddr *)&clientaddr,&sin_addr))>=0)
	{
		printf("Accept successful  \n");
	}
	
	while(1)
	{
		read(confd,&msg,sizeof(msg));
		printf("Client says : %s",msg);
		printf("\n");
		scanf("%s",msg1);
		write(confd,msg1,sizeof(msg1));
	}

}
