
import acm.program.GraphicsProgram;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */

public class Step7 extends GraphicsProgram {
    
    private static final double TIMEOUT = 200.0;
    
    public void run() {
        getMenuBar().setVisible(false);
        setBackground(Color.BLACK);
        Box clockBox = new Box(0.0, 0.0, getWidth(), getHeight());
        LedsClock clock = new LedsClock(clockBox);
        TimeTeller time = new TimeTeller();
        clock.addToGCanvas(getGCanvas());
        while(true) {
            int seconds = time.getSeconds();
            int minutes = time.getMinutes();
            int hours = time.getHours();
            clock.render(hours, minutes, seconds);
            pause(TIMEOUT);
        }
    }
}
