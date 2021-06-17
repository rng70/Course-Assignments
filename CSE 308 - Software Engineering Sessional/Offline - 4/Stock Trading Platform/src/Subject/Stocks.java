package Subject;

public class Stocks {
    private int stockCount;
    private double stockPrice;

    public Stocks(int stockCount, double stockPrice){
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
}
