import java.net.*;
import java.io.*;
import java.util.*;

class Server
{
	public static void main(String args[]) throws Exception
	{
		System.out.println("Waiting for connection ");
		ServerSocket ss = new ServerSocket(9999);
		Socket s = ss.accept();
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout = new DataOutputStream(s.getOutputStream());

		int n,ack;
		n = din.read();
		boolean arr[] = new boolean[n+1];
		System.out.println("No of frames to send : "+n);
		
		for(int i=1;i<=n;i++)
		{
			if(i==3)
			{
				System.out.println("sending frame no : "+i);
				System.out.println("Waiting foe Ack ");
				System.out.println("Negative ack received for frame no : 3");
			}
			else
			{
				dout.write(i);
				System.out.println("sending frame no : "+i);
				System.out.println("Waiting foe Ack ");
				Thread.sleep(2000);
				ack = din.read();
				
				if(ack != 255)
				{
					System.out.println("Positive ack received for frame no : "+i);
					arr[i]=true;
				}
				else
					System.out.println("Negative ack received for frame no : "+i);
					
			}
			System.out.println();
		}
		
		for(int i=1;i<=n;i++)
		{
			if(arr[i]==false)
			{
				dout.write(i);
				System.out.println("Resending frame no : "+i);
				System.out.println("Waiting foe Ack ");
				Thread.sleep(2000);
				ack = din.read();
				System.out.println("Positive ack received for frame no : "+ack);
				arr[ack]=true;
			}
			System.out.println();
		}
		System.out.println("Transfer Complete ");
		din.close();
		dout.close();
		s.close();
		ss.close();		
	}
}
