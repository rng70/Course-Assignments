package Subject;

import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class ServerReaderThread extends Thread{
    ArrayList<Stocks> allStocks;
    ArrayList<ServerConnection> connections;
    private String msg;

    ServerReaderThread(ArrayList<ServerConnection> connections, ArrayList<Stocks> allStocks){
        this.allStocks = allStocks;
        this.connections = connections;
        new Thread(this).start();
    }

    @Override
    public void run(){
        listenForInput();
    }

    /* ********************************************** */
    /*                                                */
    /*     Main thread to read at server side         */
    /*                                                */
    /* ********************************************** */
    public void listenForInput(){
        Scanner console = new Scanner(System.in);

        while(true){
            while(!console.hasNextLine()){
                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
            String input = console.nextLine();
            msg = input;
            if(input.equalsIgnoreCase("quit")){
                break;
            }
            String[] inputTexts = input.split(" ");
            triggerOperation(inputTexts[0], inputTexts[1], Double.parseDouble(inputTexts[2]));
        }
    }

    /* ********************************************** */
    /*                                                */
    /*  The three trigger operation is given for the  */
    /*    I is given for increase the stock price     */
    /*    D is given for decrease the stock price     */
    /*    C is given for changing the stock count     */
    /*                                                */
    /* ********************************************** */
    public void triggerOperation(String triggerMode, String stockName, double stockPriceOrCount){
        String msg;
        if (triggerMode.equalsIgnoreCase("I")) {
            for(int i=0;i<allStocks.size();i++){
                if(allStocks.get(i).getStockName().equalsIgnoreCase(stockName)){
                    double price = allStocks.get(i).getStockPrice() + stockPriceOrCount;
                    msg = "Stock Price Changed to " + price + " from " + allStocks.get(i).getStockPrice();
                    allStocks.get(i).setStockPrice(allStocks.get(i).getStockPrice() + stockPriceOrCount);
                    sendMsgToSubscribers(connections, msg, stockName);
                }
            }
        }else if(triggerMode.equalsIgnoreCase("D")){
            for(int i=0;i<allStocks.size();i++){
                if(allStocks.get(i).getStockName().equalsIgnoreCase(stockName)){
                    double price = allStocks.get(i).getStockPrice() - stockPriceOrCount;
                    msg = "Stock Price Changed to " + price + " from " + allStocks.get(i).getStockPrice();
                    allStocks.get(i).setStockPrice(allStocks.get(i).getStockPrice() - stockPriceOrCount);
                    sendMsgToSubscribers(connections, msg, stockName);
                }
            }
        }else if(triggerMode.equalsIgnoreCase("C")){
            for(int i=0;i<allStocks.size();i++){
                if(allStocks.get(i).getStockName().equalsIgnoreCase(stockName)){
                    int price = (int) stockPriceOrCount;
                    msg = "Stock Count Changed to " + price + " from " + allStocks.get(i).getStockCount();
                    allStocks.get(i).setStockCount((int) stockPriceOrCount);
                    sendMsgToSubscribers(connections, msg, stockName);
                }
            }
        }else{
            System.out.println("Invalid Operation");
        }
    }

    /* ********************************************** */
    /*                                                */
    /* After every trigger operation a message to the */
    /*  Subscriber is needed to be sent which is done */
    /*                 by this method                 */
    /*                                                */
    /* ********************************************** */
    public void sendMsgToSubscribers(ArrayList<ServerConnection> connections1, String msg, String stockName1){
        for(int i=0;i<connections1.size();i++){
            for(int j=0;j<ServerConnection.serverConnectionArrayList.size();j++){
                if(ServerConnection.serverConnectionArrayList.get(j)==connections1.get(i) && ServerConnection.stockName.get(j).equalsIgnoreCase(stockName1)){
                    try {
                        DataOutputStream dout = new DataOutputStream(connections1.get(i).getSocket().getOutputStream());
                        dout.writeUTF(msg);
                        dout.flush();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public String getString(){
        return msg;
    }
}
