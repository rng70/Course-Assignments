package rng70.socketprogramming;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.FileChooser;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.*;
import java.net.ConnectException;
import java.net.Socket;
import java.net.UnknownHostException;

public class HelloController {
    Socket socket = null;
    BufferedReader scanner = null;
    PrintWriter sout = null;
    @FXML
    private TextField uploadFileName, serverIP, portNo;

    @FXML
    private TextArea errors;

    @FXML
    public void ActionToChooseFileToUpload(ActionEvent event) {
        // Initialize File Chooser
        FileChooser fc = new FileChooser();

        File file = fc.showOpenDialog(null);

        if (file == null) {
            //popUP();
            System.out.println("Invalid file");
        } else {;
            uploadFileName.setText(file.getAbsolutePath());
        }
    }

    public boolean isParsable(String input) {
        try {
            Integer.parseInt(input);
            return true;
        } catch (final NumberFormatException e) {
            return false;
        }
    }

    public boolean isValidServerIP(String ip){
        if (!ip.equals("localhost")) {
            String[] arr = ip.split("\\.", -2);
            if(arr.length == 4){
                for(String s: arr){
                    if(!(isParsable(s) && ((Integer.parseInt(s) >= 0) && (Integer.parseInt(s) < 256)))){
                        errors.setText("error~: Invalid IP address: `" + ip + "` is not a valid IP address. Check the IP address of remote host and try again");
                        return false;
                    }
                }
            }else{
                return false;
            }
        }
        return true;
    }

    public void errorPopUp(String error){
        final Stage dialog = new Stage();
        dialog.initModality(Modality.APPLICATION_MODAL);

        Pane dialogVbox = new Pane();

        Text errorMessage = new Text(error);
        errorMessage.setTextAlignment(TextAlignment.CENTER);
        errorMessage.setLayoutX(20);
        errorMessage.setLayoutY(60);
        errorMessage.setFill(Color.RED);
        errorMessage.setStyle("-fx-font-size: 20");

        Button okButton = new Button("Ok");
        Button closeButton = new Button("Cancel");
        okButton.setLayoutX(330);
        okButton.setLayoutY(200);
        closeButton.setLayoutX(250);
        closeButton.setLayoutY(200);

        errorMessage.setLayoutX(100);
        errorMessage.setLayoutY(80);

        dialogVbox.getChildren().addAll(closeButton, okButton, errorMessage);

        Scene dialogScene = new Scene(dialogVbox, 400, 250);
        dialog.setTitle("!!! Fatal error !!!");
        dialog.setScene(dialogScene);
        dialogVbox.setStyle("-fx-background-color:#fffff");
        dialog.show();

        okButton.setOnMouseClicked(mouseEvent -> {
            dialog.close();
        });
        closeButton.setOnMouseClicked(mouseEvent -> {
            dialog.close();
        });
    }

