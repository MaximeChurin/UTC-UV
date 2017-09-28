
import acm.program.GraphicsProgram;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */

public class Step1 extends GraphicsProgram {

    private static final double TIMEOUT = 1000.0;
    
    public void run() {
        getMenuBar().setVisible(false);
        setBackground(Color.BLACK);
        Box ledBox = new Box(0.0, 0.0, getWidth(), getHeight());
        Led led = new Led(ledBox);
        led.addToGCanvas(getGCanvas());
        while(true) {
            led.on();
            pause(TIMEOUT);
            led.off();
            pause(TIMEOUT);
        }
    }
}
