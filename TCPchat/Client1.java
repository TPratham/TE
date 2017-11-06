import java.io.*;
import java.net.*;

class Client1
{
	public static void main(String args[]) throws Exception
	{
		Socket s = new Socket("localhost",8888);
		DataInputStream din = new DataInputStream(s.getInputStream());
		DataOutputStream dout = new DataOutputStream(s.getOutputStream());
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String str1="",str2="";
		while(str1!="Stop")
		{
			str1=br.readLine();
			dout.writeUTF(str1);
			dout.flush();
			str2=din.readUTF();
			System.out.println("Server Says : "+str2);
		}
		dout.close();
		s.close();
	}
}
