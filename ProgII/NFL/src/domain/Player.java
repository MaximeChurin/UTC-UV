
package domain;

import utils.PackUtils;

/**
 * This class represents the info we have about a player:
 * <ul>
 *  <li>its number</li>
 *  <li>its name</li>
 *  <li>stats about her advanced distance</li>
 *  <li>stats abous her advanced distance per game</li>
 * </ul>
 * 
 * @author jmgimeno
 */
public class Player {
    
    private int number;
    private String name;
    private StatVar advanced;
    private StatVar advancedPerGame;

    private static final int MAX_NAME_LENGHT = 20;
       
    /**
     * TODO Change value in Step 3
     */
    public static final int SIZE = 4 + 2 * MAX_NAME_LENGHT + 2 * StatVar.SIZE;
    
    /**
     * Returns a player giving to the unpacking of an array of byte.
     * 
     * @param record the given array of byte which contained the player packed.
     * @return returns a player giving to the unpacking of an array of byte.
     */
    public static Player fromBytes(byte[] record) {
        int offset = 0;
        
        int number = PackUtils.unpackInt(record, offset);
        offset += 4;
        String name = PackUtils.unpackLimitedString(MAX_NAME_LENGHT, record, offset);
        offset += 2 * MAX_NAME_LENGHT;
        StatVar advanced = StatVar.unpack(record, offset);
        offset += StatVar.SIZE;
        StatVar advancedPerGame = StatVar.unpack(record, offset);
        offset += StatVar.SIZE;
        
        Player p = new Player(number, name, advanced, advancedPerGame);
        return p;       
    }
    
    /**
     * Returns an array of byte which packed a player.
     * 
     * @return returns an array of byte which packed a player.
     */
    public byte[] toBytes() {
        byte[] record = new byte[SIZE];
        int offset = 0;
        
        PackUtils.packInt(number, record, offset);
        offset += 4;
        PackUtils.packLimitedString(name, MAX_NAME_LENGHT, record, offset);
        offset += 2 * MAX_NAME_LENGHT;
        advanced.pack(record, offset);
        offset += StatVar.SIZE;
        advancedPerGame.pack(record, offset);
        offset += StatVar.SIZE;
        
        return record;
    }
    
    /**
     * Constructs a player given her number and name and initializing the 
     * statistics with empty values
     * 
     * @param number the number of the player
     * @param name the name of the player
     */
    public Player(int number, String name) {
        this(number, name, new StatVar(), new StatVar());
    }

    /**
     * Constructs a player given all the values for its attributes.
     * 
     * @param number the number of the player
     * @param name the name of the player
     * @param advanced statistics of all the advances the player has made
     * @param advancedPerGame statistics of the advances the player has made per game
     */
    private Player(int number, String name, StatVar advanced, StatVar advancedPerGame) {
        this.number = number;
        this.name = name;
        this.advanced = advanced;
        this.advancedPerGame = advancedPerGame;
    }

    /**
     * Returns the number of the player.
     * 
     * @return the number of the player.
     */
    public int getNumber() {
        return number;
    }

    /**
     * Returns the name of the player.
     * 
     * @return the name of the player.
     */
    public String getName() {
        return name;
    }

    /**
     * Returns the statistics of all the advances the player has made.
     * 
     * @return the statistics of all the advances the player has made.
     */
    public StatVar getAdvanced() {
        return advanced;
    }

    /**
     * Returns the statistics of the advances per game the player has made.
     * 
     * @return the statistics of the advances per game the player has made.
     */
    public StatVar getAdvancedPerGame() {
        return advancedPerGame;
    }
    
    /**
     * Notifies that the player has made a single advance of the given distance.
     * 
     * @param distance advanced distance.
     */
    public void hasAdvanced(Distance distance) {
        this.advanced.addObservation(distance.toCentimeters());   
    }
    
    /**
     * Notifies the total distance advanced by the player in a game.
     * 
     * @param distance total advanced distance in a game
     */
    public void hasAdancedInGame(Distance distance) {
        this.advancedPerGame.addObservation(distance.toCentimeters());   
    }
    
    /**
     * Checks if two instances of Player have the same value.
     * @param p1 one player
     * @param p2 another
     * @return whether both instances have the same value or not.
     */
    public static boolean haveSameValue(Player p1, Player p2) {
        return p1.number == p2.number 
                && p1.name.equals(p2.name)
                && StatVar.haveSameValue(p1.advanced, p2.advanced)
                && StatVar.haveSameValue(p1.advancedPerGame, p2.advancedPerGame);
    }

    /**
     * Produce a String with the information of a player.
     * 
     * @return a String with the information of a player.
     */
    public String toString() {
        return String.format("Player{number=%d name=%s adv=%s advGame=%s}", 
                             number, name, advanced, advancedPerGame);
    }
    
    
}
