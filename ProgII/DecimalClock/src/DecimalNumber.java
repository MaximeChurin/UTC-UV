
import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */

public class DecimalNumber {
    private final DecimalDigit[] digits;
    private static final int BASE = 10;

    public DecimalNumber(int numDigits, Box dnBox) {
        assert numDigits > 0;
       
        digits = new DecimalDigit[numDigits];
        Box[] digitBoxes = dnBox.distributeHorizontally(numDigits);
        for(int i = 0; i < digits.length; i++){
            digits[i] = new DecimalDigit(digitBoxes[i]);            
        }       
    }

    public void addToGCanvas(GCanvas gCanvas) {
        for(int i = 0; i < digits.length; i++){
            digits[i].addToGCanvas(gCanvas);            
        }                
    }
    
    public void render(int number) {
        assert number >= 0;
        
        for(int i = 0; i < digits.length; i++){
            int pow = (int) Math.pow(BASE, digits.length - i - 1);
            digits[i].render(number / pow % BASE);        
        }             
    }
    
}
