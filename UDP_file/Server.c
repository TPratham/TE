#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define len 500

unsigned long fsize(char *file)
{
	FILE *fp = fopen(file,"r");
	fseek(fp,0,SEEK_END);
	unsigned long f = (unsigned long)ftell(fp);
	fclose(fp);
	return f;
}

void main()
{
	int sockfd;
	
	if((sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))>0)
		printf("socket create successfully \n");
		
	struct sockaddr_in addr,addr1;
	
	addr.sin_family = AF_INET;
	addr.sin_port = 9999;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	
	int addr_size = sizeof(addr);
	
	if((bind(sockfd,(struct sockaddr*)&addr,addr_size))==0) 
		printf("Bind successfull \n");
		
	char buffer[len],fname[len];
	memset(buffer,0,len);	
	
	recvfrom(sockfd,buffer,len,0,(struct sockaddr*)&addr1,&addr_size);
	strcpy(fname,buffer);
	
	printf("name of file to send : %s",fname);
	unsigned long size = fsize(fname);
	sendto(sockfd,&size,sizeof(size),0,(struct sockaddr*)&addr1,addr_size);
	
	memset(buffer,0,len);
	int itr=1;
	FILE *fp = fopen(fname,"rb");
	while(itr*len<size)
	{
		fread(buffer,len,1,fp);
		sendto(sockfd,buffer,len,0,(struct sockaddr*)&addr1,addr_size);
		//itr++;
	}
	fread(buffer,size%len,1,fp);
	sendto(sockfd,buffer,len,0,(struct sockaddr*)&addr1,addr_size);
	printf("\nFile send \n");
	fclose(fp);
	close(sockfd);
}
