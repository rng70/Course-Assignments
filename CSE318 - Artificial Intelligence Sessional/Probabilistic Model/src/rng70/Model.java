package rng70;

public class Model {
    double p;
    double[][] board;
    double[][] evidence;
    int n, m, k;
    public Model(int n, int m, int k){
        this.n = n;
        this.m = m;
        this.k = k;
        this.p = 0.9;

        board = new double[n][m];
        evidence = new double[n][m];

        SetInitialBoard(board);
        SetInitialBoard(evidence);
    }

    public boolean isCellBlocked(int r, int c){
        return board[r][c] != -1.0;
    }

    public double getCornerProbability(int r, int c){
        int count = 0;
//        if((r-1)>-1 && !isCellBlocked(r-1, c))
//            count++;
        if(((r-1)>-1 && (c-1)>-1) && !isCellBlocked(r-1, c-1))
            count++;
        if(((r-1)>-1 && (c+1)<m) && !isCellBlocked(r-1, c+1))
            count++;
        if(((r+1)<n && (c+1)<m) && !isCellBlocked(r+1, c+1))
            count++;
        if(((r+1)<n && (c-1)>-1) && !isCellBlocked(r+1, c-1))
            count++;
//        if((r+1)<n && !isCellBlocked(r+1, c))
//            count++;
//        if((c-1)>-1 && ! isCellBlocked(r, c-1))
//            count++;
//        if((c+1)<m && !isCellBlocked(r, c+1))
            count++;

        // TODO need to check if the count is 0
        final double v = (1-p) / (double) count;
        return v;
    }

    public double getEdgeProbability(int r, int c){
        int count = 0;
        if((r-1)>-1 && !isCellBlocked(r-1, c))
            count++;
//        if(((r-1)>-1 && (c-1)>-1) && !isCellBlocked(r-1, c-1))
//            count++;
//        if(((r-1)>-1 && (c+1)<m) && !isCellBlocked(r-1, c+1))
//            count++;
//        if(((r+1)<n && (c+1)<m) && !isCellBlocked(r+1, c+1))
//            count++;
//        if(((r+1)<n && (c-1)>-1) && !isCellBlocked(r+1, c-1))
//            count++;
        if((r+1)<n && !isCellBlocked(r+1, c))
            count++;
        if((c-1)>-1 && ! isCellBlocked(r, c-1))
            count++;
        if((c+1)<m && !isCellBlocked(r, c+1))
            count++;
        
        // TODO need to check if the count is 0
        final double v = p / (double) count;
        return v;
    }

    public double[][] getBoard(){
        return this.board;
    }

    public void SetInitialBoard(double[][] grid){
        for (int i=0 ;i<n;i++){
            for (int j=0;j<m;j++){
                grid[i][j]=0.0;
            }
        }
    }
    public void PrintBoard(){
        System.out.println("Hidden Markov Model");
        double sum = 0.0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                System.out.print(board[i][j] + " ");
                sum += board[i][j];
            }
            System.out.println();
        }
        System.out.println("Total Probability is : "+ sum);
    }

    public void SetInitialBoard(int value){
        double pValue = 1.0 / (value * 1.0);
        for (int i=0 ;i<n;i++){
            for (int j=0;j<m;j++)
                if(board[i][j] != -1.0 )
                    board[i][j] = pValue;
        }

    }

    public void PrintEvidence(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                System.out.print(evidence[i][j]+" ");
            }
            System.out.println();
        }
    }

    public void ProcessModel(int a, int b, int c){

    }

    public void queryCasperPosition(){
        // TODO
        System.out.println("TODO");
    }
}
