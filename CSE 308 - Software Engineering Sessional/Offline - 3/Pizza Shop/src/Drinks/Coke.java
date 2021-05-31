package Drinks;

public class Coke implements Drinks{
    @Override
    public void ShowDrinks(){
        System.out.println("This is Coke");
    }
    @Override
    public void ShowPrice(){
        System.out.println("Price of Coke is 200.00");
    }
}
