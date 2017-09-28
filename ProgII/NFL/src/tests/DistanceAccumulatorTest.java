
package tests;

import acm.program.ConsoleProgram;
import domain.Distance;
import domain.DistanceAccumulator;
import java.io.IOException;

/**
 *
 * @author jmgimeno
 */
public class DistanceAccumulatorTest extends ConsoleProgram {

    public void run() {
        try {
            println("Begin tests");
            testOnlyCreated();
            testExtrems();
            testAccumulated();
            println("End tests");
        } catch (IOException ex) {
            ex.printStackTrace(this.getWriter());
        }
    }

    private void testOnlyCreated() throws IOException {
        DistanceAccumulator accum = new DistanceAccumulator(5, "test.dat");
        if ( ! allZero(1, 5, accum) ) {
            println("ERROR - testOnlyCreated");
        }
        accum.close();
    }

    private void testExtrems() throws IOException {
        DistanceAccumulator accum = new DistanceAccumulator(5, "test.dat");
        Distance d1 = Distance.fromString("1y2f3i");
        Distance d5 = Distance.fromString("3y2f1i");
        accum.hasAdvanced(1, d1);
        accum.hasAdvanced(5, d5);
        if ( ! Distance.haveSameValue(d1, accum.totalAdvanced(1)) 
                || ! Distance.haveSameValue(d5, accum.totalAdvanced(5)) 
                || ! allZero(2, 4, accum)) {
            println("ERROR - testExtrems");
        }
        accum.close();
    }
    
    private void testAccumulated() throws IOException {
        DistanceAccumulator accum = new DistanceAccumulator(5, "test.dat");
        Distance d1 = Distance.fromString("1y2f3i");
        Distance d2 = Distance.fromString("3y2f1i");
        accum.hasAdvanced(2, d1);
        accum.hasAdvanced(2, d2);
        Distance total = new Distance();
        total.add(d1);
        total.add(d2);
        if ( ! Distance.haveSameValue(total, accum.totalAdvanced(2))) {
            println("ERROR - testAccumulated");
        }
        accum.close();
    }
    
    private boolean allZero(int first, int last, DistanceAccumulator accum) throws IOException {
        Distance zero = new Distance();
        for (int player=first; player <= last; player++) {
            Distance total = accum.totalAdvanced(player);
            if ( ! Distance.haveSameValue(total, zero) ) {
                return false;
            }
        }
        return true;
    }
    
    public static void main(String[] args) {
        new DistanceAccumulatorTest().start(args);
    }
}
