package Appetizer;

public class FrenchFries implements Appetizer{
    private double price = 100.00;
    public void ShowAppetizer(){
        System.out.println("This is French Fries");
    }
    public void setPrice(double price){
        this.price = price;
    }
    public double getPrice(){
        return price;
    }
    @Override
    public void ShowPrice(){
        System.out.println("Price of French Fries is " + price);
    }
}
