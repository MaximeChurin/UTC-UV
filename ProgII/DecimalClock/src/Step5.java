
import acm.program.GraphicsProgram;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */

public class Step5 extends GraphicsProgram {
   
    private static final int NUM_DIGITS = 3;
    
    private static final double TIMEOUT = 200.0;
    
    public void run() {
        getMenuBar().setVisible(false);
        setBackground(Color.BLACK);
        Box ledBox = new Box(0.0, 0.0, getWidth(), getHeight());
        DecimalNumber digit = new DecimalNumber(NUM_DIGITS, ledBox);
        digit.addToGCanvas(getGCanvas());
        int counter = 0;
        while(true) {
            digit.render(counter % 1000);
            counter += 1;
            pause(TIMEOUT);
        }
    }
}
