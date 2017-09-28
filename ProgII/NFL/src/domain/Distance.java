
package domain;

import java.util.StringTokenizer;
import utils.PackUtils;

/**
 * This class represents a distance given by
 * <ul>
 *  <li>yards</li>
 *  <li>feet</li>
 *  <li>inches</li>
 * </ul>
 * that can be added and transformed to centimeters.
 * 
 * @author jmgimeno
 */
public class Distance {
    
    private static final int YARDS_TO_FEET   = 3;
    private static final int FEET_TO_INCHES  = 12;
    private static final double INCHES_TO_CM = 2.54;
    
    private int yards;
    private int feet;
    private int inches;
    
    public static final int SIZE = 3 * 4;
    
    /**
     * Returns an array of byte which packed a distance.
     * 
     * @return returns an array of byte which packed a distance.
     */
    public byte[] toBytes() {
        byte[]	record = new byte[SIZE];
        int offset = 0;  
        
        PackUtils.packInt(yards, record, offset);
        offset += 4;
        PackUtils.packInt(feet, record, offset);
        offset += 4;        
        PackUtils.packInt(inches, record, offset);
        offset += 4; 
        
        return record; 
    }
    
    /**
     * Returns a distance giving to the unpacking of an array of byte.
     * 
     * @param record the given array of byte which contained the distance packed.
     * @return returns a distance giving to the unpacking of an array of byte.
     */
    public static Distance fromBytes(byte[] record) {
        int offset = 0;
        
        int yards = PackUtils.unpackInt(record, offset);
        offset += 4;
        int feet = PackUtils.unpackInt(record, offset);
        offset += 4;
        int inches = PackUtils.unpackInt(record, offset);
        offset += 4;
        
        Distance distance = new Distance(yards, feet, inches);
        return distance;       
    } 
    
    /**
     * Constructs an instance with value zero.
     */
    public Distance() {
        // This is Java way of calling a constructor from another constructor
        this(0, 0, 0);
    }

    /**
     * Constructs an instance of the class given the values of its components.
     * 
     * All values must be positive.
     * 
     * @param yards given yards
     * @param feet given feet
     * @param inches given inches
     */
    private Distance(int yards, int feet, int inches) {
        assert yards  >= 0;
        assert feet   >= 0;
        assert inches >= 0;
        
        this.yards  = yards;
        this.feet   = feet;
        this.inches = inches;
        normalize();
    }
    
    /**
     * 
     */
    private void normalize() {
        this.feet  += this.inches / FEET_TO_INCHES;
        this.inches = this.inches % FEET_TO_INCHES;
        this.yards += this.feet / YARDS_TO_FEET;
        this.feet   = this.feet % YARDS_TO_FEET;
        
        assert this.yards  >= 0;
        assert this.feet   >= 0 && this.feet   < YARDS_TO_FEET;
        assert this.inches >= 0 && this.inches < FEET_TO_INCHES;
    }
    
    /**
     * Constructs a distance given a String with the format {yards}y{feet}f{inches}i.
     * 
     * No format errors are considered.
     * 
     * @param yfi the given string with the correct format.
     * @return returns the instance with the component given by the String.
     */
    public static Distance fromString(String yfi) {
        // We suppose no format error
        StringTokenizer st = new StringTokenizer(yfi, "yfi");
        int yards   = Integer.parseInt(st.nextToken());
        int feet    = Integer.parseInt(st.nextToken());
        int inches  = Integer.parseInt(st.nextToken());
        return new Distance(yards, feet, inches);
    }
    
    /**
     * Adds the given distance to the receptor object.
     * 
     * @param that given distance.
     */
    public void add(Distance that) {
        this.yards  += that.yards;
        this.feet   += that.feet;
        this.inches += that.inches;
        normalize();
    }
    
    /**
     * Returns the distance expressed in centimeters.
     * 
     * @return the distance expressed in centimeters.
     */
    public double toCentimeters() {
        int totalFeet   = (this.yards * YARDS_TO_FEET) + this.feet;
        int totalInches = totalFeet * FEET_TO_INCHES + this.inches;
        return totalInches * INCHES_TO_CM;
    }
    
     /**
     * Produce a String with the information of the distance.
     * 
     * @return a String with the information of the distance.
     */
    public String toString() {
        return String.format("Distance{yards=%d feet=%d inches%d}", this.yards, this.feet, this.inches);
    }

    /**
     * Checks if two instances of Distanve have the same value.
     * @param d1 one distance.
     * @param d2 another distance.
     * @return whether both instances have the same value or not.
     */
    public static boolean haveSameValue(Distance d1, Distance d2) {
        return d1.yards == d2.yards
                && d1.feet == d2.feet
                && d1.inches == d2.inches;
    }
}
