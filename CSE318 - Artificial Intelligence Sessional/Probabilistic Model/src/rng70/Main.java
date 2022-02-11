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

        String s;
        while(true){
            s = scanner.nextLine();
            if(s.charAt(0)=='Q'){
                break;
            }
            if(s.charAt(0)=='C'){
                model.queryCasperPosition();
            }
        }

//        int age = 14;
//        assert age <= 18 : "Cannot Vote";
//        System.out.println("The voter's age is " + age);


    }
}
