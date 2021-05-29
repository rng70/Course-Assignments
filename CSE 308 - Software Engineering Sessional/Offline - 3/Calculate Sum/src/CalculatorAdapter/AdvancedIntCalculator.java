package CalculatorAdapter;

import IntegerCalculator.CalculateInteger;

public class AdvancedIntCalculator implements AdvancedCalculatorInterface{
    CalculateInteger calculateInteger = new CalculateInteger();
    @Override
    public void calculateIntSum(String fileName){
        calculateInteger.calculateIntSum(fileName);
        System.out.println("Sum of the integer values: " + calculateInteger.getIntSum());
    }
    @Override
    public void calculateAsciiSumInInt(String fileName){
        // do nothing
    }
}
