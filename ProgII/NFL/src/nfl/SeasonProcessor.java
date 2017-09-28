
package nfl;

import acm.program.ConsoleProgram;
import domain.Distance;
import domain.DistanceAccumulator;
import domain.Player;
import domain.StatVar;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.StringTokenizer;

/**
 *
 * @author jmgimeno 
 */
public class SeasonProcessor extends ConsoleProgram {
    
    private static final int NUM_PLAYERS = 10;
    private static final String SEASON  = "season.txt";
    private static final String PLAYERS = "players.dat";
    private static final String ACCUM  = "temporal.dat";
    
    private RandomAccessFile players;
    private BufferedReader outputGame;
    private BufferedReader outputPlayerDistances;
    
    private DistanceAccumulator accum;
    

    public void run() {
        try {
            initializePlayersInfo();
            processSeasonFile();
            printReport();
            closePlayersInfo();
        } catch (IOException ex) {
            // This prints the error on the console
            ex.printStackTrace(this.getWriter());
        }
    }
    
    /**
     * 
     * @throws IOException
     * @throws FileNotFoundException 
     */
    private void initializePlayersInfo() throws IOException, FileNotFoundException {
        players = new RandomAccessFile(PLAYERS, "rw");
        players.setLength(0L);
        for (int numPlayer = 1; numPlayer <= NUM_PLAYERS; numPlayer++) {
            Player player = new Player(numPlayer, String.format("Name-%d", numPlayer));
            byte[] record = player.toBytes();
            players.write(record);
        }
    }
    
    /**
     * 
     * @throws IOException 
     */
    private void closePlayersInfo() throws IOException {
        players.close();
    }
    
    /**
     * 
     * @throws IOException 
     */
    private void processSeasonFile() throws IOException {
        openSeasonFile();
        processSeason();
        closeSeasonFile();
    }
    
    /**
     * Opens the underlying file used by the SeasonProcessor.
     * 
     * @throws IOException 
     */
    private void openSeasonFile() throws IOException {
         outputGame = new BufferedReader (new FileReader(SEASON));         
    }
    
    /**
     * Reads a file up to the end and implements his treatment.
     * 
     * @throws IOException 
     */
    private void processSeason() throws IOException {
        String filename = outputGame.readLine();
        while (filename != null){
            openGameFiles(filename);
            processGameFile();
            closeGameFiles();
            filename = outputGame.readLine();
        }       
    }
    
    /**
     * Closes the underlying file used by the SeasonProcessor.
     * 
     * @throws IOException 
     */
    private void closeSeasonFile() throws IOException {        
        outputGame.close();
    }
    
    /**
     * Opens the given file used by the SeasonProcessor.
     * 
     * @param filename given file.
     * @throws IOException 
     */
    private void openGameFiles(String filename) throws IOException {
        outputPlayerDistances = new BufferedReader (new FileReader(filename));
    }
    
    /**
     * Initializes an instance of DistanceAccumulator.
     * 
     * Reads a file up to the end and implements his treatment.
     * 
     * @throws IOException 
     */
    private void processGameFile() throws IOException {
        accum = new DistanceAccumulator (NUM_PLAYERS, ACCUM);
        String data = outputPlayerDistances.readLine();
        while (data != null){ 
            processGame(data);
            data = outputPlayerDistances.readLine();
        }                                 
        processPlayerAdvancedPerGame();
    }
    
    /**
     * Cuts the given string and save the data to implements his treatment.
     * 
     * @param data given string.
     * @throws IOException 
     */
    private void processGame(String data) throws IOException {
        StringTokenizer st = new StringTokenizer (data, " ");
        int playerNum = Integer.parseInt(st.nextToken());
        Distance playerDistance = Distance.fromString(st.nextToken());
        processPlayerAdvanced(playerNum, playerDistance);
    }
    
    /**
     * Reads the player at the given position and increments his distance total
     * parameter of the given distance.
     * 
     * Writes this player at the given position and increments the  distance 
     * accumulator of this player with the given distance.
     * 
     * @param playerNum given position.
     * @param playerDistance given distance.
     * @throws IOException 
     */
    private void processPlayerAdvanced(int playerNum, Distance playerDistance) throws IOException {
        Player p = readPlayer(playerNum-1);
        p.hasAdvanced(playerDistance);
        writePlayer(playerNum-1, p);
        
        accum.hasAdvanced(playerNum, playerDistance);
    }
    
    /**
     * For the number of players reads the player and increments his distance 
     * per game with the value of the distance accumulator of the player.
     * 
     * Writes this player..
     * 
     * @throws IOException 
     */
    private void processPlayerAdvancedPerGame() throws IOException {
        for (int numPlayer = 1; numPlayer <= NUM_PLAYERS; numPlayer++) {           
            Player p = readPlayer(numPlayer-1);
            p.hasAdancedInGame(accum.totalAdvanced(numPlayer));
            writePlayer(numPlayer-1, p);
        }        
    }
    
    /**
     * Closes the underlying file used by the SeasonProcessor.
     * 
     * @throws IOException 
     */
    private void closeGameFiles() throws IOException {
        outputPlayerDistances.close();
    }
    
    /**
     * Returns a player located at the given position of the file.
     * 
     * @param pos given position of the file.
     * @return returns a player located at the given position of the file.
     * @throws IOException 
     */    
    private Player readPlayer(int pos) throws IOException {
        long position = pos * Player.SIZE;
        byte[] record = new byte [Player.SIZE];
        players.seek(position);
        players.read(record);
        return Player.fromBytes(record);
    }
    
    /**
     * Write a given player at the given position of the file.
     * 
     * @param pos given position of the file.
     * @param p given player.
     * @throws IOException 
     */
    private void writePlayer(int pos, Player p) throws IOException {
        long position = pos * Player.SIZE;
        byte[] record = p.toBytes();
        players.seek(position);
        players.write(record);
    }   
    
    /**
     * 
     * @throws IOException 
     */
    private void printReport() throws IOException {
        players.seek(0L);
        byte[] record = new byte[Player.SIZE];
        int bytesRead = players.read(record);
        while (bytesRead != -1) {
            Player player = Player.fromBytes(record);
            printReportOfPlayer(player);
            bytesRead = players.read(record);
        }
    }

    /**
     * 
     * @param player 
     */
    private void printReportOfPlayer(Player player) {
        println("Name: " + player.getName());
        if (player.getAdvanced().count() > 0) {
            println("ADV:  " + player.getAdvanced());
        }
        if (player.getAdvancedPerGame().count() > 0) {
            println("ADG:  " + player.getAdvancedPerGame());             
        }
        println("-----------------------");
    }
    
    /**
     * 
     * @param args 
     */
    public static void main(String[] args) {
        new SeasonProcessor().start(args);
    }

}
