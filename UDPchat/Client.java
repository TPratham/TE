import java.io.*;
import java.net.*;

class Client
{
	public static void main(String args[]) throws Exception
	{
		DatagramSocket s = new DatagramSocket(84);
		InetAddress ra = InetAddress.getLocalHost();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		byte buf[];
		String str1="",str2="";
		while(!str1.equals("stop"))
		{
			str1 = br.readLine();
			buf = str1.getBytes();
			DatagramPacket p1 = new DatagramPacket(buf,buf.length,ra,85);
			s.send(p1);
			byte buffer[] = new byte[20];
			DatagramPacket p2 = new DatagramPacket(buffer,buffer.length);
			s.receive(p2);
			buffer = p2.getData();
			str2 = new String(buffer);
			System.out.println("Server Says : "+str2);
		}
	}
}
