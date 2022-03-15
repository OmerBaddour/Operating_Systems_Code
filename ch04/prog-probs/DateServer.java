/**
 * Time-of-day server listening to port 6013.
 *
 * Figure 3.27
 *
 * @author Silberschatz, Gagne, and Galvin. 
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018.
 */
 
import java.net.*;
import java.io.*;
import java.util.concurrent.*;

class DateServerThread implements Runnable {
	
	Socket client;

	public DateServerThread(Socket client) {
		this.client = client;
	}

	public void run() {

		try {
			PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
			// write the Date to the socket
			pout.println(new java.util.Date().toString());

			// close the socket and resume listening for more connections
			client.close();
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}

public class DateServer
{
	public static void main(String[] args)  {
		try {
			ServerSocket sock = new ServerSocket(6013);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// we have a connection

				Thread thrd = new Thread(new DateServerThread(client));
				thrd.start();
			}
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}
