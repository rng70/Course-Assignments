package rng70.socketprogramming;

import java.io.*;
import java.net.Socket;

public class ClientUploadThread implements Runnable{
    Socket uploadSocket;
    String fileName;
    PrintWriter printer = null;


    public ClientUploadThread(Socket uploadSocket, String fileName){
        this.uploadSocket = uploadSocket;
        this.fileName = fileName;
    }

    private void sendChunkByChunk(int chunkSize, int fileID) throws IOException{
        int count;
        byte[] buffer = new byte[chunkSize];

        File file = new File(this.fileName);
        FileInputStream fis = new FileInputStream(this.fileName);

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
        int fileID;
        int chunkSize;
        try{
           scanner = new DataInputStream(this.uploadSocket.getInputStream());
           chunkSize = scanner.readInt();
           fileID = scanner.readInt();
           sendChunkByChunk(chunkSize, fileID);
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
