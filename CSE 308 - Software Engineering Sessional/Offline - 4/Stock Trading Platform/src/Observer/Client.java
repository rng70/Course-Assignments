package Observer;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    Socket socket;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    public static void main(String[] args) {
        new Client();
    }
    public Client(){
        try {
             socket = new Socket("localhost", 3333);
             dataInputStream = new DataInputStream(socket.getInputStream());
             dataOutputStream = new DataOutputStream(socket.getOutputStream());

            listenFotInput();
        } catch(UnknownHostException e){
            e.printStackTrace();
        } catch(IOException e){
            e.printStackTrace();
        }
    }
    public void listenFotInput(){
        Scanner console = new Scanner(System.in);
        while(true){
            while(console.hasNextLine()){
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
            try {
                dataOutputStream.writeUTF(input);
                while(dataInputStream.available()==0){
                    try {
                        Thread.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                String reply = dataInputStream.readUTF();
                System.out.println(reply);
            } catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }
        try {
            dataInputStream.close();
            dataOutputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
