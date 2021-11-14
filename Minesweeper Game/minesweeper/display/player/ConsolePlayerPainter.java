package minesweeper.display.player;

import minesweeper.TestUtils;
import minesweeper.models.player.Player;
import java.util.Collections;
import java.util.List;

/**
 * This class is used as a 'main menu' for the game,
 * used in at the start of the game to show all the existing players and displays them 
 * under the leaderboard with the corresponding points they have. 
 * @version 1.0
 * @author Anay Bhutoria
 */
public class ConsolePlayerPainter implements PlayerPainter {

	/**
     * When a player name is inputed, this method is called
     * to display the player name, and their corresponding points 
     * @param p
     */
	@Override
    public void paint(Player p)  { 
        System.out.println("\n>>>> Player <<<<");
        System.out.println(p);
        System.out.println();
    }
	
	/**
	 * This method is called at the start of the game to show all the existing players
	 * and rank them on the leaderboard according to how many points they have
	 *@param list of players 
	 */
    @Override
    public void paint(List<Player> players)  {
        if (players == null || players.size() == 0)  { //if no players print no existing players
            System.out.println("No existing players!");
            return;
        }
        System.out.println("\n>>>> Leaderboard <<<<");       
        Collections.sort(players,Collections.reverseOrder()); //sorting the players from greatest to least points
        for (Player p: players)  { // iterating through the list of players and displaying them 
            System.out.printf("%10s  %-8d\n",
                    p.getName(), p.getPoints());
        }
        System.out.println(); 	
    }
    
    /**
     * This method is used to test this class, it is not used in the game
     * @param args
     */
    public static void main(String[] args) {
        ConsolePlayerPainter playerPainter =
                new ConsolePlayerPainter();
        List<Player> players =
                TestUtils.testPlayers();
        playerPainter.paint(players);
        playerPainter.paint(players.get(0));
    }
}