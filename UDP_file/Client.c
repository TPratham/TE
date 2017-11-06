#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define len 500
#define SERVER "127.0.0.1"

void main()
{
	int sockfd,l,i;
	unsigned long size;
	
	if((sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))>0)
		printf("socket create successfully \n");
		
	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = 9999;	
	int addr_size = sizeof(addr);
	
	if(inet_aton(SERVER,&addr.sin_addr)==0)
		printf("address converted successfully \n");
		
	char buffer[len],fname[20];
	memset(buffer,0,len);
	
	printf("Enter file name : ");
	scanf("%s",fname);
	l = strlen(fname);
	sendto(sockfd,fname,sizeof(fname),0,(struct sockaddr*)&addr,addr_size);
	recvfrom(sockfd,&size,sizeof(size),0,(struct sockaddr*)&addr,&addr_size);
	
	for(i=0;i<l-1;i++)
	{
		if(fname[i]=='.')
		{
			fname[i-1]='1';
		}
	}
	
	memset(buffer,0,len);
	int itr=1;
	FILE *fp = fopen(fname,"wb");
	while(itr*len<size)
	{
		recvfrom(sockfd,buffer,len,0,(struct sockaddr*)&addr,&addr_size);
		fwrite(buffer,len,1,fp);
		memset(buffer,0,len);
		itr++;
	}
	recvfrom(sockfd,buffer,len,0,(struct sockaddr*)&addr,&addr_size);
	fwrite(buffer,size%len,1,fp);
	printf("File received \n");
	fclose(fp);
	close(sockfd);
}
