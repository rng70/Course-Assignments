package Pizza;

public class VeggiPizza implements Pizza{
    @Override
    public void ShowPizza(){
        System.out.println("This is veggie pizza");
    }
    public @Override
    void ShowPrice(){
        System.out.println("Price of Veggie Pizza is 650.00");
    }
}
