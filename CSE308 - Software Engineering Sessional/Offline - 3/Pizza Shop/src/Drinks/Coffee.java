package Drinks;

public class Coffee implements Drinks{
    @Override
    public void ShowDrinks(){
        System.out.println("This is Coffee");
    }
    @Override
    public void ShowPrice(){
        System.out.println("Price of Coffee is 350.00");
    }
}
