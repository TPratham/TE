import java.io.*;
import java.net.*;
import java.util.*;

class Client
{
	public static void main(String args[])throws Exception
	{
		Socket s = new Socket("localhost",8888);
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout = new DataOutputStream(s.getOutputStream());
		Scanner sc = new Scanner(System.in);
		
		int d[] = new int[20],g[] = new int[20],temp[] = new int[20],crc[] = new int[20];
		int l,lg,app,t;
		
		System.out.println("Enter size of Data : ");
		l = sc.nextInt();
		System.out.println("Enter Data : ");
		for(int i=0;i<l;i++)
		{
			d[i] = sc.nextInt();
		}
		
		System.out.println("Enter size of Generator : ");
		lg = sc.nextInt();
		System.out.println("Enter Data : ");
		for(int i=0;i<lg;i++)
		{
			g[i] = sc.nextInt();
		}
		
		app = lg-1;
		System.out.println("No of 0's to be Appended : "+app);
		t=l+app;
		
		for(int i=l;i<t;i++)
		{
			d[i]=0;
		}
		
		System.out.print("Message afer appending zero's : ");
		for(int i=0;i<t;i++)
		{
			System.out.print(d[i]);
		}
		System.out.println();
		
		for(int j=0;j<t;j++)
			temp[j]=d[j];
		
		int k=0;
		for(int i=0;i<l;i++)
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
		
		for(int i=l,j=0;i<t;i++,j++)
		{
			d[i]=crc[j];
		}
		
		System.out.print("Message to send : ");
		for(int i=0;i<t;i++)
		{
			System.out.print(d[i]);
		}
		dout.write(t);
		for(int i=0;i<t;i++)
		{
			dout.write(d[i]);
		}
		
		dout.write(lg);
		for(int i=0;i<lg;i++)
		{
			dout.write(g[i]);
		}
		System.out.println();
	}
}
