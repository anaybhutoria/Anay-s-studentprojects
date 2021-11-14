package minesweeper.input.player;

import minesweeper.TestUtils;
import minesweeper.Utils;
import minesweeper.display.player.ConsolePlayerPainter;
import minesweeper.models.player.Player;
import java.util.List;
import java.util.Scanner;

/**
 * This class provides a concrete implementation for 
 * its abstract parent (PlayerRetriver) . 
 * It provides the functionality for getting a Player from
 * console interaction with a user.
 * @version 1.0
 * @author Anay Bhutoria
 */
public class ConsolePlayerRetriever extends PlayerRetriever {
    private ConsolePlayerPainter playerPainter;
    public ConsolePlayerRetriever(List<Player> players)  {
        super(players);
        this.playerPainter = new ConsolePlayerPainter();
     }
   
    /**
     * This method scans the next input and compares it with the existing players list,
     * if a player already exists then select that player in the list, if player is not in list,
     * create a new player
     * @return existingPlayer
     */ 
    @Override
    public Player retrievePlayer() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("\n>=== Choose an existing player" +
                "\n     to play the game as " +
                "\n     or create a new player ===<");
        playerPainter.paint(players);
        System.out.print("Player name: ");
        String name = scanner.nextLine();
        Player existingPlayer = Utils.getPlayerFromList(name, players);
        if (existingPlayer == null) {
          existingPlayer = new Player(name);
          players.add(existingPlayer);
        }
        System.out.println();
        return existingPlayer;
    }
   
    /**
     * This method shows the use of the
     * ConsolePlayerRetriever, and is only used to test this class
     * @param args no command-line arguments expected
     */
    public static void main(String[] args) {
        List<Player> players = TestUtils.testPlayers();
        ConsolePlayerRetriever playerRetriever =
                new ConsolePlayerRetriever(players);
        Player player = playerRetriever.retrievePlayer();
        new ConsolePlayerPainter().paint(player);
    }
}
