/**
 * Quote-of-the-day server listening to port 6017.
 *
 */
 
import java.net.*;
import java.io.*;

public class QOTDServer
{
	public static void main(String[] args)  {
		try {
			ServerSocket sock = new ServerSocket(6017);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// we have a connection
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				// write the Date to the socket
				pout.println("Quote of the day");

				// close the socket and resume listening for more connections
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
	}
}
