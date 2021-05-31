package Decorator;

import Appetizer.Appetizer;

public abstract class AppetizedDecorator implements Appetizer {
    protected Appetizer decoratedAppetizer;
    public AppetizedDecorator(Appetizer decoratedAppetizer){
        this.decoratedAppetizer = decoratedAppetizer;
    }
    @Override
    public void ShowAppetizer(){
        decoratedAppetizer.ShowAppetizer();
    }
}
