package CalculatorAdapter;

import Calculator.Calculator;

public class CalculatorAdapter implements Calculator {
    AdvancedCalculatorInterface newInterface;
    public CalculatorAdapter(String fileType){
        if(fileType.equalsIgnoreCase("ascii")){
            newInterface = new AdvancedAsciiCalculator();
        }else{
            newInterface = new AdvancedIntCalculator();
        }
    }
    public void calculateSum(String isAscii, String fileName){
        if(isAscii.equalsIgnoreCase("ascii")){
            newInterface.calculateAsciiSumInInt(fileName);
        }else{
            newInterface.calculateIntSum(fileName);
        }
    }
}
