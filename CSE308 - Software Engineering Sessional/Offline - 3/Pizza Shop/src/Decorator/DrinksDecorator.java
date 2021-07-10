package Decorator;

import Drinks.Drinks;

public abstract class DrinksDecorator implements Drinks {
    protected Drinks decoratedDrinks;
    public DrinksDecorator(Drinks decoratedDrinks){
        this.decoratedDrinks = decoratedDrinks;
    }

    @Override
    public void ShowDrinks(){
        decoratedDrinks.ShowDrinks();
    }
}
