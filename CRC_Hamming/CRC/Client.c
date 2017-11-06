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
	int d[20],g[20],n,ng,app,temp[20],crc[20],i,k;
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created suuccessfully \n");
		
	struct sockaddr_in serveraddr;
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = 6666;
	
	int sin_size = sizeof(serveraddr);
	if((confd = connect(sockfd,(struct sockaddr*)&serveraddr,sin_size))==0)
		printf("connection successful \n");
		
	printf(" Enter size of Data : ");
	scanf("%d",&n);
	
	printf(" Enter Data : ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&d[i]);
	}
	
	printf(" Enter size of Generator : ");
	scanf("%d",&ng);
	
	printf(" Enter Data : ");
	for(i=0;i<ng;i++)
	{
		scanf("%d",&g[i]);
	}
	
	app = ng-1;
	printf("\n No of 0's to be appended : ");
	printf("%d",app);
	
	for(int i=n;i<n+app;i++)
	{
		d[i]=0;
	}
	printf("\n Message After appending zero : ");
	for(int i=0;i<n+app;i++)
	{
		printf("%d",d[i]);
	}
	printf("\n");
	for(int j=0;j<n+app;j++)
		temp[j]=d[j];
	int j;
	for(i=0;i<n;i++)
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
	
	for(i=n,j=0;i<n+app;i++,j++)
	{
		d[i]=crc[j];
	}
	
	printf("\n Message to be transferred : ");
	for(int i=0;i<n+app;i++)
	{
		printf("%d",d[i]);
	}
	printf("\n");
	
	write(sockfd,&n,sizeof(n));
	write(sockfd,&app,sizeof(app));
	d[5]=1;
	
	for(i=0;i<n+app;i++)
	{
		write(sockfd,&d[i],sizeof(int));
	}
	write(sockfd,&ng,sizeof(ng));
	for(i=0;i<ng;i++)
	{
		write(sockfd,&g[i],sizeof(g[i]));
	}
	
	
}
