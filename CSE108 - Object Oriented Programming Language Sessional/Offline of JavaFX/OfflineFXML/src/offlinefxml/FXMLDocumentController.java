package offlinefxml;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.FileChooser;
import javafx.stage.FileChooser.ExtensionFilter;

public class FXMLDocumentController implements Initializable { 
    
    private Label label,label2;
   @FXML private Button Button1,Button2;
   @FXML ObservableList<MyDataType>list = FXCollections.observableArrayList();
   @FXML TableView<MyDataType> table = new TableView<>();
   @FXML  private TableColumn<MyDataType,String>wordss ;
   @FXML private TableColumn<MyDataType,Integer>frequent;    
   @FXML  private TextArea filename; 
   ObjectProperty<MyDataType> criticalPerson = new SimpleObjectProperty<>();
   
    public class MyDataType {
    private final int intValue ;
    private final String stringValue ;
    MyDataType(String stringValue,int intValue) {
        this.intValue = intValue ;
        this.stringValue = stringValue ;
    }
    public int getIntValue() {
        return intValue ;
    }
    public String getStringValue() {
        return stringValue ;
    }
}
    
    String path = "\0";
    int total = 0;
    int remain = 0;
    @FXML
    public void Button1Action(ActionEvent event){
	FileChooser fc = new FileChooser();
                    fc.getExtensionFilters().addAll(new ExtensionFilter("Text file","*.txt"));
	File file = fc.showOpenDialog(null);
	
	if(file != null){
	    filename.setText("FileName : " + file.getName() +"\n\nLocation of File :" + file.getAbsolutePath());
                       path  = file.getAbsolutePath();
	}	
	else{
	    System.out.println("File is invalid");
	}
    }      
    @FXML
    public void Button2Action(ActionEvent event) throws IOException{
                    Path pathing = Paths.get(path);
                    System.out.println(path);
                    BufferedReader reader = new BufferedReader(new FileReader(pathing.toFile()));
                    Map<String,Integer>wordfound = new HashMap<>();
                    String line = reader.readLine();
                    total = 0;

          while(line != null){
            if(!line.trim().equals("")){
               String[] words = line.split("[\\W]+");
               for(String word : words){
                   if(word == null || word.trim().equals("")){
                       continue;
                   }
                   else{
                       String processed = word.toLowerCase();
                       processed = processed.replace(","," ");

                       if(wordfound.containsKey(processed)){
                           wordfound.put(processed,wordfound.get(processed)+1);
                       }
                       else {
                           wordfound.put(processed,1);
                           total++;
                       }
                   }
               }
            }
            line = reader.readLine();
        }       
          list.clear();
          wordfound.entrySet().stream().forEach((word) -> {
               MyDataType ob = new MyDataType(word.getKey(),word.getValue());
               list.add(ob);
        });
           MyDataType ob = new MyDataType("Total  Unique Words ",total);
           list.add(ob);
          criticalPerson.set(table.getItems().get(total+remain));
//          remain += total+1;
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        wordss.setCellValueFactory(new PropertyValueFactory<>("stringValue"));
        table.setRowFactory(tv -> {
            TableRow<MyDataType> row = new TableRow<>();
            BooleanBinding critical = row.itemProperty().isEqualTo(criticalPerson).and(row.itemProperty().isNotNull());
            row.styleProperty().bind(Bindings.when(critical)
                .then("-fx-background-color: yellow ;")
                .otherwise(""));
            return row ;
        });       
        frequent.setCellValueFactory(new PropertyValueFactory<>("intValue"));
        table.setItems(list);   
    }      
}
