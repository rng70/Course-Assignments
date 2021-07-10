import java.util.Scanner;

public class Main {
    static void Menu(){
        System.out.println(
                """
                        Enter Your choice
                        \t1. Beef Pizza with French fry
                        \t2. Veggie Pizza with onion rings\s
                        \t3. A combo meal with Veggie Pizza, French Fry and Coke\s
                        \t4. A combo meal with Veggie Pizza, Onion Rings and Coffee\s
                        \t5. A Beef Pizza only""");
    }
    public static void main(String[] args) {
        Menu();
        int choice;
        Scanner scanner = new Scanner(System.in);
        choice = scanner.nextInt();
        MealPack mealPack = new MealPack(choice);
        mealPack.showPrice(choice);
    }
}
