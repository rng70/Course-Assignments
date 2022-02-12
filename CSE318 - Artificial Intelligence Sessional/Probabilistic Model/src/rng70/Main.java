package rng70;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    // write your code here
        System.out.println("Nothing is good here!!!");
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

        /**
         * @brief initial probability of each cell of the board
         * will be same as 1/(n*m-k) where k is the cell with
         * obstacle where Casper cannot stay
         */
        model.SetInitialBoard(n*m-k);

        String s;
        while(true){
            s = scanner.nextLine();
            if(s.charAt(0)=='Q' || s.charAt(0)=='q'){
                break;
            }
            if(s.charAt(0)=='C' || s.charAt(0)=='c'){
                model.queryCasperPosition();
            }else if(s.charAt(0)=='R' || s.charAt(0)=='r'){
                String[] arrOfStr = s.split(" ");
                model.ProcessModel(Integer.parseInt(arrOfStr[1]), Integer.parseInt(arrOfStr[2]), Integer.parseInt(arrOfStr[3]));
            }
        }
    }
}
