
import acm.graphics.GCanvas;
import acm.graphics.GRect;
import java.awt.Color;

/**
 *
 * @author jmgimeno
 */
public class DecimalDigit {

    private static final String ZERO =  "············" +
                                        "···######···" +
                                        "··########··" +
                                        "··##····##··" +
                                        "··##····##··" +
                                        "··##····##··" +
                                        "··##····##··" +
                                        "··##····##··" + 
                                        "··##····##··" +
                                        "··########··" +
                                        "···######···" +
                                        "············";
    
    private static final String ONE =   "············" +
                                        "·····##·····" +
                                        "····###·····" +
                                        "···####·····" +
                                        "·····##·····" +
                                        "·····##·····" +
                                        "·····##·····" +
                                        "·····##·····" + 
                                        "·····##·····" +
                                        "···######···" +
                                        "···######···" +
                                        "············";
    
    private static final String TWO =   "············" +
                                        "···######···" +
                                        "··########··" +
                                        "··##····##··" +
                                        "·······###··" +
                                        "······###···" +
                                        "·····###····" +
                                        "····###·····" + 
                                        "···###······" +
                                        "··########··" +
                                        "··########··" +
                                        "············";
    
    private static final String THREE = "············" +
                                        "···######···" +
                                        "··########··" +
                                        "··##····##··" +
                                        "········##··" +
                                        "·····####···" +
                                        "·····####···" +
                                        "········##··" + 
                                        "··##····##··" +
                                        "··########··" +
                                        "···######···" +
                                        "············";
    
    private static final String FOUR  = "············" +
                                        "······###···" +
                                        "·····####···" +
                                        "····#####···" +
                                        "···###·##···" +
                                        "··###··##···" +
                                        "··##···##···" +
                                        "··########··" + 
                                        "··########··" +
                                        "·······##···" +
                                        "·······##···" +
                                        "············";
        
    private static final String FIVE =  "············" +
                                        "··########··" +
                                        "··########··" +
                                        "··##········" +
                                        "··##········" +
                                        "··#######···" +
                                        "··########··" +
                                        "········##··" + 
                                        "········##··" +
                                        "··########··" +
                                        "··#######···" +
                                        "············";
     
    private static final String SIX =   "············" +
                                        "···#######··" +
                                        "··########··" +
                                        "··##········" +
                                        "··##········" +
                                        "··#######···" +
                                        "··########··" +
                                        "··##····##··" + 
                                        "··##····##··" +
                                        "··########··" +
                                        "···######···" +
                                        "············";
    
    private static final String SEVEN = "············" +
                                        "··########··" +
                                        "··########··" +
                                        "········##··" +
                                        "·······###··" +
                                        "······###···" +
                                        "·····###····" +
                                        "····###·····" + 
                                        "···###······" +
                                        "··###·······" +
                                        "··##········" +
                                        "············";
    
    private static final String EIGHT = "············" +
                                        "···######···" +
                                        "··########··" +
                                        "··##····##··" +
                                        "··##····##··" +
                                        "···######···" +
                                        "···######···" +
                                        "··##····##··" + 
                                        "··##····##··" +
                                        "··########··" +
                                        "···######···" +
                                        "············";
        
    private static final String NINE =  "············" +
                                        "···######···" +
                                        "··########··" +
                                        "··##····##··" +
                                        "··##····##··" +
                                        "··########··" +
                                        "···#######··" +
                                        "········##··" + 
                                        "········##··" +
                                        "··########··" +
                                        "··#######···" +
                                        "············";
    
    private static final String[] patterns = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };
    
    private static final Color COLOR_OFF = Color.BLACK;
    private static final Color COLOR_ON = Color.YELLOW;
    private static final int RESOLUTION = 12;

    private final GRect[][] pixels;
    
    public DecimalDigit(Box ddBox) {
        pixels = new GRect[RESOLUTION][RESOLUTION];
        Box[][] ledBoxes = ddBox.distributeBidimensionally(RESOLUTION, RESOLUTION);
        for (int row = 0; row < RESOLUTION; row++) {
            for (int col = 0; col < RESOLUTION; col++) {
                GRect led = new GRect(ledBoxes[row][col].getX(),
                                      ledBoxes[row][col].getY(),
                                      ledBoxes[row][col].getWidth(),
                                      ledBoxes[row][col].getHeight());
                led.setFilled(true);
                led.setColor(COLOR_OFF);
                pixels[row][col] = led;
            }
        }
    }
    
    public void addToGCanvas(GCanvas gCanvas) {
       for (int row = 0; row < RESOLUTION; row++) {
            for (int col = 0; col < RESOLUTION; col++) {
                gCanvas.add(pixels[row][col]);
            }
        }    
    }
    
    public void render(int digit) {
        String pattern = patterns[digit];
        render(pattern);
    }
    
    private void render(String pattern) {
        for (int row = 0; row < RESOLUTION; row++) {
            for (int col = 0; col < RESOLUTION; col++) {
                int charPos = row * RESOLUTION + col;
                if (pattern.charAt(charPos) == '#') {
                    pixels[row][col].setColor(COLOR_ON);
                } else {
                    pixels[row][col].setColor(COLOR_OFF);
                }
            }
            
        }
    }
    
}
