package rng70.socketprogramming;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
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
import java.util.ArrayList;
import java.util.Locale;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ClientGUIController {
    Socket socket = null;
    Socket uploadSocket = null;
    Socket downloadSocket = null;

    DataInputStream dataInputStream = null;
    DataOutputStream dataOutputStream = null;
    PrintWriter printer = null;
    BufferedReader scanner = null;

    String fileToUpload = null;

    private int uPort, dPort;
    String serverIPAddress, serverPortNo, sID, sName;

    @FXML
    private TreeView treeViewFiles, listOfStudent;

    @FXML
    private TextField uploadFileName, serverIP, portNo, idToSeeFiles, downloadFilePath, uploadMode, requestFileText;

    @FXML
    private TextArea errors, notifications;

    @FXML
    private RadioButton publicRB, privateRB, myIDToSeeFiles;

    private ExecutorService uploadPool = Executors.newFixedThreadPool(10);

    @FXML
    public void ActionToChooseFileToUpload(ActionEvent event) {
        // Initialize File Chooser
        FileChooser fc = new FileChooser();

        File file = fc.showOpenDialog(null);

        if (file == null) {
            //popUP();
            System.out.println("Invalid file");
        } else {
            uploadFileName.setText(file.getAbsolutePath());
            fileToUpload = file.getAbsolutePath();
        }
    }

    private void generateStreams() {
        try {
            socket = new Socket(serverIPAddress, Integer.parseInt(serverPortNo));

            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            scanner = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            printer = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
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

    public boolean isValidServerIP(String ip) {
        if (!ip.equals("localhost")) {
            String[] arr = ip.split("\\.", -2);
            if (arr.length == 4) {
                for (String s : arr) {
                    if (!(isParsable(s) && ((Integer.parseInt(s) >= 0) && (Integer.parseInt(s) < 256)))) {
                        errors.setText("error~: Invalid IP address: `" + ip + "` is not a valid IP address. Check the IP address of remote host and try again");
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
        return true;
    }

    public void errorPopUp(String error) {
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
        dialogVbox.setStyle("-fx-background-color:WHITE");
        dialog.show();

        okButton.setOnMouseClicked(mouseEvent -> {
            dialog.close();
        });
        closeButton.setOnMouseClicked(mouseEvent -> {
            dialog.close();
        });
    }

    /* ************************* */
    /* This function is to show  */
    /*  Server Connection popup  */
    /*      window to user       */
    /* ************************* */
    public void popUp() {
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
            sID = studentIDField.getText();
            sName = studentNameField.getText();
            if (sID.equals("")) {
                errorPopUp("Student ID is required.\n This field cannot be null");
            } else {
                printer.println(sID);
                printer.println(sName);
                dialog.close();
                try {
                    uPort = Integer.parseInt(scanner.readLine());
                    dPort = Integer.parseInt(scanner.readLine());
                    uploadSocket = new Socket(serverIPAddress, uPort);
                    downloadSocket = new Socket(serverIPAddress, dPort);
                } catch (IOException e) {
                    errors.setText("error~: Invalid Upload/Download Port:  Remote host refusing to connect at upload or download listening port. Check the IP address of remote host and try again");
                }
            }
        });
    }

/*    public void SetToTextAreaError(String s){
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
//    } */

    public void ActionToConnectServer(ActionEvent actionEvent) {
        serverIPAddress = serverIP.getText().toLowerCase();
        serverPortNo = portNo.getText();

        if (serverIPAddress.equals("")) {
            errors.setText("error~: Invalid IP address:  IP address of remote host cannot be null. Check the IP address of remote host and try again");
        } else if (serverPortNo.equals("")) {
            errors.setText("error~: Invalid Port No: Port number cannot be null. Check the IP address of remote host and listening ports and try again");
        } else {
            if ((isValidServerIP(serverIPAddress) && isParsable(serverPortNo) && ((Integer.parseInt(serverPortNo) > 0) && (Integer.parseInt(serverPortNo) < 65536)))) {
                try {
                    generateStreams();
                    String serverResponse = scanner.readLine();

                    if (serverResponse.equalsIgnoreCase("Connection Established: Please send your Student ID")) {
                        popUp();
                    }
                } catch (UnknownHostException e) {
                    errors.setText("error~: Unknown Host: Host IP address is unknown. Check the ip address is valid and remote host is up");
                    errors.setText(String.valueOf(e));
                } catch (ConnectException e) {
                    errors.appendText("error~: Connection Refused: Remote host is refusing to connect. Check the port is valid and the remote host is up");
                    errors.appendText(String.valueOf(e));
                } catch (IOException e) {
                    errors.setText("error~: Unknown Error: Unknown IO error occurred. Check the port is valid and the remote host is up");
                    errors.setText(String.valueOf(e));
                }
            } else {
                if (isValidServerIP(serverIPAddress)) {
                    errors.setText("error~: Invalid Port No: `" + serverPortNo + "` is not a valid port number. Check the IP address of remote host and listening ports and try again");
                }
            }
        }
    }

    public void ActionToShowActiveStudentList(ActionEvent actionEvent) throws IOException{
        dataOutputStream.writeUTF("ShowActiveStudentList");
        dataOutputStream.flush();
        SetToTreeView(ShowList());
    }

    public void SetToTreeView(TreeItem<String>... tree){
        // Create the Root TreeItem
        TreeItem rootItem = new TreeItem("Students");

        // Add children to the root
        for(TreeItem<String> p : tree){
            rootItem.getChildren().add(p);
        }

        // Set the Root Node
        rootItem.setExpanded(true);
        listOfStudent.setShowRoot(true);
        listOfStudent.setRoot(rootItem);
    }

    public void ActionToShowAllStudentList(ActionEvent actionEvent) throws IOException {
        dataOutputStream.writeUTF("ShowActiveStudentList");
        dataOutputStream.flush();
        TreeItem<String> t1 = ShowList();
        dataOutputStream.writeUTF("ShowAllStudentList");
        dataOutputStream.flush();
        TreeItem<String> t2 =ShowList();

        SetToTreeView(t1, t2);
    }

    private TreeItem<String> ConvertToTreeItem(String nodeName, ArrayList<String> nodeItems){
        TreeViewHelper treeViewHelper = new TreeViewHelper(nodeName, nodeItems);

        return treeViewHelper.getItems();
    }

    private TreeItem<String> ShowList() {
        String nodeName = null;
        ArrayList<String> studentList = new ArrayList<>();
        try {
            while(nodeName == null){
                if(dataInputStream.available() > 0){
                    nodeName = dataInputStream.readUTF();
                }
            }
            int size = dataInputStream.readInt();

            while(dataInputStream.available() < 0){
                System.out.println("Data not available");
            }
            for (int i = 0; i < size; i++) {
                String s = dataInputStream.readUTF();
                studentList.add(s);
                System.out.println(s);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return ConvertToTreeItem(nodeName, studentList);
    }

    private TreeItem<String> ShowList(String pathName, String nodeName) throws IOException{
        dataOutputStream.writeUTF(pathName);
        dataOutputStream.flush();
        String tmp = null;
        ArrayList<String> studentList = new ArrayList<>();
        try {
            while(tmp == null){
                if(dataInputStream.available() > 0){
                    tmp = dataInputStream.readUTF();
                    System.out.println(tmp);
                }
            }
            int size = dataInputStream.readInt();
            System.out.println("Size <<---->>" + size);

            while(dataInputStream.available() < 0){
                System.out.println("Data not available");
            }
            for (int i = 0; i < size; i++) {
                String s = dataInputStream.readUTF();
                studentList.add(s);
                System.out.println(s);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return ConvertToTreeItem(nodeName, studentList);
    }

    private TreeItem<String> ShowDirectories(String pathName, String nodeName) throws IOException {
        dataOutputStream.writeUTF(pathName);
        dataOutputStream.flush();
        String tmp = null;
        ArrayList<String> studentList = new ArrayList<>();
        try {
            while (tmp == null) {
                if (dataInputStream.available() > 0) {
                    tmp = dataInputStream.readUTF();
                    System.out.println(tmp);
                }
            }
            int size = dataInputStream.readInt();
//            System.out.println("Size <<---->>" + size);

            while (dataInputStream.available() < 0) {
                System.out.println("Data not available");
            }
            for (int i = 0; i < size; i++) {
                String s = dataInputStream.readUTF();
                studentList.add(s);
//                System.out.println(s);
            }

            for(int i=0;i<studentList.size();i++){
                dataOutputStream.writeUTF(pathName + "/" + studentList.get(i));
                dataOutputStream.flush();
                tmp = null;
                ArrayList<TreeItem<String>> directoryListsTree = new ArrayList<>();
                ArrayList<String> pq = new ArrayList<>();
                try {
                    while (tmp == null) {
                        if (dataInputStream.available() > 0) {
                            tmp = dataInputStream.readUTF();
                            System.out.println(tmp);
                        }
                    }
                    size = dataInputStream.readInt();
//            System.out.println("Size <<---->>" + size);

                    while (dataInputStream.available() < 0) {
                        System.out.println("Data not available");
                    }
                    for (int j = 0; j < size; j++) {
                        String s = dataInputStream.readUTF();
                        pq.add(s);
                    }
                    directoryListsTree.add(ConvertToTreeItem(studentList.get(i), pq));
                    pq.clear();
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }catch (IOException e){
            e.printStackTrace();
        }

        return ConvertToTreeItem(nodeName, studentList);
    }

    public void ActionToShowFiles(ActionEvent actionEvent) throws IOException{
        String id = idToSeeFiles.getText();
        boolean t1 = myIDToSeeFiles.isSelected(), t2 = publicRB.isSelected(), t3 = privateRB.isSelected();

        ArrayList<TreeItem<String>> arrayList = new ArrayList<>();
        TreeItem rootItem = new TreeItem("Files");
        TreeItem interMediateItem1=null, intermediateItem2=null;

        if(!sID.equals("")){
            t1 |= id.equals(sID);
        }

        if(!t2 && !t3){
            errorPopUp("Selection mode error: \nSelect Private or Public");
        } else if(!t1 && t3){
            errorPopUp("You Cannot See Private \n files of " + id);
        } else{
            System.out.println("Here");
            if(t1){
                 interMediateItem1 = new TreeItem(id);
                 ArrayList<TreeItem<String>> treeItems = new ArrayList<>();
                 String pathName;
                if(t2){
                    pathName = "ShowFiles ./" + id + "/public";
                    treeItems.add(ShowList(pathName, "Public"));
                }
                if(t3){
                    pathName = "ShowFiles ./" + id + "/private";
                    treeItems.add(ShowList(pathName, "Private"));
                }
                interMediateItem1.getChildren().addAll(treeItems);
            }else{
                intermediateItem2 = new TreeItem(id);
                String pathName = "ShowFiles ./" + id+"/public";
                intermediateItem2.getChildren().add(arrayList.add(ShowList(pathName, "Public")));
            }
        }
        if(interMediateItem1 != null)
            arrayList.add(interMediateItem1);
        if(intermediateItem2 != null)
            arrayList.add(intermediateItem2);

        rootItem.getChildren().addAll(arrayList);
        rootItem.setExpanded(true);
        treeViewFiles.setShowRoot(true);
        treeViewFiles.setRoot(rootItem);

    }

    public void ActionToUploadFiles(ActionEvent actionEvent) throws IOException{
        String s = uploadMode.getText().toLowerCase();
        if (fileToUpload == null) {
            errorPopUp("Cannot upload null file");
            System.out.println("Wrong file");
        } else {
            dataOutputStream.writeUTF("SendingFile " + s);
            dataOutputStream.flush();

            ClientUploadThread clientUploadThread = new ClientUploadThread(uploadSocket, fileToUpload);
            uploadPool.execute(clientUploadThread);
        }
    }

    public void ActionToDownloadFiles(ActionEvent actionEvent) throws IOException{
        String dFileName = downloadFilePath.getText();
        dataOutputStream.writeUTF("DownloadFile " + dFileName);
        dataOutputStream.flush();
        ClientDownloadThread clientDownloadThread = new ClientDownloadThread(downloadSocket, dFileName);
        uploadPool.execute(clientDownloadThread);
    }

    public void requestForFile(ActionEvent actionEvent) throws IOException{
        String dFileName = requestFileText.getText();
        dataOutputStream.writeUTF("RequestFile " + dFileName);
        dataOutputStream.flush();
    }

    public void notificationShowButton(ActionEvent actionEvent) {
        printer.println("ShowNotifications");
        ShowList();
    }

    public void ActionToLogOut(ActionEvent event) throws IOException{
        dataOutputStream.writeUTF("LogOut");
        Platform.exit();
    }
}