package Subject;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class Server{
    ServerSocket serverSocket;
    boolean shouldRun = true;
    ArrayList<ServerConnection> connections = new ArrayList<>();
    private static ArrayList<Stocks> allStocks = new ArrayList<>();

    public static void main(String[] args) {
        readStocks();
        printStocks();
        new Server();
    }

    /* ********************************************** */
    /*                                                */
    /*                Main server thread              */
    /*                                                */
    /* ********************************************** */
    public Server(){
        try {
            serverSocket = new ServerSocket(3333);
            new ServerReaderThread(connections, allStocks);
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

    /* ********************************************** */
    /*                                                */
    /*    After reading all Stocks from file this     */
    /*   method is used to show the stock lists to    */
    /*                   clients                      */
    /*                                                */
    /* ********************************************** */
    public static void sendFirstMsgToClient(ServerConnection sc){
        sc.sendStocksToAll(allStocks);
    }

    /* ********************************************** */
    /*                                                */
    /*   This method is used to print the available   */
    /*            stocks at the server side           */
    /*                                                */
    /* ********************************************** */
    public static void printStocks(){
        System.out.println("Available Stocks: ");
        for(int i=0;i<allStocks.size();i++){
            System.out.println(allStocks.get(i).getStockName() + " " + allStocks.get(i).getStockCount()
                    + " "+allStocks.get(i).getStockPrice());
        }
        System.out.println("<-- ----------------------------------------------- -->");
    }

    /* ********************************************** */
    /*                                                */
    /*  At the beginning the stocks price need to be  */
    /*  read from a file to show the stock prices to  */
    /*     all the users when they first login        */
    /*                                                */
    /* ********************************************** */
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
}
