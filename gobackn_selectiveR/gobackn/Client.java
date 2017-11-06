import java.net.*;
import java.io.*;
import java.util.*;

class Client
{
	public static void main(String args[]) throws Exception
	{
		Socket s = new Socket("localhost",9999);
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout = new DataOutputStream(s.getOutputStream());
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Scanner sc = new Scanner(System.in);
		
		int n,check,frame,ack;
		
		System.out.println("Enter no of frames to receive : ");
		n = sc.nextInt();
		dout.write(n);
		dout.flush();
		check=1;
		for(int i=1;i<=n;i++)
		{
			frame = din.read();
			if(frame==check)
			{
				System.out.println("Received frame no : "+i);
				System.out.println("Sending positive Ack ");
				Thread.sleep(2000);
				ack=frame;
				dout.write(ack);
				++check;
			}
			else
			{
				if(frame==4)
				{
					System.out.println("Discarded frame no: "+3);
					System.out.println("Sending NEGATIVE ack");
					System.out.println();
				}
				--i;
				System.out.println("Discarded frame no: "+frame);
				System.out.println("Sending NEGATIVE ack");
				dout.write(-1);
			}
			System.out.println();
		}
		System.out.println("Transfer Complete ");
		din.close();
		dout.close();
		s.close();
	}
}
