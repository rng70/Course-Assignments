package Subject;

public class Stocks {
    private int stockCount;
    private final String stockName;
    private double stockPrice;

    public Stocks(String stockName, int stockCount, double stockPrice){
        this.stockName = stockName;
        this.stockCount = stockCount;
        this.stockPrice = stockPrice;
    }

    public int getStockCount(){
        return this.stockCount;
    }

    public double getStockPrice(){
        return this.stockPrice;
    }

    public void setStockCount(int stockCount){
        this.stockCount = stockCount;
    }
    public void setStockPrice(double stockPrice){
        this.stockPrice = stockPrice;
    }
    public String getStockName(){
        return this.stockName;
    }
}
