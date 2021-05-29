package CalculatorAdapter;


import Adapter.AsciiConverter;
import IntegerCalculator.CalculateInteger;

public class AdvancedAsciiCalculator implements AdvancedCalculatorInterface{
    AsciiConverter converter = new AsciiConverter();
    CalculateInteger calculateInteger;
    @Override
    public void calculateAsciiSumInInt(String fileName){
        converter.convertCharToInteger(fileName);
        String newFilename = converter.getIntermediateFileName();
        calculateInteger = new CalculateInteger();
        calculateInteger.calculateIntSum(newFilename);
        System.out.println("Sum of the ascii values: " + calculateInteger.getIntSum());
    }
    @Override
    public void calculateIntSum(String fileName){
        // do nothing
    }
}
