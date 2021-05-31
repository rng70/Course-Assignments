package Decorator;
import Pizza.Pizza;
import Appetizer.Appetizer;
public abstract class MealDecorator implements Pizza, Appetizer{
    protected Pizza decoratedPizza;
    protected Appetizer decoratedAppetizer;
    public MealDecorator(Pizza decoratedPizza, Appetizer decoratedAppetizer){
        this.decoratedPizza = decoratedPizza;
        this.decoratedAppetizer = decoratedAppetizer;
    }
    @Override
    public void ShowPizza(){
        decoratedPizza.ShowPizza();
    }
    @Override
    public void ShowAppetizer(){

        decoratedAppetizer.ShowAppetizer();
    }

}
