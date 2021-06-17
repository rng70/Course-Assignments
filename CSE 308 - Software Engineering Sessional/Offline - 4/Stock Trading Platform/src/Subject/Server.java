package Subject;

import java.io.*;
import java.io.FileNotFoundException;
import java.util.Scanner;
import Subject.Stocks;

public class Server implements Subject{
    Stocks stocks;

    @Override
    public void readStocks(){
        String filename = "./input.txt";

        try{
            File file = new File(filename);
            Scanner scanner = new Scanner(file);

            while(scanner.hasNextLine()){
                String[] line = scanner.nextLine().split(" ");

                stocks = new Stocks(Integer.parseInt(line[1]), Double.parseDouble(line[2]));
                allStocks.put(line[0], stocks);

            }

        }catch (FileNotFoundException e){
            System.out.println("File not found");
            e.printStackTrace();
        }
    }
    @Override
    public void triggerOperation(char triggerMode){
        if (triggerMode == 'I' || triggerMode == 'i') {
            System.out.println("Found I");
        }else if(triggerMode == 'D' || triggerMode == 'd'){
            System.out.println("Found D");
        }else if(triggerMode == 'C' || triggerMode == 'c'){
            System.out.println("Found C");
        }else{
            System.out.println("Invalid Operation");
        }
    }

    @Override
    public void sendStockToAll(){

    }
}
