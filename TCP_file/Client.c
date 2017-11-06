#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main()
{
	int sockfd,confd;
	char ch;
	FILE *fp;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created suuccessfully \n");
		
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 6666;
	
	int sin_size = sizeof(serveraddr);
	if((confd = connect(sockfd,(struct sockaddr*)&serveraddr,sin_size))==0)
		printf("connection successful \n");
		
	fp = fopen("b.txt","w");
	read(sockfd,&ch,sizeof(ch));
	while(ch!=EOF)
	{
		fputc(ch,fp);
		read(sockfd,&ch,sizeof(ch));
	}
	printf("FILE RECEIVED \n");
	fclose(fp);
}
