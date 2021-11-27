package rng70.server;

import java.io.*;
import java.net.Socket;
import javafx.util.Pair;

import java.text.FieldPosition;
import java.util.Collections;
import java.util.Scanner;
import java.util.ArrayList;
import java.net.ServerSocket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainServerConnectionThread implements Runnable{
    Socket socket;
    Writer output;
    MainServerThread server;
    DataInputStream dataInputStream;
    DataOutputStream dataOutputStream;

    boolean shouldRun = true;
    Socket uploadSocket = null;
    Socket downloadSocket = null;
    BufferedReader scanner = null;
    PrintWriter printWriter = null;
    String studentID, studentName;
    ServerSocket uploadServerSocket, downloadServerSocket;

    public static ArrayList<MainServerConnectionThread> serverConnectionArrayList = new ArrayList<>();
    private static ExecutorService childPool = Executors.newFixedThreadPool(10);


    /* ********************************************** */
    /*                                                */
    /*         Main server connection thread          */
    /*                                                */
    /* ********************************************** */
    public MainServerConnectionThread(MainServerThread server, Socket socket, Writer output, ServerSocket uploadServerSocket, ServerSocket downloadServerSocket) {
        this.socket = socket;
        this.server = server;
        this.output = output;
        this.uploadServerSocket = uploadServerSocket;
        this.downloadServerSocket = downloadServerSocket;
    }

    /* ********************************************** */
    /*                                                */
    /*        Get Socket for the current client       */
    /*                                                */
    /* ********************************************** */
    private Socket getSocket(){
        return this.socket;
    }

    private void makeDirectory(String studentID, String studentName){
        Runtime run = Runtime.getRuntime();
        String cmd;
        try {
            cmd = "mkdir " + studentID;
            run.exec(cmd);
            cmd = "mkdir ./" + studentID + "/private";
            run.exec(cmd);
            cmd = "mkdir ./" + studentID + "/public";
            run.exec(cmd);
            cmd = "touch ./" + studentID + "/notifications.txt";
            run.exec(cmd);

            String nameFile = "./" + studentID + "/fileID.txt";
            File file = new File(nameFile);
            try{
                if(!file.exists()) {
                    file.createNewFile();
                }
            }catch (IOException e){
                e.printStackTrace();
            }
//            file = new File(nameFile);
            Scanner sc = null;
            try{
                sc = new Scanner(file);
            }catch (IOException e){
                e.printStackTrace();
            }
            int index=0;
            while(sc.hasNextLine()){
                index = Integer.parseInt(sc.nextLine());
            }
            Writer myWriter;
            try {
                myWriter = new BufferedWriter(new FileWriter(nameFile));
                myWriter.write(Integer.toString(index));
                myWriter.flush();
                myWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private ArrayList<String> currentAllList(){
        ArrayList<String> list = new ArrayList<>();

        File file = new File("./allStudentList.txt");
        Scanner fileScanner = null;
        try {
            fileScanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        while(fileScanner.hasNextLine()){
            String s = fileScanner.nextLine();
            list.add(s);
        }

        return list;
    }

    public void acceptOrRejectThisConnection(){
        try {
            assert  socket != null;
            printWriter = new PrintWriter(socket.getOutputStream(), true);
            scanner = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        assert printWriter != null;
        printWriter.println("Connection Established: Please send your Student ID");

        try {
            this.studentID = scanner.readLine();
            this.studentName = scanner.readLine();

            if(studentID.equals("")){
                printWriter.println("error~: Connection Closed: remote host closed connection. Provide correct student id and try again");
                socket.close();
            }else{
                String needToAppend = studentID + " " + studentName + "\n";

                if(MainServerThread.activeStudentList.contains(new Pair<>(studentID, studentName))){
                    printWriter.println("error~: Connection Closed: remote host closed connection. Duplicate Student ID found at current session");
                    socket.close();
                }else{
                    MainServerThread.activeStudentList.add(new Pair<>(studentID, studentName));
                    if(!currentAllList().contains(studentID + " " + studentName)) {
                        output.append(needToAppend);
                        output.flush();
                    }

                    printWriter.println(uploadServerSocket.getLocalPort());
                    printWriter.println(downloadServerSocket.getLocalPort());

                    uploadSocket = uploadServerSocket.accept();
                    downloadSocket = downloadServerSocket.accept();

                    makeDirectory(studentID, studentName);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private ArrayList<Pair<String, String>> generateTextList(String fileNameWithPath, boolean checkIf){
        ArrayList<Pair<String, String>> textList = new ArrayList<>();

        File file = new File(fileNameWithPath);
        Scanner fileScanner = null;
        try {
            fileScanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        while(fileScanner.hasNextLine()){
            String[] s = fileScanner.nextLine().split(" ");
            if(checkIf && !(MainServerThread.activeStudentList.contains(new Pair<>(s[0], s[1])))){
                textList.add(new Pair<>(s[0], s[1]));
            }else if(!checkIf){
                textList.add(new Pair<>(s[0], s[1]));
            }
        }

        return textList;
    }

    private ArrayList<String> generateFileList(String pathName){
        System.out.println(pathName);
        File directoryPath = new File(pathName);

        String[] directories = directoryPath.list((current, name) -> new File(current, name).isDirectory());

//        String[] contents = directoryPath.list();
        ArrayList<String> s = new ArrayList<>();
        if(directories==null){
            directories[0] = "No files available";
        }
        Collections.addAll(s, directories);

        return s;
    }

    /* ********************************************** */
    /*                                                */
    /* After every trigger operation a message to the */
    /*  Subscriber is needed to be sent which is done */
    /*                 by this method                 */
    /*                                                */
    /* ********************************************** */
    public void sendToCurrentClient(Socket sc, ArrayList<Pair<String, String>> studentList, String s) {
        try {
            streamForSendingStrings(sc, s, studentList.size());

            for(Pair p : studentList){
//                System.out.println("Sending: " + p.getKey() + " " + p.getValue());
                dataOutputStream.writeUTF("LogIn ID: " + p.getKey() + ", Name: " + p.getValue());
                dataOutputStream.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendFileNameToCurrentClient(Socket sc, ArrayList<String> studentList, String s) {
        try {
            streamForSendingStrings(sc, s, studentList.size());

            for(String p : studentList){
                System.out.println("File name :" + p);
                dataOutputStream.writeUTF(p);
                dataOutputStream.flush();
            }
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

    private void notifyAllClient(String id, String fName) throws IOException{
        ArrayList<String> s = new ArrayList<>();
        s = generateFileList("./");
        for(int i=0;i<s.size();i++){
            if(isParsable(s.get(i))){
                String p = "./"+s.get(i)+"/notifications.txt";
                Writer wr = new BufferedWriter(new FileWriter(p, true));
                wr.write(id + " requested for " + fName);
                wr.flush();
                wr.close();
            }
        }
    }

    private void streamForSendingStrings(Socket sc, String s, int size) throws IOException {
        dataOutputStream = new DataOutputStream(sc.getOutputStream());
//        System.out.println("Printing ++++++++++> " + s);
        dataOutputStream.writeUTF(s);
        dataOutputStream.flush();
//        System.out.println("sending size : " + size);
        dataOutputStream.writeInt(size);
        dataOutputStream.flush();
    }

    /* ********************************************** */
    /*                                                */
    /*  The process of Sending Data is handled here   */
    /*                                                */
    /* ********************************************** */
    public void sendToClient(MainServerConnectionThread sc, String text) {
        String[] input = text.split(" ");
        if (input[0].equalsIgnoreCase("ShowActiveStudentList")) {
            sendToCurrentClient(sc.getSocket(), MainServerThread.activeStudentList, "Active Student List");
        } else if (input[0].equalsIgnoreCase("ShowAllStudentList")) {
            sendToCurrentClient(sc.getSocket(), generateTextList("./allStudentList.txt", true), "Inactive Student List");
        }else if(input[0].equalsIgnoreCase("ShowNotifications")){
            sendToCurrentClient(sc.getSocket(), generateTextList("./" + studentID + "/notifications.txt", false), "SendingNotifications");
        }else if(input[0].equalsIgnoreCase("ShowFiles")){
            sendFileNameToCurrentClient(sc.getSocket(), generateFileList(input[1]), "Files");
        }else if(input[0].equalsIgnoreCase("SendingFile")){
            System.out.println("Pick " + input[1]);
            UploadServerThread uploadServerThread = new UploadServerThread(this.uploadSocket, this.studentID, input[1]);
            childPool.execute(uploadServerThread);
        }else if(input[0].equalsIgnoreCase("LogOut")){
            MainServerThread.activeStudentList.remove(new Pair<>(studentID, studentName));
            try {
                sc.getSocket().close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }else if(input[0].equalsIgnoreCase("DownloadFile")){
            DownloadServerThread uploadServerThread = new DownloadServerThread(this.downloadSocket, input[1]);
            childPool.execute(uploadServerThread);
        }else if(input[0].equalsIgnoreCase("RequestFile")){
            try {
                MainServerThread.requestWriter.append(sc.studentID + " " + input[1] + "false");
                MainServerThread.requestWriter.flush();
                notifyAllClient(sc.studentID, input[1]);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void run() {
        acceptOrRejectThisConnection();
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            while (shouldRun) {
                while (dataInputStream.available() == 0) {
                    try {
                        Thread.sleep(1);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                String textIn = dataInputStream.readUTF();
                System.out.println("Current Text : "+textIn);
                sendToClient(this, textIn);
            }
            dataInputStream.close();
            dataOutputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}