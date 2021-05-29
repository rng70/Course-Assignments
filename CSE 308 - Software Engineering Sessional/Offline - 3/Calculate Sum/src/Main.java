import Calculator.CalculateSum;

import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
      CalculateSum calculateSum = new CalculateSum();
      String fileName = "G:\\GitHub Repositories\\Course-Assignments\\CSE 308 - Software Engineering Sessional\\Offline - 3\\Calculate Sum\\src\\input.txt";

      System.out.println("Do you want to input as Ascii value?\n\t1. Yes\n\t2. No");
      int choice;
      String text;
      Scanner scanner = new Scanner(System.in);
      choice = scanner.nextInt();
      if(choice == 1)
          text = "Ascii";
      else
          text = "Txt";

      System.out.println("File considered as a " + text + " file");
      calculateSum.calculateSum(text, fileName);
  }
}