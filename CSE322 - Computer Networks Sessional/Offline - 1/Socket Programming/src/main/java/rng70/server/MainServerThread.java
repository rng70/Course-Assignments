package rng70.server;

import javafx.util.Pair;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.net.ServerSocket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainServerThread {
    private static final int PORT = 6000;

    public static ArrayList<MainServerConnectionThread> mainServerConnectionThreadsList = new ArrayList<>();
    public static Writer requestWriter = null;
    public static final ArrayList<Pair<String, String>> activeStudentList = new ArrayList<>();
    private static ExecutorService pool = Executors.newFixedThreadPool(100);
    ServerSocket uploadServerSocket = null;
    ServerSocket downloadServerSocket = null;

    /* ********************************************** */
    /*                                                */
    /*  This method allows us to see the output of a  */
    /*                 process                        */
    /*                                                */
    /* ********************************************** */
    public static void printProcessOutput(Process process) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }

    /* ********************************************** */
    /*                                                */
    /*                Main server thread              */
    /*                                                */
    /* ********************************************** */
    public MainServerThread() {
        Socket socket;
        Writer output = null;
        ServerSocket serverSocket = null;

        final int UPLOAD_PORT = 3000;
        final int DOWNLOAD_PORT = 3333;

        final ArrayList<Socket> socketArrayList = new ArrayList<>();

        File allStudentList = new File("./allStudentList.txt");
        File request = new File("./requests.txt");
        try {
            allStudentList.createNewFile();
            request.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            output = new BufferedWriter(new FileWriter(allStudentList, true));
            requestWriter = new BufferedWriter(new FileWriter(request, true));
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            serverSocket = new ServerSocket(PORT);
            uploadServerSocket = new ServerSocket(UPLOAD_PORT);
            downloadServerSocket = new ServerSocket(DOWNLOAD_PORT);
        } catch (IOException e) {
            e.printStackTrace();
        }

        boolean shouldRun = true;
        assert serverSocket != null;
        while(shouldRun){
            try{
                socket = serverSocket.accept();
                socketArrayList.add(socket);
                MainServerConnectionThread mainServerConnectionThread = new MainServerConnectionThread(this, socket, output, uploadServerSocket, downloadServerSocket);
                mainServerConnectionThreadsList.add(mainServerConnectionThread);

                pool.execute(mainServerConnectionThread);
//                Thread thread = new Thread(mainServerConnectionThread);
//                thread.start();

//                acceptOrRejectThisConnection(mainServerConnectionThread);
            }catch (IOException e){
                shouldRun = false;
                try {
                    printProcessOutput(Runtime.getRuntime().exec("ls -al"));
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
                e.printStackTrace();
            }
        }
    }

//    public void acceptOrRejectThisConnection(MainServerConnectionThread mainServerConnectionThread){
//        mainServerConnectionThread.acceptOrRejectThisConnection();
//    }

    public static void main(String[] args){
        new MainServerThread();
    }
}
