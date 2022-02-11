package rng70;

public class Model {
    double p;
    double[][] board;
    int n, m, k;
    public Model(int n, int m, int k){
        this.n = n;
        this.m = m;
        this.k = k;
        this.p = 0.9;

        board = new double[n][m];
    }

    public boolean isCellBlocked(int r, int c){
        return board[r][c] != -1.0;
    }

    public double getEdgeProbability(int r, int c){
        int count = 0;
        if((r-1)>-1 && !isCellBlocked(r-1, c))
            count++;
        if(((r-1)>-1 && (c-1)>-1) && !isCellBlocked(r-1, c-1))
            count++;
        if(((r-1)>-1 && (c+1)<m) && !isCellBlocked(r-1, c+1))
            count++;
        if(((r+1)<n && (c+1)<m) && !isCellBlocked(r+1, c+1))
            count++;
        if(((r+1)<n && (c-1)>-1) && !isCellBlocked(r+1, c-1))
            count++;
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

    public void PrintModel(){
        System.out.println("what the hell is going on");
    }

    public void queryCasperPosition(){
        // TODO
        System.out.println("TODO");
    }
}
