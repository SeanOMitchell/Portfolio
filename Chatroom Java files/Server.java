//Created by Sean Mitchell - 201155022 - University of Liverpool

import java.io.*;
import java.net.*;
import java.util.*;

/**
 * The main class of the program.
 * Contains the variables needed for the server to function and the methods that give it functionality.
 */
public class Server {

    //Tools to create the server and allow clients to connect
    private static int portNum = 2222;
    private static ServerSocket serverSocket = null;
    private static Socket clientSocket = null;

    // This chat server can accept up to maxClientsCount clients' connections.
    private static final int maxClientsCount = 50;
    private static final clientThread[] clientList = new clientThread[maxClientsCount];

    //Extra variables for storing extra server details
    private static final ServerDetails sDetails = new ServerDetails();
    private static final HashSet<String> clientNames = new HashSet<>();
    static ArrayList<Socket> clientSocketList = new ArrayList<>(); 

    /**
     * The main method of the program.
     * Creates the server and constantly listens for and allows new clients to connect.
     */
    public static void main(String args[]) {
        Thread thread;
        if (args.length >= 1) {
            portNum = Integer.valueOf(args[0]).intValue();
        }

        System.out.println("Opening the server using port number = " + portNum);

    //Open a server socket on the portNumber (default 2222) and catch any exceptions
        try {
            serverSocket = new ServerSocket(portNum);
            sDetails.setServerStartTime(System.nanoTime());
            InetAddress ip;
            ip = InetAddress.getLocalHost();
            sDetails.setipAddress(ip.getHostAddress());
            //Accept incoming clients connecting to the server
            while (true) {
                clientSocket = serverSocket.accept();
                //create a new thread to handle the running of the client
                thread = new Thread(new clientThread(clientSocket, clientList, sDetails, clientNames));
                thread.start();
                //Add the created thread to the list of clients
                clientSocketList.add(clientSocket);

            }
        } catch (IOException ioe) {
            System.err.println("I/O error:");
            System.err.println(ioe.getMessage());
            System.exit(1);
        }
    }
}

/**
 * The main class of the program.
 * Creates the server and constantly listen for and allow new clients to connect.
 * Distributes data around between clients and the user.
 */
class clientThread implements Runnable {

    //Tools needed for client - server communication
    private BufferedReader is = null;
    private PrintStream os = null;
    private Socket clientSocket = null;

    //The list of all clients for sending messages to all
    private final clientThread[] clientList;
    private int maxClientsCount;

    //Additional information needed for commands
    private ServerDetails sDetails;
    private HashSet<String> clientNames;
    private long clientStartTime = 0;

    /**
     * The constructor for the {@link clientThread client} class.
     * Instantiates all private variables to those passed through the parameters.
     * @param clientSocket the client socket that is linked to this thread.
     * @param clientThreads the List of all active connected clients.
     * @param serverDetails additional list of details about the server inclusing ip Address and time started.
     * @param nameList the list of all currently in use usernames.
     */
    public clientThread(Socket clientSocket, clientThread[] clientThreads, ServerDetails serverDetails, HashSet<String> nameList) {
        this.clientSocket = clientSocket;
        this.clientList = clientThreads;
        this.maxClientsCount = clientList.length;
        this.sDetails = serverDetails;
        this.clientNames = nameList;
    }