    public void popUp() {

        // Play default sound
//        final Runnable runnable = (Runnable) Toolkit.getDefaultToolkit().getDesktopProperty("win.sound.default");

//        if (runnable != null) {
//            runnable.run();
//        }

        final Stage dialog = new Stage();

        dialog.initModality(Modality.APPLICATION_MODAL);

        Pane dialogVbox = new Pane();

        Text studentID = new Text("Student ID: ");
        studentID.setTextAlignment(TextAlignment.CENTER);
        studentID.setLayoutX(40);
        studentID.setLayoutY(60);
        studentID.setFill(Color.WHITE);
        Text studentName = new Text("Name: ");
        studentName.setTextAlignment(TextAlignment.CENTER);
        studentName.setLayoutX(40);
        studentName.setLayoutY(100);
        studentName.setFill(Color.WHITE);

        Button okButton = new Button("Ok");
        Button closeButton = new Button("Cancel");
        okButton.setLayoutX(330);
        okButton.setLayoutY(200);
        closeButton.setLayoutX(250);
        closeButton.setLayoutY(200);

        TextField studentIDField = new TextField();
        studentIDField.setLayoutX(130);
        studentIDField.setLayoutY(40);
        studentIDField.setPromptText("Student ID");
        TextField studentNameField = new TextField();
        studentNameField.setLayoutX(130);
        studentNameField.setLayoutY(80);
        studentNameField.setPromptText("Name");

        dialogVbox.getChildren().addAll(studentID, studentName, okButton, studentIDField, studentNameField);

        Scene dialogScene = new Scene(dialogVbox, 400, 250);
        dialog.setTitle("Enter Student ID and Name");
        dialog.setScene(dialogScene);
        dialogVbox.setStyle("-fx-background-color:#000000");
        dialog.show();

        okButton.setOnMouseClicked(mouseEvent -> {
            String id = studentIDField.getText();
            String name = studentNameField.getText();
            if(id.equals("")){
                errorPopUp("Student ID is required.\n This field cannot be null");
            }else{
                sout.println(id);
                sout.println(name);
                dialog.close();
            }
        });
//        closeButton.setOnMouseClicked(mouseEvent -> {
//            dialog.close();
//        });
    }

//    public void SetToTextAreaError(String s){
//        TextFlow flow = new TextFlow();
//        String log = ">> Sample passed \n";
//        Text t1 = new Text("error~: Invalid IP address:");
//        t1.setFill(Color.DARKGREEN);
////        errors.setStyle("-fx-text-fill: #1afd01;-fx-font-weight:bold;");
////        errors.appendText("error~: Invalid IP address:");
//        errors.setText(t1);
//        Text t2 = new Text();
////        errors.setStyle("-fx-text-fill: RED;-fx-font-weight:normal;");
//        errors.appendText("  IP address of remote host cannot be null. Check the IP address of remote host and try again");
//        errors.appendText("\n");
////        errors.setText(String.valueOf(Bindings.concat(t1.textProperty().concat(t2.textProperty()))));
//    }

    public void ActionToConnectServer(ActionEvent actionEvent) {
        String serverIPAddress = serverIP.getText().toLowerCase();
        String serverPortNo = portNo.getText();
        if(serverIPAddress.equals("")){
//            errors.setStyle("-fx-text-fill: #ff0000;-fx-font-weight:bold;");
//            t1.setText(log);
            errors.setText("error~: Invalid IP address:  IP address of remote host cannot be null. Check the IP address of remote host and try again");
        }else if(serverPortNo.equals("")){
            errors.setText("error~: Invalid Port No: Port number cannot be null. Check the IP address of remote host and listening ports and try again");
        }else{
            if((isValidServerIP(serverIPAddress) && isParsable(serverPortNo) && ((Integer.parseInt(serverPortNo) > 0) && (Integer.parseInt(serverPortNo) < 65536)))){
                try {
                    socket = new Socket(serverIPAddress, Integer.parseInt(serverPortNo));
                    scanner = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    sout = new PrintWriter(socket.getOutputStream(), true);
                    String serverResponse = scanner.readLine();
                    if(serverResponse.equalsIgnoreCase("Connection Established: Please send your Student ID")){
                        popUp();
                    }
                } catch(UnknownHostException e){
                    errors.setText("error~: Unknown Host: Host IP address is unknown. Check the ip address is valid and remote host is up");
                    errors.setText(String.valueOf(e));
                } catch(ConnectException e){
                    errors.appendText("error~: Connection Refused: Remote host is refusing to connect. Check the port is valid and the remote host is up");
                    errors.appendText(String.valueOf(e));
                } catch (Exception e) {
                    errors.setText("error~: Unknown Error: Unknown IO error occurred. Check the port is valid and the remote host is up");
                    errors.setText(String.valueOf(e));
                }
            }else{
                if(isValidServerIP(serverIPAddress)) {
                    errors.setText("error~: Invalid Port No: `" + serverPortNo + "` is not a valid port number. Check the IP address of remote host and listening ports and try again");
                }
            }
        }
    }

    public void ActionToShowActiveStudentList(ActionEvent actionEvent) {
    }

    public void ActionToShowAllStudentList(ActionEvent actionEvent) {
    }

    public void ActionToShowFiles(ActionEvent actionEvent) {
    }

    public void ActionToUploadFiles(ActionEvent actionEvent) {
    }

    public void notificationShowButton(ActionEvent actionEvent) {
    }
}