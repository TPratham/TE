import java.io.*;
import java.net.*;

class Server
{
	public static void main(String args[]) throws Exception
	{
		ServerSocket ss = new ServerSocket(8888);
		while(true)
		{
			Socket s = ss.accept();
			DataInputStream din = new DataInputStream(s.getInputStream());
			DataOutputStream dout = new DataOutputStream(s.getOutputStream());
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
			String str1="",str2="",str3="";
			while(str1!="stop")
			{
				str1 = din.readUTF();
				System.out.println("Client1 Says : "+str1);
				str3 = din1.readUTF();
				System.out.println("Client2 Says : "+str3);
				str2=br.readLine();
				dout.writeUTF(str2);
				dout1.writeUTF(str2);
				dout.flush();
			}
		}
		din.close();
		s.close();
		ss.close();
	}
}
