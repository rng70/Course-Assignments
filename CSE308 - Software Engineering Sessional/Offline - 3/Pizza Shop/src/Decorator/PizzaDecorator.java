package Decorator;

import Pizza.Pizza;

public abstract class PizzaDecorator implements Pizza {
    protected Pizza decoratePizza;
    public PizzaDecorator(Pizza decoratePizza){
        this.decoratePizza = decoratePizza;
    }
    @Override
    public void ShowPizza(){
        decoratePizza.ShowPizza();
    }
    @Override
    public void ShowPrice(){
        decoratePizza.ShowPrice();
    }
    public void ShowPizzaDecorator(){
        ShowPizza();
        ShowPrice();
    }
}
