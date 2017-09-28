
package tests;

import acm.program.ConsoleProgram;
import domain.Distance;
import domain.Player;

/**
 *
 * @author jmgimeno
 */
public class PlayerTest extends ConsoleProgram {
    
    public void run() {
        println("Begin tests on Player");
        testPlayer();
        println("End tests on Player");
    }

    private void testPlayer() {
        Player p1 = new Player(15, "Dustin Pedroia"); // Yes, I know he's a baseball player
        p1.hasAdvanced(Distance.fromString("1y2f3i"));
        p1.hasAdancedInGame(Distance.fromString("3y2f1i"));
        Player p2 = Player.fromBytes(p1.toBytes());
        if ( ! Player.haveSameValue(p1, p2)) {
            println("ERROR - testPlayer");
        }
    }
    
    public static void main(String[] args) {
        new PlayerTest().start(args);
    }
}
