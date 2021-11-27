package rng70.server;

import java.net.Socket;
import java.io.*;

public class DownloadServerThread implements Runnable{
    Socket uploadSocket;
    String fileName;
    PrintWriter printer = null;


    public DownloadServerThread(Socket uploadSocket, String fileName){
        this.uploadSocket = uploadSocket;
        this.fileName = fileName;
    }

    private void sendChunkByChunk(int chunkSize) throws IOException{
        int count;
        byte[] buffer = new byte[chunkSize];

        File file = new File(this.fileName);
        FileInputStream fis = new FileInputStream("./"+this.fileName);

        DataOutputStream dos = new DataOutputStream(this.uploadSocket.getOutputStream());
        String[] tempFileName = this.fileName.split("/");
        String actualNameOfFile = tempFileName[tempFileName.length - 1];

        dos.writeUTF(actualNameOfFile);
        dos.flush();
        System.out.println("File Size = " + file.length());

        dos.writeLong(file.length());
        dos.flush();
        ;
        while ((count = fis.read(buffer)) > 0) {
            dos.write(buffer, 0, count);
            dos.flush();
        }
    }

    @Override
    public void run(){
        DataInputStream scanner;
        int chunkSize;
        try{
            scanner = new DataInputStream(this.uploadSocket.getInputStream());
            chunkSize = scanner.readInt();
            System.out.println("Printing chunk size : "+ chunkSize);
            sendChunkByChunk(chunkSize);
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}