
import acm.program.GraphicsProgram;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */

public class ClockProgram extends GraphicsProgram {
    
    private static final double TIMEOUT = 500.0;

    @Override
    public void run() {
        getMenuBar().setVisible(false);
        setBackground(Color.BLACK);
        Box applicationBox = new Box(0.0, 0.0, getWidth(), getHeight());
        Clock clock = new Clock(applicationBox);
        TimeTeller timeTeller = new TimeTeller();
        clock.addToGCanvas(getGCanvas());
        while (true) {
            int hours = timeTeller.getHours();
            int minutes = timeTeller.getMinutes();
            int seconds = timeTeller.getSeconds();
            clock.render(hours, minutes, seconds);
            pause(TIMEOUT);
        }
    }  
}
