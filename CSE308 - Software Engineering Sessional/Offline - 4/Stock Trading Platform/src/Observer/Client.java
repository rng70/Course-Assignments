package Observer;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    ClientConnection clientConnection;

    public static void main(String[] args) {
        new Client();
    }

    public Client(){
        try {
             Socket socket = new Socket("localhost", 3333);

             clientConnection = new ClientConnection(socket, this);
             clientConnection.start();
             listenForInput();
        } catch(UnknownHostException e){
            e.printStackTrace();
        } catch(IOException e){
            e.printStackTrace();
        }
    }

    public void listenForInput(){
        Scanner console = new Scanner(System.in);

        while(true){
            while(!console.hasNextLine()){
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            String input = console.nextLine();
            if(input.equalsIgnoreCase("quit")){
                break;
            }
            clientConnection.sendStringToServer(input);
        }
        clientConnection.close();
    }
}
