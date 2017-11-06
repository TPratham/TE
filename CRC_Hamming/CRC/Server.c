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
	int d[20],g[20],n,ng,app,temp[20],crc[20],i,k,j,flag=0;

	
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
		
	read(confd,&n,sizeof(n));
	read(confd,&app,sizeof(app));	
	
	for(i=0;i<n+app;i++)
	{
		read(confd,&d[i],sizeof(d[i]));
	}
	
	printf("\nMessage received : ");
	for(int i=0;i<n+app;i++)
	{
		printf("%d",d[i]);
	}
	printf("\n");
	read(confd,&ng,sizeof(ng));
	
	for(i=0;i<ng;i++)
	{
		(confd,&g[i],sizeof(g[i]));
	}
	for(int j=0;j<n+app;j++)
		temp[j]=d[j];
	
	for(i=0;i<n+app;i++)
	{
		j=0;
		k=i;
		if(temp[k]>=g[j])
		{
			for(j=0,k=i;j<ng;j++,k++)
			{
				if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
				{
				    temp[k]=0;
				}
				else
				{
				    temp[k]=1;
				}
			 }
		}
	}
	
	for(i=0,j=n;i<n+app;i++,j++)
	{
		crc[i]=temp[j];
	}
	
	for(i=0;i<app-1;i++)
	{
		if(crc[i] == 0)
			flag=1;
	}
	printf("\n");
	
	if(flag==1)
		printf("No Error in frame");
	else
		printf("Error In frame ");
	printf("\n");
}
