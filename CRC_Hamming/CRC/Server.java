import java.io.*;
import java.net.*;

class Server
{
	public static void main(String args[])throws Exception
	{
		ServerSocket ss = new ServerSocket(8888);
		Socket s = ss.accept();
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout = new DataOutputStream(s.getOutputStream());
	
		int d[] = new int[20],g[] = new int[20],temp[] = new int[20],crc[] = new int[20];
		int t,lg,l,flag=0;
		
		t = din.read();
		for(int i=0;i<t;i++)
		{
			d[i]=din.read();
		}
		
		System.out.print("Message Received : ");
		for(int i=0;i<t;i++)
		{
			System.out.print(d[i]);
		}
		
		lg = din.read();
		for(int i=0;i<lg;i++)
		{
			g[i]=din.read();
		}
		l = t-lg-1;
		
		for(int j=0;j<t;j++)
			temp[j]=d[j];
		
		int k=0;
		for(int i=0;i<t;i++)
		{
			int j=0;
			k=i;
			if (temp[k]>=g[j])
			{
			    for(j=0,k=i;j<lg;j++,k++)
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
		
		for(int i=0,j=l;i<t;i++,j++)
		{
			crc[i]=temp[j];
		}
		
		for(int i=0;i<lg-1;i++)
		{
			if(crc[i] == 0)
				flag=1;
		}
		System.out.println();
		
		if(flag==1)
			System.out.println("No Error in frame");
		else
			System.out.println("Error In frame ");
	}
}
