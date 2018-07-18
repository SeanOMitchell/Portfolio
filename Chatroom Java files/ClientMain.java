//Created by Sean Mitchell - 201155022 - University of Liverpool

/**
 * The main method of the program.
 * Calls the {@link ClientInstance client} class to start the client and connect to the server.
 */
public class ClientMain {
    public static void main(String[] args) {
        ClientInstance cInstance = new ClientInstance();
        cInstance.run();
    }
}
