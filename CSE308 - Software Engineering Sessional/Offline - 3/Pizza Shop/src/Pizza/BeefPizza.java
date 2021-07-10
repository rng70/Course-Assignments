package Pizza;

public class BeefPizza implements Pizza{
    @Override
    public void ShowPizza(){
        System.out.println("This is beef pizza");
    }
    @Override
    public void ShowPrice(){
        System.out.println("Price of Beef Pizza is 750.00");
    }
}
