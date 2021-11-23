package server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class server {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(6000);
            System.out.println("Server Started");
        } catch (IOException e) {
            e.printStackTrace();
        }

        while(true){
            Socket socket = null;
            try {
                assert serverSocket != null;
                socket = serverSocket.accept();
                System.out.println("Client connected");
            } catch (IOException e) {
                e.printStackTrace();
            }

            ObjectInputStream objectInputStream = null;
            ObjectOutputStream objectOutputStream = null;
            try {
                assert socket != null;
                objectInputStream = new ObjectInputStream(socket.getInputStream());
                objectOutputStream = new ObjectOutputStream(socket.getOutputStream());

            } catch (IOException e) {
                e.printStackTrace();
            }

            try {
                assert objectInputStream != null;
                String message = (String) objectInputStream.readObject();
                System.out.println("Msg from client"+ message);

                assert objectOutputStream != null;
                objectOutputStream.writeObject(message.toUpperCase());
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}
