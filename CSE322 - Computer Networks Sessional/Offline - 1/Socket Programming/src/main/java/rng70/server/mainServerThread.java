package rng70.server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class mainServerThread {
    private static final int PORT = 6000;
    private static ArrayList<Socket> socketArrayList = new ArrayList<>();

    public static void printResults(Process process) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line = "";
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }

    private static void makeDirectory(String studentID, String studentName){
        Runtime run = Runtime.getRuntime();
        String cmd;
        try {
            cmd = "mkdir " + studentID;
            run.exec(cmd);
            cmd = "mkdir ./" + studentID + "/private";
            run.exec(cmd);
            cmd = "mkdir ./" + studentID + "/public";
            run.exec(cmd);
            cmd = "touch ./" + studentID + "/" + studentName + "-notifications.txt";
            run.exec(cmd);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        Socket socket = null;
        PrintWriter printWriter = null;
        BufferedReader scanner = null;
        ServerSocket serverSocket = null;

        try {
            serverSocket = new ServerSocket(PORT);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try{
            assert serverSocket != null;
            socket = serverSocket.accept();
            socketArrayList.add(socket);
        }catch (IOException e){
            e.printStackTrace();
        }

        try {
            assert  socket != null;
            printWriter = new PrintWriter(socket.getOutputStream(), true);
            scanner = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        } catch (IOException e) {
            e.printStackTrace();
        }

        assert printWriter != null;
        printWriter.println("Connection Established: Please send your Student ID");

        String studentID, studentName;
        try {
            studentID = scanner.readLine();
            studentName = scanner.readLine();

            if(studentID.equals("")){
                printWriter.println("error~: Connection Closed: remote host closed connection. Provide correct student id and try again");
                socket.close();
            }else{
                makeDirectory(studentID, studentName);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
