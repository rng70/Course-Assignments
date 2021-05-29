package Adapter;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class AsciiConverter {
    private final String intermediateFileName = "G:\\GitHub Repositories\\Course-Assignments\\CSE 308 - Software Engineering Sessional\\Offline - 3\\Calculate Sum\\src\\Adapter\\IntermediateConvertedFile.txt";
    public void convertCharToInteger(String fileNameWithPath){
        try{
            File openFile = new File(fileNameWithPath);
            File writeToThisFile = new File(intermediateFileName);
            Scanner fileReader = new Scanner(openFile);

            while(fileReader.hasNextLine()){
                String[] c = fileReader.nextLine().split(" ");
                if(writeToThisFile.exists()){
                    writeToThisFile.delete();
                }
                try {
                    FileWriter fw =
                            new FileWriter(intermediateFileName, true);
                    for (String value : c) {
                        String s = (int) (value.charAt(0)) + " ";
                        fw.write(s);
                        System.out.print(s);
                    }
                    fw.close();
                }catch(IOException e){
                    System.out.println("An error occurred. Fail to generate intermediate converted file");
                    e.printStackTrace();
                }

            }
            fileReader.close();
        }catch(FileNotFoundException e){
            System.out.println("File not found. An error occurred");
            e.printStackTrace();
        }
    }
    public String getIntermediateFileName(){
        return intermediateFileName;
    }
}
