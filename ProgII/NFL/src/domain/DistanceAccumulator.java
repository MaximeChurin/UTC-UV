
package domain;

import java.io.RandomAccessFile;
import java.io.IOException;
import java.io.PrintWriter;

/**
 * This class accumulates the distances for the given players using a 
 * random access binary file.
 * 
 * @author jmgimeno
 */
public class DistanceAccumulator {

    private final RandomAccessFile distances;
    private final int numPlayers;

    /**
     * Constructs an instance to accumulate distances for the given number of 
     * players using the fina named filename.
     * 
     * The numPlayers should be positive and the contents of the given file are 
     * erased. Valid players are numbered from 1 to numPlayers.
     * 
     * @param numPlayers given number of players.
     * @param filename the anem of teh file to be used.
     * @throws IOException 
     */
    public DistanceAccumulator(int numPlayers, String filename) throws IOException {
        assert numPlayers > 0;
        this.distances = new RandomAccessFile(filename, "rw");
        this.numPlayers = numPlayers;
        initDistances();
    }
    
    /**
     * Initializes an instance to accumulate distances for the number of
     * players with distance where there values are zero.
     * 
     * @throws IOException 
     */
    private void initDistances() throws IOException {
        Distance distance = new Distance();
        for (int numPlayer = 1; numPlayer <= numPlayers; numPlayer ++){
            writeDistance(numPlayer-1, distance);
        }      
    }
    
    /**
     * Returns a distance located at the given position of the file.
     * 
     * @param pos given position of the file.
     * @return returns a distance located at the given position of the file.
     * @throws IOException 
     */
    private Distance readDistance(int pos) throws IOException {
        long offset = pos * Distance.SIZE;
        byte[] record = new byte [Distance.SIZE];
        distances.seek(offset);
        distances.read(record);
        return Distance.fromBytes(record);
    }
    
    /**
     * Write a given distance at the given position of the file.
     * 
     * @param pos given position of the file.
     * @param distance given distance.
     * @throws IOException 
     */
    private void writeDistance(int pos, Distance distance) throws IOException {
        long offset = pos * Distance.SIZE;
        byte[] record = distance.toBytes();
        distances.seek(offset);
        distances.write(record);
    }
    
    /**
     * Adds the given distance to the accumulated total for the given player.
     * 
     * The method ignores invalid numPlayer values.
     * 
     * @param numPlayer the number of the player.
     * @param distance the distance advanced.
     * @throws IOException if there is a problem with the file.
     */
    public void hasAdvanced(int numPlayer, Distance distance) throws IOException {
        if (1 <= numPlayer && numPlayer <= this.numPlayers) {
            Distance total = this.readDistance(numPlayer-1);
            total.add(distance);
            this.writeDistance(numPlayer-1, total);
        }
    }
    
    /**
     * Returns the distance advanced by the player corresponding to this number.
     * 
     * If an invalid numPlayer is given returns null.
     * 
     * @param numPlayer the number of the player.
     * @return the distance advanced by the player corresponding to this number 
     * or null if the numPlayer is not valid.
     * @throws IOException if there is a problem with the file.
     */
    public Distance totalAdvanced(int numPlayer) throws IOException {
        if (1 <= numPlayer && numPlayer <= this.numPlayers) {
            return this.readDistance(numPlayer-1);
        } else {
            return null;
        }
    }
    
    /**
     * Closes the underlying file used by the DistanceAccumulator.
     * 
     * @throws IOException if there is a problem with the file.
     */
    public void close() throws IOException {
        this.distances.close();
    }
    
    /**
     * Print on the given writer the contents of the file underlying file.
     * 
     * <b>ONLY for debugging purposes.</b>
     * 
     * @param writer where the info is printed.
     * @throws IOException if there is a problem with the file.
     */
    public void dump(PrintWriter writer) throws IOException {
        this.distances.seek(0L);
        for (int player=1; player <= this.numPlayers; player++) {
            Distance distance = this.readDistance(player-1);
            writer.printf("%d - %s (%.2f cm)\n", 
                          player, distance, distance.toCentimeters());
        }
        writer.println("-----------------------");
    }
}
