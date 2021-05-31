package Meal;

import Decorator.ComboMealDecorator;
import Appetizer.Appetizer;
import Drinks.Drinks;
import Pizza.Pizza;

public class ComboMeal extends ComboMealDecorator {
  public ComboMeal(Pizza pizzaDecorator, Appetizer appetizerDecorator, Drinks drinksDecorator) {
      super(pizzaDecorator, appetizerDecorator, drinksDecorator);
  }
  @Override
  public void ShowPizza(){
      super.ShowPizza();
  }
  @Override
  public void ShowDrinks(){
      super.ShowDrinks();
  }
  @Override
  public void ShowAppetizer(){
      super.ShowAppetizer();
  }
  public void ShowPrice(){
      super.comboMealPizza.ShowPrice();
      super.comboMealDrinks.ShowPrice();
      super.comboMealAppetizer.ShowPrice();
  }
  public void ShowComboMeal(){
      ShowPizza();
      ShowDrinks();
      ShowAppetizer();
      ShowPrice();
  }
}
