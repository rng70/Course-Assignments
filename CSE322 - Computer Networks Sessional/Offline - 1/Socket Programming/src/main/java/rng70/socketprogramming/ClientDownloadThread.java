package rng70.socketprogramming;

import java.net.Socket;
import java.io.*;

public class ClientDownloadThread implements Runnable{

    public static final int MAX_BUFFER_SIZE = 2048;
    public static final int MAX_CHUNK_SIZE = 1024;
    public static final int MIN_CHUNK_SIZE = 256;
    public static int CURRENT_BUFFER_SIZE;
    private final int STRING_SIZE = 20;
    private String fileName;
    Socket uploadSocket;
    public ClientDownloadThread(Socket uploadSocket, String fileName){
        this.uploadSocket = uploadSocket;
        this.fileName = fileName;
    }

    private void getFile(int randomChunkSize) throws IOException{
        DataInputStream dataInputStream = new DataInputStream(this.uploadSocket.getInputStream());
        String fileName = null;
        fileName = dataInputStream.readUTF();

        if(fileName != null){
            FileOutputStream fis = new FileOutputStream(fileName);

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
        try{
            printWriter = new DataOutputStream(uploadSocket.getOutputStream());
            System.out.println("Chunk size: " + randomChunkSize);
            printWriter.writeInt(randomChunkSize);
            printWriter.flush();
            getFile(randomChunkSize);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}

//
//public class ClientDownloadThread implements Runnable{
//
//    Socket downloadSocket;
//    String fileName;
//
//    public ClientDownloadThread(Socket downloadSocket, String fileName){
//        this.downloadSocket = downloadSocket;
//        this.fileName = fileName;
//    }
//
//    @Override
//    public void run(){
//
//    }
//
//    public static void main(String[] args){
//
//    }
//}