    /**
     * The main method of the class.
     * Contains all the I/O for the client talking to the server, including asking for data, recieving and sending messages between clients and fullfilling commands.
     */
    public void run() {
        int maxClientsCount = this.maxClientsCount;
        clientThread[] clientList = this.clientList;
        String name = null;

        try {
            //Create input and output streams for this client
            this.is = new BufferedReader(new InputStreamReader(this.clientSocket.getInputStream()));
            this.os = new PrintStream(this.clientSocket.getOutputStream());
            //Prompt user to enter a username, must not be already in use
            this.os.println("Enter your name.");
            String nameInput = null;
            do {
                nameInput = this.is.readLine().trim();
                try {
                    name = nameInput;
                } catch (Exception e) {
                    this.os.println("Please enter a name");
                    name = null;
                }
                if(this.clientNames.contains(name)){
                    this.os.println("Sorry that name is taken, please try again");
                    name = null;
                }
            }while(name == null);
            this.clientNames.add(name);
            //Track when the client connected to the server
            this.clientStartTime = System.nanoTime();
            //Display welcome message to all other users as well as unique welcome messages for the user
            this.os.println("Hello " + name + ". Welcome to ChatterBot.\nTo leave, enter /quit in a new line");
            for (int i = 0; i < maxClientsCount; i++) {
                if ((clientList[i] != null) && (clientList[i] != this)) {
                    clientList[i].os.println("*** " + name + " has entered ChatterBot ***");
                } else if ((clientList[i] != null) && (clientList[i] == this)) {
                    clientList[i].os.println("*** You have entered ChatterBot using the name; " + name + " ***\nUse /commands to see a list of commands you can use");
                }
            }
            //Reads the users input and either distributes it to other clients or fulfills the request
            while (true) {
                String line = this.is.readLine();
                if (line.startsWith("/quit")) {
                    break;
                } else if (line.startsWith("/serverup")) {
                    this.os.println(this.sDetails.serverRunTime());
                    this.os.flush();
                } else if (line.startsWith("/clientup")) {
                    long totalTime = System.nanoTime() - clientStartTime;
                    this.os.println(totalTime / 1000000000);
                    this.os.flush();
                } else if (line.startsWith("/ip")) {
                    this.os.println(sDetails.getIpAddress());
                    this.os.flush();
                } else if (line.startsWith("/connected")) {
                    this.os.println("Connected clients; " + this.clientNames.size());
                    this.os.flush();
                } else if (line.startsWith("/commands")) {
                    this.os.println("/serverup;  How long the server has been running\n" +
                            "/clientup;  How long the client has been running\n" +
                            "/ip;        Lists the client's ip address\n" +
                            "/connected; How many clients are connected to the server\n" +
                            "/quit;      Quit ChatterBot");
                    this.os.flush();
                } else {
                    PrintStream oss;
                    for (int i = 0; i < Server.clientSocketList.size(); i++) {
                        final Socket outputSocket = Server.clientSocketList.get(i);
                        if (clientSocket != outputSocket) {
                            try {
                                oss = new PrintStream(outputSocket.getOutputStream());
                                oss.println("<" + name + "> " + line);
                                oss.flush();
                            }
                            catch (IOException ioe) {
                                System.err.println("I/O error:");
                                System.err.println(ioe.getMessage());
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < maxClientsCount; i++) {
                if ((clientList[i] != null) && (clientList[i] != this)) {
                    clientList[i].os.println("*** " + name + " is leaving ChatterBot ***");
                    clientList[i].os.flush();
                }
            }
            this.os.println("*** Bye " + name + " ***");
            this.os.flush();
            this.clientNames.remove(name);

        } catch (IOException ioe) {
            System.err.println("I/O error:");
            System.err.println(ioe.getMessage());
        } finally { // close connections

            //Clean-up and releasing the array space for another client to join
            for (int i = 0; i < maxClientsCount; i++) {
                if (clientList[i] == this) {
                    clientList[i] = null;
                }
            }

            this.clientNames.remove(name);

            try {
                this.is.close();
            } catch (IOException ioe) {
                System.err.println("I/O error:");
                System.err.println(ioe.getMessage());
            }
            if (this.os != null) {
                this.os.close();
            }
            if (this.clientSocket != null) {
                try {
                    this.clientSocket.close();
                } catch (IOException ioe) {
                    System.err.println("I/O error:");
                    System.err.println(ioe.getMessage());
                }
            }
        }
    }
}

/**
 * Contains details about the server for all clients.
 * Stores the ip of the Server and the time when it was first started.
 */
class ServerDetails{
    private long serverStartTime = 0;
    private String ipAddress = null;

    /**
     * Set the server start time.
     * @param startTime the value that will become the servers start time value.
     */
    public void setServerStartTime(long startTime){
        serverStartTime = startTime;
    }

    /**
     * Get the server run time.
     * Works out the difference in time between the request and when the server started and converts it to seconds.
     */
    public long serverRunTime(){
        long endTime = System.nanoTime();
        long totalTime = endTime - serverStartTime;
        return (totalTime / 1000000000);
    }

    /**
     * Set the ip address.
     * @param ip the value that will become the ipAddress' value.
     */
    public void setipAddress(String ip){
        ipAddress = ip;
    }

    /**
     * Gets the Ip address of the server.
     */
    public String getIpAddress(){
        return ipAddress;
    }
}
