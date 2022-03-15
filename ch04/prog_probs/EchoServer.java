/**
 * Echo server program 
 *
 */
 
import java.net.*;
import java.io.*;
import java.util.concurrent.*;

class EchoServerThread implements Runnable {

	Socket client;
	
	public EchoServerThread(Socket client) {
		this.client = client;
	}

	public void run() {
		try {
			InputStream sockIn = client.getInputStream();
			OutputStream sockOut = client.getOutputStream();

			int sockByte;
			while ( (sockByte = sockIn.read()) != -1) { // connection alive
				System.out.print((char) sockByte);
				sockOut.write(sockByte);
			}

			// close the socket and resume listening for more connections
			client.close();
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}

public class EchoServer
{
	public static void main(String[] args)  {
		try {
			ServerSocket sock = new ServerSocket(7777);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// we have a connection

				Thread thrd = new Thread(new EchoServerThread(client));
				thrd.start();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
	}
}
