import Appetizer.*;
import Meal.*;
import Pizza.*;
import Drinks.*;

public class MealPack {
    Meal meal = null;
    ComboMeal comboMeal = null;
    CSPizza pizza = null;
    public MealPack(int choice){
        if(choice > 0 && choice < 3){
            if(choice == 1){
                meal = new Meal(new BeefPizza(), new FrenchFries());
            }else{
                meal = new Meal(new VeggiPizza(), new OnionRings());
            }
        }else{
            if(choice == 3){
                comboMeal = new ComboMeal(new VeggiPizza(), new FrenchFries(), new Coke());
            }else if(choice == 4){
                comboMeal = new ComboMeal(new VeggiPizza(), new OnionRings(), new Coffee());
            }else{
                pizza = new CSPizza(new BeefPizza());
            }
        }
    }
    public void showMeal(int param){
        if(param > 0 && param < 3){
            meal.ShowMeal();
        }else if(param > 2 && param < 5){
            comboMeal.ShowComboMeal();
        }else{
            pizza.ShowPizzaDecorator();
        }
    }

}
