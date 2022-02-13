package rng70;

import java.text.DecimalFormat;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        DecimalFormat df_obj = new DecimalFormat("#.###");
        System.out.println("Please enter the input");

        int n, m, k;
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();

        Model model = new Model(n, m, k);
        double[][] board = model.getBoard();

        int r, c;
        for(int i=0;i<k;i++){
            r = scanner.nextInt();
            c = scanner.nextInt();
            board[r][c] = -1.0;
        }

        /*
         * initial probability of each cell of the board
         * will be same as 1/(n*m-k) where k is the cell with
         * obstacle where Casper cannot stay
         */
        model.SetInitialBoard(n*m-k);
        model.InitialBoardStatus();

        String s;
        int counter = 0;
        while(true){
            s = scanner.nextLine();
            if(s.length()>0){
                if(s.charAt(0)=='Q' || s.charAt(0)=='q'){
                    break;
                }
                if(s.charAt(0)=='C' || s.charAt(0)=='c'){
                    model.QueryCasperPosition();
                }else if(s.charAt(0)=='R' || s.charAt(0)=='r'){
                    counter++;
                    String[] arrOfStr = s.split(" ");

                    System.out.println("Probability Update (" + counter + "-th Reading):");
                    String str;
                    if(Integer.parseInt(arrOfStr[3])==1){
                        str = "[The probabilities of the cells around ("+Integer.parseInt(arrOfStr[1])+ ", " + Integer.parseInt(arrOfStr[2]) + ") will increase while those of others may decrease.]";
                    }else{
                        str = "[The probabilities of the cells around ("+Integer.parseInt(arrOfStr[1])+ ", " + Integer.parseInt(arrOfStr[2]) + ") will decrease while those of others may increase.]";
                    }
                    System.out.println(str);
                    model.ProcessModel(Integer.parseInt(arrOfStr[1]), Integer.parseInt(arrOfStr[2]), Integer.parseInt(arrOfStr[3]));
                }
            }
        }
    }
}
