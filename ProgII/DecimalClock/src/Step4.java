
import acm.program.GraphicsProgram;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */

public class Step4 extends GraphicsProgram {
    
    private static final double TIMEOUT = 1000.0;
    
    public void run() {
        getMenuBar().setVisible(false);
        setBackground(Color.BLACK);
        Box ledBox = new Box(0.0, 0.0, getWidth(), getHeight());
        DecimalDigit digit = new DecimalDigit(ledBox);
        digit.addToGCanvas(getGCanvas());
        int counter = 0;
        while(true) {
            digit.render(counter % 10);
            counter += 1;
            pause(TIMEOUT);
        }
    }
}
