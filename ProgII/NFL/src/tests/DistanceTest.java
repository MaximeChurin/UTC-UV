
package tests;

import acm.program.ConsoleProgram;
import domain.Distance;

/**
 *
 * @author jmgimeno
 */
public class DistanceTest extends ConsoleProgram {
    
    public void run() {
        println("Begin tests on Distance");
        testDistance();
        println("End tests on Distance");
    }
    
    private Distance regenerate(Distance d) {
        byte[] record = d.toBytes();
        return Distance.fromBytes(record);
    }
    
    private void testDistance() {
        Distance d1 = Distance.fromString("1y2f3i");
        Distance d2 = regenerate(d1);
        if ( ! Distance.haveSameValue(d1, d2) ) {
            println("ERROR - testDistance");
        }
    }

    public static void main(String[] args) {
        new DistanceTest().start(args);
    }
}
