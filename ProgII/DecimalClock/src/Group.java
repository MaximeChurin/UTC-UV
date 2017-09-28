                                                        
import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */
class Group {    
    private final Bar[] bars;

    public Group(int[] sizes, Box groupBox) {
        
        bars = new Bar[sizes.length];
        Box[] rowBoxes = groupBox.distributeVertically(sizes.length);
        for (int i = 0; i < bars.length; i++){
            bars[i] = new Bar(sizes[i], rowBoxes[i]);
        }
    }

    public void addToGCanvas(GCanvas gCanvas) {
        for (int i = 0; i < bars.length; i++){
            bars[i].addToGCanvas(gCanvas);
        }
    } 

    public void render(int[] values) {
        for (int i = 0; i < bars.length; i++){
            bars[i].render(values[bars.length - 1 - i]);
        }        
    } 
    
}
