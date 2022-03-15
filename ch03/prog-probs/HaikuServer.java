/**
 * Haiku server listening to port 6017.
 *
 */
 
import java.net.*;
import java.io.*;

public class HaikuServer
{
	public static void main(String[] args)  {
		try {
			ServerSocket sock = new ServerSocket(5575);

			// now listen for connections
			while (true) {
				Socket client = sock.accept();
				// we have a connection
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				// write the Date to the socket
				pout.println("An old silent pond\nA frog jumps into the pond--\n"
					     + "Splash! Silence again.");

				// close the socket and resume listening for more connections
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
	}
}
