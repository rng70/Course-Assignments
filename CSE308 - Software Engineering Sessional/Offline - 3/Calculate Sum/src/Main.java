import Calculator.CalculateSum;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    static boolean checkIsIntParsalbe(String fileName){
        boolean isParsable = true;
        try{
            File file = new File(fileName);
            Scanner fileReader = new Scanner(file);
            String[] nextElement;
            int nextElementIntValue;

            while(fileReader.hasNextLine()){
                nextElement = fileReader.nextLine().split(" ");
                for (String s : nextElement) {
                    try {
                        nextElementIntValue = Integer.parseInt(s);
                    } catch (NumberFormatException e) {
                        isParsable = false;
                        break;
                    }
                }
            }
        } catch(FileNotFoundException e){
            System.out.println("File not found. An error occurred");
            e.printStackTrace();
        }
        return isParsable;
    }
  public static void main(String[] args) {
      CalculateSum calculateSum = new CalculateSum();
      String fileName = "G:\\GitHub Repositories\\Course-Assignments\\CSE 308 - Software Engineering Sessional\\Offline - 3\\Calculate Sum\\src\\input.txt";

      String text;
      System.out.println("Do you want to input as Ascii value?\n\t1. Yes\n\t2. No");
      int choice;
      Scanner scanner = new Scanner(System.in);
      choice = scanner.nextInt();
      if(choice == 1)
          text = "Ascii";
      else
          text = "Txt";
//      if(checkIsIntParsalbe(fileName)){
//          System.out.println("Integer parsable");
//          text = "Txt";
//      }else{
//          System.out.println("Not Integer parsable");
//          text = "Ascii";
//      }

      System.out.println("<== +++++++++++++++++++ =>\nFile considered as a " + text + " file\n<== +++++++++++++++++++ =>\n");
      calculateSum.calculateSum(text, fileName);
  }
}