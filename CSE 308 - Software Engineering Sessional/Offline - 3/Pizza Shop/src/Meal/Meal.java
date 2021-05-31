package Meal;

import Appetizer.Appetizer;
import Decorator.MealDecorator;
import Pizza.Pizza;

public class Meal extends MealDecorator {
    public Meal(Pizza pizza, Appetizer appetizer){
        super(pizza, appetizer);
    }
    @Override
    public void ShowPizza(){
        super.ShowPizza();
    }
    @Override
    public void ShowAppetizer(){
        super.ShowAppetizer();
    }
    public void ShowPrice(){
        super.decoratedPizza.ShowPrice();
        super.decoratedAppetizer.ShowPrice();
    }
    public void ShowMeal(){
        ShowPizza();
        ShowAppetizer();
        ShowPrice();
    }
}
