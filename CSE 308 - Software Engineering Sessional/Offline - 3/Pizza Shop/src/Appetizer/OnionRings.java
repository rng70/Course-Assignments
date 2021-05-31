package Appetizer;

public class OnionRings implements Appetizer{
    private double price = 100.00;
    @Override
    public void ShowAppetizer(){
        System.out.println("This is Onion Rings");
    }
    public void setPrice(double price){
        this.price = price;
    }
    public double getPrice(){
        return price;
    }
    @Override
    public void ShowPrice(){
        System.out.println("Price of Onion Rings is " + price);
    }
}
