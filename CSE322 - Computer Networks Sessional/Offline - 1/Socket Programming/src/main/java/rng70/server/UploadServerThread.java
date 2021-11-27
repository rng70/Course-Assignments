package rng70.server;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class UploadServerThread implements Runnable{

    public static final int MAX_BUFFER_SIZE = 2048;
    public static final int MAX_CHUNK_SIZE = 1024;
    public static final int MIN_CHUNK_SIZE = 256;
    public static int CURRENT_BUFFER_SIZE;
    private String mode;
    private String studentID;

    Socket uploadSocket;
    public UploadServerThread(Socket uploadSocket, String studentID, String mode){
        this.uploadSocket = uploadSocket;
        this.studentID = studentID;
        this.mode = mode;
    }

    private int getAlphaNumericString(){
        String currFileName = "./" + studentID + "/fileID.txt";
        File file = new File(currFileName);
        Scanner fileScanner = null;
        try {
            fileScanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String s = "1";
        while(fileScanner.hasNextLine()){
            s = fileScanner.nextLine();
        }
        int currentID = Integer.parseInt(s) + 1;
        BufferedWriter myWriter;
        try {
            myWriter = new BufferedWriter(new FileWriter(currFileName));
            myWriter.write(currentID);
            myWriter.flush();
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return currentID;
    }

    private void getFile(int randomChunkSize, int currFileID) throws IOException{
        DataInputStream dataInputStream = new DataInputStream(this.uploadSocket.getInputStream());
        String fileName = null;
        fileName = dataInputStream.readUTF();

        if(fileName != null){
            if(mode.equalsIgnoreCase("private")){
                this.mode = "private";
            }else{
                this.mode = "public";
            }
            String nowThisFile = "./" + studentID + "/" + mode + "/" + studentID + "-" + currFileID + "-" + fileName;
            FileOutputStream fis = new FileOutputStream(nowThisFile);

            long size = dataInputStream.readLong();
            byte[] actualContent = new byte[randomChunkSize];

            while(size > 0 && ((randomChunkSize = dataInputStream.read(actualContent, 0, (int) Math.min(actualContent.length, size))) != -1)){
                size -= Math.min(actualContent.length, size);
                fis.write(actualContent, 0, randomChunkSize);
            }
        }
    }
    @Override
    public void run() {
        int randomChunkSize =  (int)(Math.random()*(MAX_CHUNK_SIZE-MIN_CHUNK_SIZE+1)+MIN_CHUNK_SIZE);
        DataOutputStream printWriter;
        int fileID = getAlphaNumericString();
        try{
            printWriter = new DataOutputStream(uploadSocket.getOutputStream());
            printWriter.writeInt(randomChunkSize);
            printWriter.flush();
            printWriter.writeInt(fileID);
            printWriter.flush();
            getFile(randomChunkSize, fileID);
        }catch (IOException e){
            e.printStackTrace();
        }


    }
}
