
import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */
class LedsClock {
    
    private Group[] watchGroups;
    private static final int SIZE = 3;
    private static final int[] SIZES_HOURS = new int[] { 3, 10 };
    private static final int[] SIZES_MINUTES_AND_SECONDS = new int[] { 6, 10 };

    public LedsClock(Box ledBox) {
        watchGroups = new Group[SIZE];        
        Box[] rowBoxes = ledBox.distributeVertically(SIZE);
        for(int i = 0; i < watchGroups.length; i++){
            if (i == 0){
                watchGroups[i] = new Group(SIZES_HOURS, rowBoxes[i]);
            }            
            else {
                watchGroups[i] = new Group(SIZES_MINUTES_AND_SECONDS, rowBoxes[i]);
            }
        }
    }

    public void addToGCanvas(GCanvas gCanvas) {
        for(int i = 0; i < watchGroups.length; i++){
            watchGroups[i].addToGCanvas(gCanvas);
        }
    }

    public void render(int hours, int minutes, int seconds) {
        watchGroups[0].render(normalize(hours));
        watchGroups[1].render(normalize(minutes));
        watchGroups[2].render(normalize(seconds)); 
    }
    
    private int[] normalize (int time){
        int[] values = new int[] { time % 10, time / 10 };
        return values;
    }
    
}
