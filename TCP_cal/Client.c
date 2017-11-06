#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

void main()
{
	int sockfd,confd,op1,op2,choice,ans;
	char op;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket create successfully");
		
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 9999;
	
	int sinsize = sizeof(serveraddr);
	if((confd = connect(sockfd,(struct sockaddr*)&serveraddr,sinsize))>=0)
		printf("connection successfull \n");
		
	printf("\n 1- Addition \n 2- Subtraction \n 3- Multiplication \n 4- Division \n 5- Exit \n Enter your choice : ");
	scanf("%d",&choice);
	printf("Enter two operands : ");
	scanf("%d%d",&op1,&op2);
	switch(choice)
	{
		case 1:
			op='+';	
			break;
		
		case 2:
			op='-';	
			break;
		
		case 3:
			op='*';	
			break;
			
		case 4:
			op='/';	
			break;
			
		default:
			printf("wrong choice \n");
	}
	write(sockfd,&op1,sizeof(op1));
	write(sockfd,&op2,sizeof(op2));
	write(sockfd,&op,10);
	
	read(sockfd,&ans,sizeof(ans));
	
	printf("Ans : %d",ans);
	printf("\n");
	close(sockfd);
}
