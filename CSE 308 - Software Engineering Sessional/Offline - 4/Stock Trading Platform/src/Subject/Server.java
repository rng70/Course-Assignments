package Subject;

import java.io.*;
import java.io.FileNotFoundException;
import java.net.ServerSocket;
import java.util.Scanner;

public class Server implements Subject{
    Stocks stocks;
    ServerSocket serverSocket;

    public static void main(String[] args) {
        new Server();
    }
    public Server(){
        try {
            serverSocket = new ServerSocket(3333);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }
    @Override
    public void readStocks(){
        String filename = "./input.txt";

        try{
            File file = new File(filename);
            Scanner scanner = new Scanner(file);

            while(scanner.hasNextLine()){
                String[] line = scanner.nextLine().split(" ");

                stocks = new Stocks(line[0], Integer.parseInt(line[1]), Double.parseDouble(line[2]));
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
