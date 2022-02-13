package rng70;

import java.text.DecimalFormat;

public class Model {
    double p, g;
    double[][] board;
    double[][] evidence;
    double[][] nonNormalizedBoard;
    int n, m, k;

    DecimalFormat df_obj = new DecimalFormat("#.####");
    public Model(int n, int m, int k){
        this.n = n;
        this.m = m;
        this.k = k;
        this.p = 0.9;
        this.g = 0.85;

        board = new double[n][m];
        evidence = new double[n][m];
        nonNormalizedBoard = new double[n][m];

        SetInitialBoard(board);
        SetInitialBoard(evidence);
        SetInitialBoard(nonNormalizedBoard);
    }

    private boolean isCellBlocked(int r, int c){
        return board[r][c] == -1.0;
    }

    private boolean isValidCell(int r, int c){
        return (r >= 0 && r < n) && (c >= 0 && c < m);
    }

    private double getCornerProbability(int r, int c){
        int count = 1;

        if(((r-1)>-1 && (c-1)>-1) && !isCellBlocked(r-1, c-1))
            count++;
        if(((r-1)>-1 && (c+1)<m) && !isCellBlocked(r-1, c+1))
            count++;
        if(((r+1)<n && (c+1)<m) && !isCellBlocked(r+1, c+1))
            count++;
        if(((r+1)<n && (c-1)>-1) && !isCellBlocked(r+1, c-1))
            count++;

        return (1-p) / (double) count;
    }

    public void InitialBoardStatus(){
        System.out.println("\n\n[A " + n + "X" + m + " grid where each cell without obstacle has a probability value = 1/" + (n*m-k) + ", Each cell with obstacle has a probability value = 0.]");
    }

    public double getEdgeProbability(int r, int c){
        int count = 0;
        if((r-1)>-1 && !isCellBlocked(r-1, c))
            count++;
        if((r+1)<n && !isCellBlocked(r+1, c))
            count++;
        if((c-1)>-1 && ! isCellBlocked(r, c-1))
            count++;
        if((c+1)<m && !isCellBlocked(r, c+1))
            count++;
        
        // TODO need to check if the count is 0
        if(count == 0)
            return 0;
        return p / (double) count;
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
        System.out.println("<++++++++++++++++++++++++++++++++++>");
        System.out.println("Hidden Markov Model");
        double sum = 0.0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                System.out.print(df_obj.format(board[i][j]) + " ");
                sum += board[i][j];
            }
            System.out.println();
        }
        System.out.println("Total Probability is : "+ df_obj.format(sum));
        System.out.println("<++++++++++++++++++++++++++++++++++>\n");

    }

    public void SetInitialBoard(int value){
        double pValue = 1.0 / (value * 1.0);
        for (int i=0 ;i<n;i++){
            for (int j=0;j<m;j++) {
                if (board[i][j] != -1.0) {
                    board[i][j] = pValue;
                }
            }
        }
    }

    public void PrintEvidence(){
        System.out.println("<++++++++++++++++++++++++++++++++++>");
        System.out.println("Evidence matrix");
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                System.out.print(evidence[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println("<++++++++++++++++++++++++++++++++++>\n");
    }

    public double GetCornerCumulativeProb(int r, int c){
        double cProb = 0.0;
        if(isValidCell(r-1, c-1)){
            if(!isCellBlocked(r-1, c-1)){
                cProb += board[r-1][c-1] * getCornerProbability(r, c);
            }
        }
        if(isValidCell(r-1, c+1)){
            if(!isCellBlocked(r-1, c+1)){
                cProb += board[r-1][c+1] * getCornerProbability(r, c);
            }
        }
        if(isValidCell(r+1, c-1)){
            if(!isCellBlocked(r+1, c-1)){
                cProb += board[r+1][c-1] * getCornerProbability(r, c);
            }
        }
        if(isValidCell(r+1, c+1)){
            if(!isCellBlocked(r+1, c+1)){
                cProb += board[r+1][c+1] * getCornerProbability(r, c);
            }
        }
        // special case: own cell
        if(isValidCell(r, c)){
            if(!isCellBlocked(r, c)){
                cProb += board[r][c] * getCornerProbability(r, c);
            }
        }

        return cProb;
    }

    public double GetAdjCumulativeProb(int r, int c){
        double cProb = 0.0;
        if(isValidCell(r-1, c)){
            if(!isCellBlocked(r-1, c)){
                cProb += board[r-1][c] * getEdgeProbability(r, c);
            }
        }
        if(isValidCell(r+1, c)){
            if(!isCellBlocked(r+1, c)){
                cProb += board[r+1][c] * getEdgeProbability(r, c);
            }
        }
        if(isValidCell(r, c-1)){
            if(!isCellBlocked(r, c-1)){
                cProb += board[r][c-1] * getEdgeProbability(r, c);
            }
        }
        if(isValidCell(r, c+1)){
            if(!isCellBlocked(r, c+1)){
                cProb += board[r][c+1] * getEdgeProbability(r, c);
            }
        }
        return cProb;
    }

    public void UpdateEvidenceMatrix(int r, int c, int b){
        double prob;
        if(b==1){
            prob = g;
        }else {
            prob = 1 - g;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
               if(i==r || i==(r-1) || i==(r+1)){
                   if(j==c || j==(c-1) || j==(c+1)){
                        evidence[i][j] = prob;
                   }else{
                       evidence[i][j] = 1-prob;
                   }
               }else{
                   evidence[i][j] = 1-prob;
               }
            }
        }
    }
    public void Normalize(double[][] tempBoard, double sum){
        for(int i=0;i<tempBoard.length;i++){
            for(int j=0;j<tempBoard[i].length;j++){
                board[i][j] = tempBoard[i][j]/sum;
            }
        }
    }

    public void ProcessModel(int a, int b, int c){
        double sum = 0.0;
        UpdateEvidenceMatrix(a, b, c);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!isCellBlocked(i, j)){
                    double value = GetAdjCumulativeProb(i, j) + GetCornerCumulativeProb(i, j);
                    nonNormalizedBoard[i][j]=value*evidence[i][j];
                    sum += nonNormalizedBoard[i][j];
                }
            }
        }
        Normalize(nonNormalizedBoard, sum);
        PrintBoard();
    }

    public void QueryCasperPosition(){
        // TODO
        PrintBoard();
        int maxR = -1, maxC = -1;
        double maxP = board[0][0];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){

                if(board[i][j] > maxP){
//                    System.out.print(df_obj.format(board[i][j]) + " > " + df_obj.format(maxP) + " = true");
                    maxR = i;
                    maxC = j;
                    maxP = board[i][j];
                }
            }
        }
        System.out.println("[Casper is most probably at (" + (maxR+1) + "," + (maxC) + ") [assuming it has the highest probability value among the cells]]");
    }
}
