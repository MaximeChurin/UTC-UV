
import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */
public class DecimalClock {
    private final DecimalNumber[] numbers; 
    private static final int SIZE = 3;
    private static final int DECIMAL = 2;

    public DecimalClock(Box dcBox) { 
        numbers = new DecimalNumber[SIZE]; 
        Box[] numberBoxes = dcBox.distributeHorizontally(SIZE);
        for(int i = 0; i < numbers.length; i++){
            numbers[i] = new DecimalNumber(DECIMAL, numberBoxes[i]);            
        } 
    }
        
    public void addToGCanvas(GCanvas gCanvas) {
        for(int i = 0; i< numbers.length; i++){
            numbers[i].addToGCanvas(gCanvas);          
        }          
    }
    
    public void render(int hours, int minutes, int seconds) {
        assert 0 <= hours   &&   hours <= 23;
        assert 0 <= minutes && minutes <= 59;
        assert 0 <= seconds && seconds <= 59;
        
        numbers[0].render(hours);
        numbers[1].render(minutes);
        numbers[2].render(seconds);         
    }
    
}
