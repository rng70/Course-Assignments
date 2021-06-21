package Subject;

import java.io.*;
import java.io.FileNotFoundException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class Server implements Subject{
    ServerSocket serverSocket;
    boolean shouldRun = true;
    ArrayList<ServerConnection> connections = new ArrayList<ServerConnection>();


    public static void main(String[] args) {
        readStocks();
        printStocks();
        new Server();
    }
    public Server(){
        try {
            serverSocket = new ServerSocket(3333);
            while(shouldRun) {
                Socket socket = serverSocket.accept();
                ServerConnection serverConnection = new ServerConnection(socket, this);
                serverConnection.start();
                connections.add(serverConnection);
                sendFirstMsgToClient(serverConnection);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void sendFirstMsgToClient(ServerConnection sc){
        sc.sendStocksToAll(allStocks);
    }
    public static void printStocks(){
        for(int i=0;i<allStocks.size();i++){
            System.out.println("Stock Name: "+allStocks.get(i).getStockName());
            System.out.println("Stock Count: "+allStocks.get(i).getStockCount());
            System.out.println("Stock Price: "+allStocks.get(i).getStockPrice());
            System.out.println("<-- ----------------------------------------------- -->");
        }
    }
    public static void readStocks(){
        String filename = "G:\\GitHub Repositories\\Course-Assignments\\CSE 308 - Software Engineering Sessional\\Offline - 4\\Stock Trading Platform\\src\\Subject\\input.txt";

        try{
            File file = new File(filename);
            Scanner scanner = new Scanner(file);

            while(scanner.hasNextLine()){
                String[] line = scanner.nextLine().split(" ");

                Stocks stocks = new Stocks(line[0], Integer.parseInt(line[1]), Double.parseDouble(line[2]));
                allStocks.add(stocks);
            }
        }catch (FileNotFoundException e){
            System.out.println("File not found");
            e.printStackTrace();
        }
    }
    @Override
    public void triggerOperation(char triggerMode, String stockName, double stockPriceOrCount){
        if (triggerMode == 'I' || triggerMode == 'i') {
            for(int i=0;i<allStocks.size();i++){
                allStocks.get(i).setStockPrice(allStocks.get(i).getStockPrice() + stockPriceOrCount);
            }
        }else if(triggerMode == 'D' || triggerMode == 'd'){
            for(int i=0;i<allStocks.size();i++){
                allStocks.get(i).setStockPrice(allStocks.get(i).getStockPrice() - stockPriceOrCount);
            }
        }else if(triggerMode == 'C' || triggerMode == 'c'){
            for(int i=0;i<allStocks.size();i++){
                allStocks.get(i).setStockCount((int) stockPriceOrCount);
            }
        }else{
            System.out.println("Invalid Operation");
        }
    }

    @Override
    public void sendStockToAll(){
    }
}
