package Observer;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ClientConnection extends Thread{
    Socket socket;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    boolean shouldRun = true;


    public ClientConnection(Socket socket, Client client){
        this.socket = socket;
    }
    public void sendStringToServer(String text){
        try {
            dataOutputStream.writeUTF(text);
            dataOutputStream.flush();
        } catch (IOException e) {
            e.printStackTrace();
            close();
        }
    }

    @Override
    public void run(){
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            while(shouldRun){
                try {
                    while(dataInputStream.available()==0){
                        try {
                            Thread.sleep(1);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    String reply = dataInputStream.readUTF();
                    System.out.println(reply);
                }catch (IOException e){
                    e.printStackTrace();
                    close();
                }
            }
        }catch (IOException e){
            e.printStackTrace();
            close();
        }
    }

    public void close(){

        try {
            dataInputStream.close();
            dataOutputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
