import java.io.*;
import java.net.*;

class Server
{
	public static void main(String args[]) throws Exception
	{
		DatagramSocket s = new DatagramSocket(85);
		InetAddress ra = InetAddress.getLocalHost();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		byte buf[];
		String str1="",str2="";
		while(!str1.equals("stop"))
		{
			byte buffer[] = new byte[20];
			DatagramPacket p1 = new DatagramPacket(buffer,buffer.length);
			s.receive(p1);
			buffer = p1.getData();
			str1 = new String(buffer);
			System.out.println("Client says : "+str1);
			str2 = br.readLine();
			buf = str2.getBytes();
			DatagramPacket p2 = new DatagramPacket(buf,buf.length,ra,84);
			s.send(p2);
		}
	}
}
