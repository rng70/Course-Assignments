package client;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class client {
    public static void main(String[] args) {
        Socket socket = null;
        try {
            socket = new Socket("127.0.0.1", 6000);
            System.out.println("Client connected");
        } catch (IOException e) {
            e.printStackTrace();
        }

        ObjectInputStream objectInputStream = null;
        ObjectOutputStream objectOutputStream = null;
        if(socket == null){
            System.out.println("Socket Null");
        }
        try{
            assert socket != null;
            System.out.println("Here");
            objectInputStream = new ObjectInputStream(socket.getInputStream());
            objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        }catch(IOException e){
            e.printStackTrace();
        }

        System.out.println("WTF");
        Scanner scanner = new Scanner(System.in);

        String message = scanner.nextLine();
        System.out.println(message);

        try{
//            assert objectInputStream != null;
//            assert objectOutputStream != null;

            objectOutputStream.writeObject(message);
            System.out.println("Object were written");
            String ack = (String) objectInputStream.readObject();

            System.out.println("Received from server"+ ack);
        }catch (IOException | ClassNotFoundException e){
            e.printStackTrace();
        }

    }
}
