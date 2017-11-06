#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main()
{
	int sockfd,confd;
	FILE *fp;
	char ch;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))>=0)
		printf("Socket create successfully \n");
		
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 6666;
	
	if((bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))==0)
		printf("Bind successful \n");
	
	if((listen(sockfd,5))==0)
		printf("listen successful \n");
		
	int sin_size = sizeof(clientaddr);
	if((confd = accept(sockfd,(struct sockaddr*)&clientaddr,&sin_size))>0)
		printf("accept successful \n");
		
	fp = fopen("abc.txt","r");
	ch = fgetc(fp);
	while(ch!=EOF)
	{
		write(confd,&ch,sizeof(ch));
		ch = fgetc(fp);
	}
	write(confd,&ch,sizeof(ch));
	printf("file send \n");
	fclose(fp);	
}
