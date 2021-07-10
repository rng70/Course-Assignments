package IntegerCalculator;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class CalculateInteger {
    private int sum = 0;

    public void calculateIntSum(String fileNameWithPath){
        try{
            File openFile = new File(fileNameWithPath);
            Scanner fileReader = new Scanner(openFile);

            while(fileReader.hasNextInt()){
                sum += fileReader.nextInt();
            }
            fileReader.close();
        }catch(FileNotFoundException e){
            System.out.println("File not found. An error occurred");
            e.printStackTrace();
        }
    }
    public int getIntSum(){
        return sum;
    }

}
