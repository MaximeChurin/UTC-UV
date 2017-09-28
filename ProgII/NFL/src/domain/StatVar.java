
package domain;

import utils.PackUtils;

/**
 * For the sequentially given observations computes the following statistics:
 * <ul>
 *  <li>count</li>
 *  <li>mean</li>
 *  <li>standard deviation</li>
 *  <li>minimum</li>
 *  <li>maximum</li>
 * </ul>
 * @author jmgimeno
 */
public class StatVar {

    private int count;
    private double sum;
    private double sumSquares;
    private double min;
    private double max;
    
    public static final int SIZE = 4 + 4 * 8;

    /**
     * Returns a StatVar giving to the unpacking of an array of byte at a 
     * specific position.
     * 
     * @param record the array of byte which contained one or more StatVar 
     * packed.
     * @param offset the value of the position where we start the unpacking.
     * @return Returns a StatVar giving to the unpacking of an array of byte 
     * at a specific position.
     */
    public static StatVar unpack(byte[] record, int offset) {
        StatVar sv = new StatVar();
        
        sv.count = PackUtils.unpackInt(record, offset);
        offset += 4;
        sv.sum = PackUtils.unpackDouble(record, offset);
        offset += 8;        
        sv.sumSquares = PackUtils.unpackDouble(record, offset);
        offset += 8;        
        sv.min = PackUtils.unpackDouble(record, offset);
        offset += 8;
        sv.max = PackUtils.unpackDouble(record, offset);
        offset += 8;       
        
        return sv;
    }
    
    /**
     * Packs a StatVar into an array of byte at a specific position.
     * 
     * @param record the array of byte which contained the last StatVar packed 
     * and this new StatVar.
     * @param offset the value of the position where we start the packing.
     */
    public void pack(byte[] record, int offset) {
        PackUtils.packInt(count, record, offset);
        offset += 4;
        PackUtils.packDouble(sum, record, offset);
        offset += 8;        
        PackUtils.packDouble(sumSquares, record, offset);
        offset += 8;        
        PackUtils.packDouble(min, record, offset);
        offset += 8;        
        PackUtils.packDouble(max, record, offset);
        offset += 8;
    }
    
    /**
     * Constructs an instance with no observations.
     */
    public StatVar() {
        this.count = 0;
        this.sum = 0.0;
        this.sumSquares = 0.0;
        this.min = Double.POSITIVE_INFINITY;
        this.max = Double.NEGATIVE_INFINITY;
    }
    
    /**
     * Adds a new observation of the statistic variable.
     * 
     * @param value the observer value.
     */
    public void addObservation(double value) {
        this.count += 1;
        this.sum += value;
        this.sumSquares += value * value;
        if (value <= this.min) { this.min = value; }
        if (value >= this.max) { this.max = value; }
    }
    
    /**
     * Returns the number of observed values.
     * 
     * @return the number of observed values.
     */
    public int count() {
        return count;
    }
    
    /**
     * Returns the mean of the observed values.
     * 
     * @return the mean of the observed values.
     */    
    public double mean() {
        return this.sum / this.count;
    }
    
    /**
     * Returns the standard deviation of the observed values.
     * 
     * @return the standard deviation of the observed values.
     */ 
    public double stdDev() {
        double mean = mean();
        double variance = this.sumSquares / this.count - mean * mean;
        return Math.sqrt(variance);
    }
    
    /**
     * Returns the minimum of the observed values.
     * 
     * @return the minimum of the observed values.
     */ 
    public double min() {
        return this.min;
    }
    
    /**
     * Returns the maximum of the observed values.
     * 
     * @return the maximum of the observed values.
     */ 
    public double max() {
        return this.max;
    }
    
    /**
     * Produces a String with the information of the variable.
     * 
     * @return a String with the information of the variable.
     */
    public String toString() {
        if (this.count == 0) {
            return "StatVar{No observations}";
        } else {
            return String.format("StatVar{count=%d mean=%.2f stdev=%.2f min=%.2f max=%.2f}", 
                                 this.count, this.mean(), this.stdDev(), this.min, this.max);
        }
    }
    
    /**
     * Checks if two instances of Player have the same value.
     * 
     * @param sv1 one StatVar
     * @param sv2 another
     * @return whether both instances have the same value or not.
     */
    public static boolean haveSameValue(StatVar sv1, StatVar sv2) {
        return sv1.count == sv2.count 
                && sv1.sum == sv2.sum
                && sv1.sumSquares == sv2.sumSquares
                && sv1.min == sv2.min
                && sv1.max == sv2.max;
    }
}
