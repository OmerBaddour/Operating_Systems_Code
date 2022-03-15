/**
 * Echo client program 
 *
 */ 

import java.net.*;
import java.io.*;

public class EchoClient
{
	public static void main(String[] args)  {
		try {
			// this could be changed to an IP name or address other than the localhost
			Socket sock = new Socket("127.0.0.1",7777);
			InputStream sockIn = sock.getInputStream();
			OutputStream sockOut = sock.getOutputStream();

			int stdinByte;
			int sockByte;
			while (true) {
				// read from stdin
				if ( (stdinByte = System.in.read()) != -1) {
					// send through socket
					sockOut.write(stdinByte);
				}
				

				// read from socket
				if ( (sockByte = sockIn.read()) != -1) {
					// write to stdout
					System.out.print((char)sockByte);
				}
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
	}
}
