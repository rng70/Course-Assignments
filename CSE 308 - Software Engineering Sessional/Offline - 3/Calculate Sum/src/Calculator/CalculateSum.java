package Calculator;

import CalculatorAdapter.AdvancedAsciiCalculator;
import CalculatorAdapter.AdvancedCalculatorInterface;
import CalculatorAdapter.AdvancedIntCalculator;
import CalculatorAdapter.CalculatorAdapter;

public class CalculateSum implements Calculator {
     CalculatorAdapter calculatorAdapter;
    @Override
    public void calculateSum(String isAscii, String fileName) {
        calculatorAdapter = new CalculatorAdapter(isAscii);
        calculatorAdapter.calculateSum(isAscii, fileName);
    }
}
