package Subject;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

public class ServerConnection extends Thread{
    Socket socket;
    Server server;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;
    boolean shouldRun = true;
    public static ArrayList<String> stockName = new ArrayList<>();
    public static ArrayList<ServerConnection> serverConnectionArrayList = new ArrayList<>();

    /* ********************************************** */
    /*                                                */
    /*         Main server connection thread          */
    /*                                                */
    /* ********************************************** */
    public ServerConnection(Socket socket, Server server){
        super("Server Connection Thread");
        this.socket = socket;
        this.server = server;
    }

    /* ********************************************** */
    /*                                                */
    /* After every trigger operation a message to the */
    /*  Subscriber is needed to be sent which is done */
    /*                 by this method                 */
    /*                                                */
    /* ********************************************** */
    public void sendStocksToAll(ArrayList<Stocks> stocks){
        try {
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            dataOutputStream.writeUTF("Currently Available Stocks:");
            dataOutputStream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
        for(int i=0;i<stocks.size();i++){
            try {
                dataOutputStream.writeUTF(stocks.get(i).getStockName() + " " + stocks.get(i).getStockCount() + " " + stocks.get(i).getStockPrice());
                dataOutputStream.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /* ********************************************** */
    /*                                                */
    /*   Method to get socket fo server connections   */
    /*                                                */
    /* ********************************************** */
    public Socket getSocket(){
        return this.socket;
    }

    /* ********************************************** */
    /*                                                */
    /*  The process of Subscription is handled here   */
    /*                                                */
    /* ********************************************** */
    public void sendStringToClient(ServerConnection sc, String text){
        String outputText = "";
        boolean isSubscribed = false;
        String[] input = text.split(" ");
        if(input[0].equalsIgnoreCase("s")){
            for(int i=0;i<stockName.size();i++){
                if(stockName.get(i).equalsIgnoreCase(input[1]) && serverConnectionArrayList.get(i) == sc){
                    outputText = "Already Subscribed";
                    isSubscribed = true;
                    break;
                }
            }
            if(!isSubscribed){
                outputText = "Successfully Subscribed to " + input[1];
                stockName.add(input[1]);
                serverConnectionArrayList.add(sc);
            }
        }else if(input[0].equalsIgnoreCase("u")){
            for(int i=0;i<stockName.size();i++){
                if(stockName.get(i).equalsIgnoreCase(input[1]) && serverConnectionArrayList.get(i) == sc){
                    outputText = "Unsubscribed Successful";
                    stockName.remove(i);
                    serverConnectionArrayList.remove(i);
                    isSubscribed = true;
                    break;
                }
            }
            if(!isSubscribed){
                outputText = "You are not subscribed in " + input[1];
            }
        }
        try {
            dataOutputStream.writeUTF(outputText);
            dataOutputStream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run(){
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            while (shouldRun){
                while(dataInputStream.available()==0){
                    try {
                        Thread.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                String textIn = dataInputStream.readUTF();
                sendStringToClient(this, textIn);
            }
            dataInputStream.close();
            dataOutputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
