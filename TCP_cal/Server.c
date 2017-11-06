#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

void main()
{
	int sockfd,confd,op1,op2,ans=0;
	char op;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>=0)
		printf("Socket created successfully \n");
		
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 9999;
	
	if((bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==0)
		printf("Bind successfull \n");
		
	if((listen(sockfd,5))==0)
		printf("Listen successfull \n");
	
	int sinsize = sizeof(serveraddr);
	if((confd = accept(sockfd,(struct sockaddr*)&serveraddr,&sinsize))>=0)
		printf("Accept Successsfull \n");
	
	read(confd,&op1,sizeof(op1));
	read(confd,&op2,sizeof(op2));
	read(confd,&op,10);
	printf("op1 =: %d \n",op1);
	printf("op2 =: %d \n",op2);
	
	switch(op)
	{
		case '+':
			ans = op1+op2;
			break;
		
		case '-':
			ans = op1-op2;
			break;
		
		case '*':
			ans = op1*op2;
			break;
			
		case '/':
			ans = op1/op2;
			break;
			
		default:
			printf("wrong choice \n");
	}
	printf("Ans : %d",ans);
	printf("\n");
	write(confd,&ans,sizeof(ans));
	close(sockfd);
}
