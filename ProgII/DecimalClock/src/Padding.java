
/**
 *
 * @author jmgimeno
 */
public class Padding {
    
    private final double top;
    private final double right;
    private final double bottom;
    private final double left;

    public Padding(double top, double right, double bottom, double left) {
        assert 0.0 <= top;
        assert 0.0 <= right;
        assert 0.0 <= bottom;
        assert 0.0 <= left;
        assert top + bottom <= 1.0;
        assert left + right <= 1.0;
        
        this.top = top;
        this.right = right;
        this.bottom = bottom;
        this.left = left;
    }

    public static Padding regular(double padding) {
        return new Padding(padding, padding, padding, padding);
    }
    
    public static Padding horizontal(double padding) {
        return new Padding(0.0, padding, 0.0, padding);
    }
    
    public static Padding vertical(double padding) {
        return new Padding(padding, 0.0, padding, 0.0);
    }
    
    public double getTop() {
        return top;
    }

    public double getRight() {
        return right;
    }

    public double getBottom() {
        return bottom;
    }

    public double getLeft() {
        return left;
    }  
}
