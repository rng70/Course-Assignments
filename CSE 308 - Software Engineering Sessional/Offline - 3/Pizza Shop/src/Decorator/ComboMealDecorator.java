package Decorator;

import Appetizer.Appetizer;
import Drinks.Drinks;
import Pizza.Pizza;

public abstract class ComboMealDecorator implements Pizza, Appetizer, Drinks {
    protected Pizza comboMealPizza;
    protected Drinks comboMealDrinks;
    protected Appetizer comboMealAppetizer;

    public ComboMealDecorator(Pizza comboMealPizza, Appetizer comboMealAppetizer, Drinks comboMealDrinks){
        this.comboMealPizza = comboMealPizza;
        this.comboMealDrinks = comboMealDrinks;
        this.comboMealAppetizer = comboMealAppetizer;
    }
    @Override
    public void ShowPizza(){
        comboMealPizza.ShowPizza();
    }
    @Override
    public void ShowDrinks(){
        comboMealDrinks.ShowDrinks();
    }
    @Override
    public void ShowAppetizer(){
        comboMealAppetizer.ShowAppetizer();
    }
}
