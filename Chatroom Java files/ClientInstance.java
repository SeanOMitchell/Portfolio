//Created by Sean Mitchell - 201155022 - University of Liverpool

import java.io.*;
import java.net.*;
import java.util.Scanner;

/**
 * The main class of the client.
 * Contains the Variables needed for proper functioning, and the run method.
 */
public class ClientInstance implements Runnable{

    //The server connection information
    public static String serverHost = "localhost";
    public static int serverPort = 2222;

    // The tools needed to communicate with the server
    private static Socket clientSocket = null;
    private static BufferedReader in = null;
    private static PrintWriter out = null;

    //A simple bool stating whether the client is closing or not
    private static boolean closed = false;

    /**
     * The main body of the Client, communicates with the server.
     * Asks for the server address, then connects to the server and constantly communicates via read and writes until closed.
     */
    public void run()
    {
        in = null;
        out = null;

        Scanner userInput = new Scanner(System.in);
        String argInput = null;

        //User input for the server address and error handling for invalid input
        System.out.println("Please enter the address of the server you wish to connect to.\nAlternatiely, type; localhost to connect locally");
        do {
            argInput = userInput.next();
            try {
                serverHost = argInput;
            } catch (Exception e) {
                System.out.print("Please enter a server address\n:");
                serverHost = null;
            }
        }while(serverHost == null);

        System.out.println("Thanks for using ChatterBot\nNow using host = " + serverHost + ", and portNumber = " + serverPort);

        //Try and open the I/O streams, and catch any errors
        try {
            // Connect to Server
            clientSocket = new Socket(serverHost, serverPort);
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
        } catch (UnknownHostException e) {
            System.out.println("Don't know about host " + serverHost);
        } catch (IOException e) {
            System.out.println("Couldn't get I/O for the connection to the host " + serverHost);
        }

        //If I/O was successfully started, start communictaing with the server
        if (clientSocket != null && in != null && out != null) {
            try {
                // Create and start Sender thread
                messageOut sending = new messageOut(out, closed);
                sending.start();

                // Read messages from the server and print them
                String message;
                while ((message = in.readLine()) != null) {
                    System.out.println(message);
                    if (message.indexOf("*** Bye") != -1) {
                        closed = true;
                        break;
                    }
                }

            } catch (IOException ioe) {
                System.out.println("Connection to server broken, we appologise for the inconveniance.");
                System.exit(1);
            } finally { // close connections
                closed = true;
                try {
                    in.close();
                } catch (IOException ioe) {
                    System.err.println("I/O error:");
                    System.err.println(ioe.getMessage());
                }
                if (out != null) {
                    out.close();
                }
                if (clientSocket != null) {
                    try {
                        clientSocket.close();
                    } catch (IOException ioe) {
                        System.err.println("I/O error:");
                        System.err.println(ioe.getMessage());
                    }
                }
            }
        }
    }
}

/**
 * The class for sending information to the server.
 * Implements a thread to be able to concurrently send information to the server.
 */
class messageOut extends Thread
{
    private PrintWriter mOut;
    private boolean done;

    /**
     * The constructor.
     * Initialises the variables in the class.
     * @param aOut the writer that allows for writing to the server.
     * @param closed simple bool tracking whether the client is closing.
     */
    public messageOut(PrintWriter aOut, boolean closed)
    {
        mOut = aOut;
        done = closed;
    }

    /**
     * Main body of the class.
     * Opens a reader and sends the information to the server.
     */
    public void run()
    {
        try {
            BufferedReader sIn = new BufferedReader(new InputStreamReader(System.in));

            while (!done) {
                String responseLine = sIn.readLine();
                mOut.println(responseLine);
                mOut.flush();
                if (responseLine.startsWith("/quit")){
                    break;
                }
            }
        } catch (IOException ioe) {
            System.err.println("I/O error:");
            System.err.println(ioe.getMessage());
        }
    }
}