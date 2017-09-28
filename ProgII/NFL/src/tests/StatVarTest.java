
package tests;

import acm.program.ConsoleProgram;
import domain.StatVar;

/**
 *
 * @author jmgimeno
 */
public class StatVarTest extends ConsoleProgram {
    
    public void run() {
        println("Begin tests on StatVar");
        testEmptyStat();
        testNonEmptyStat();
        println("End tests on StatVar");
    }

    private StatVar createNonEmptyStatVar() {
        StatVar sv = new StatVar();
        for (int i = 0; i < 10; i++) {
            sv.addObservation(3 * i + 7);
        }
        return sv;
    }
    
    private StatVar regenerate(StatVar sv) {
        int offset = 7;
        byte[] record = new byte[StatVar.SIZE + offset];
        sv.pack(record, offset);
        return StatVar.unpack(record, offset);
    }
    
    private void testEmptyStat() {
        StatVar sv1 = new StatVar();
        StatVar sv2 = regenerate(sv1);
        if ( ! StatVar.haveSameValue(sv1, sv2) ) {
            println("ERROR - testEmptyStat");
        }
    }
    
    private void testNonEmptyStat() {
        StatVar sv1 = createNonEmptyStatVar();
        StatVar sv2 = regenerate(sv1);
        if ( ! StatVar.haveSameValue(sv1, sv2) ) {
            println("ERROR - testNonEmptyStat");
        }
    }
    
    public static void main(String[] args) {
        new StatVarTest().start(args);
    }
}
