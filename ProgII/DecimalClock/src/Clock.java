
import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */
public class Clock {
    
    private final double ledsToDecimalRatio = 3.0 / 4.0;
    private final DecimalClock decimalClock;
    private final LedsClock ledsClock;
    
    public Clock(Box clockBox) { 
        Box[] topBottom = clockBox.splitTopBottom(ledsToDecimalRatio);
        ledsClock = new LedsClock(topBottom[0]);
        decimalClock = new DecimalClock(topBottom[1]);
    }

    public void addToGCanvas(GCanvas gCanvas) {
        ledsClock.addToGCanvas(gCanvas);
        decimalClock.addToGCanvas(gCanvas);
    }

    public void render(int hours, int minutes, int seconds) {
        ledsClock.render(hours, minutes, seconds);
        decimalClock.render(hours, minutes, seconds);
    }
}
