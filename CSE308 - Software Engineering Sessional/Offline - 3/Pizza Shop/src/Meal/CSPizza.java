package Meal;

import Decorator.PizzaDecorator;
import Pizza.Pizza;

public class CSPizza extends PizzaDecorator {
    public CSPizza(Pizza pizza){
        super(pizza);
    }
    @Override
    public void ShowPrice(){
        super.ShowPrice();
    }
    @Override
    public void ShowPizzaDecorator(){
        super.ShowPizzaDecorator();
    }
}
