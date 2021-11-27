package rng70.socketprogramming;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class ClientGUIMainThread extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(ClientGUIMainThread.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 1300, 900);
        stage.setTitle("Client Interface");
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args: the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
}