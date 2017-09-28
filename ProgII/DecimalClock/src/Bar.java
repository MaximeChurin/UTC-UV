import acm.graphics.GCanvas;

/**
 *
 * @author jmgimeno
 */
class Bar {
    private final Led[] leds;
    
    public Bar(int size, Box barBox) {
        assert size > 0;        
        
        leds = new Led[size];
        Box[] columBoxes = barBox.distributeHorizontally(size);
        for (int i = 0; i < leds.length; i++){
            leds[i] = new Led(columBoxes[i]);
        }
    }

    public void addToGCanvas(GCanvas gCanvas) {
        for (int i = 0; i < leds.length; i++){
            leds[i].addToGCanvas(gCanvas);
        }
    }       
    

    public void render(int value) {
        leds[value].on();
        if(value > 0){
            leds[value - 1].off();            
        }
        if(value == 0){
            leds[leds.length - 1].off();            
        }  
    }
    
}
