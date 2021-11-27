package rng70.socketprogramming;

import java.util.ArrayList;
import javafx.scene.control.TreeItem;

public class TreeViewHelper
{
    String ItemNodeName;
    ArrayList<String>NeedToConvert;
    public TreeViewHelper(){}
    public TreeViewHelper(String ItemNodeName, ArrayList<String>NeedToConvert) {
        this.ItemNodeName = ItemNodeName;
        this.NeedToConvert = NeedToConvert;
    }

    public TreeItem<String> getItems(){
        ArrayList<TreeItem<String>> convertedList = new ArrayList<>();

        TreeItem<String> list = new TreeItem<>(ItemNodeName);
        for(String s : NeedToConvert){
            convertedList.add(new TreeItem<>(s));
        }

        list.getChildren().addAll(convertedList);
        list.setExpanded(true);
        return list;
    }

    // This method creates an ArrayList of TreeItems (Products)
    public ArrayList<TreeItem<String>> getProducts()
    {
        ArrayList<TreeItem<String>> products = new ArrayList<>();

        TreeItem<String> cars = new TreeItem<>("Cars");
        cars.getChildren().addAll(getCars());
        cars.setExpanded(true);

        TreeItem<String> buses = new TreeItem<>("Buses");
        buses.getChildren().addAll(getBuses());
        buses.setExpanded(true);

        TreeItem<String> trucks = new TreeItem<>("Trucks");
        trucks.getChildren().addAll(getTrucks());
        trucks.setExpanded(true);

        TreeItem<String> motorbikes = new TreeItem<>("Motorcycles");
        motorbikes.getChildren().addAll(getMotorcycles());
        motorbikes.setExpanded(true);

        products.add(cars);
        products.add(buses);
        products.add(trucks);
        products.add(motorbikes);

        return products;
    }

    // This method creates an ArrayList of TreeItems (Cars)
    private ArrayList<TreeItem<String>> getCars()
    {
        ArrayList<TreeItem<String>> cars = new ArrayList<>();

        TreeItem<String> ferrari = new TreeItem<>("Ferrari");
        TreeItem<String> porsche = new TreeItem<>("Porsche");
        TreeItem<String> ford = new TreeItem<>("Ford");
        TreeItem<String> mercedes = new TreeItem<>("Mercedes");

        cars.add(ferrari);
        cars.add(porsche);
        cars.add(ford);
        cars.add(mercedes);

        return cars;
    }

    // This method creates an ArrayList of TreeItems (Buses)
    private ArrayList<TreeItem<String>> getBuses()
    {
        ArrayList<TreeItem<String>> buses = new ArrayList<>();

        TreeItem<String> gm = new TreeItem<>("GM");
        TreeItem<String> vw = new TreeItem<>("VW");
        TreeItem<String> man = new TreeItem<>("MAN");
        TreeItem<String> volvo = new TreeItem<>("Volvo");

        buses.add(gm);
        buses.add(man);
        buses.add(volvo);
        buses.add(vw);

        return buses;
    }

    // This method creates an ArrayList of TreeItems (Trucks)
    private ArrayList< TreeItem<String> > getTrucks()
    {
        ArrayList< TreeItem<String> > trucks = new ArrayList<>();

        TreeItem<String> sony = new TreeItem<>("Sony");
        TreeItem<String> mercedes = new TreeItem<>("Mercedes");
        TreeItem<String> gm = new TreeItem<>("GM");
        TreeItem<String> ford = new TreeItem<>("Ford");

        trucks.add(mercedes);
        trucks.add(sony);
        trucks.add(gm);
        trucks.add(ford);

        return trucks;
    }

    // This method creates an ArrayList of TreeItems (Motorbikes)
    private ArrayList< TreeItem<String> > getMotorcycles()
    {
        ArrayList< TreeItem<String> > motorcycles = new ArrayList<>();

        TreeItem<String> harley = new TreeItem<>("Harley");
        TreeItem<String> suzuki = new TreeItem<>("Suzuki");
        TreeItem<String> ktm = new TreeItem<>("KTM");
        TreeItem<String> honda = new TreeItem<>("Honda");

        motorcycles.add(harley);
        motorcycles.add(honda);
        motorcycles.add(ktm);
        motorcycles.add(suzuki);

        return motorcycles;
    }
}
