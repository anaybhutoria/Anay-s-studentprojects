package minesweeper.models.player;

import minesweeper.input.player.ConsolePlayerRetriever;
import minesweeper.input.player.PlayerRetriever;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;


/**
 * This class represents a PlayerManager
 * A PlayerManager has an ArrayList of players and playerRetrievers.
 * @author Mika Ong
 * @version 1.0
 */
 public class PlayerManager {
    private Player player;
    private Set<Player> players = new HashSet<>();
    private PlayerRetriever playerRetriever = new ConsolePlayerRetriever(new ArrayList<>(getPlayers()));

    /**
     * Get player from playerRetriever class and add it to set of players.
     * @return player Player.
     */
    public Player getCurrentPlayer()  {
        player = playerRetriever.retrievePlayer();
        getPlayers().add(player);
        return player;
    }

    /**
     * Getter for the players and returns the set of Players
     * @return players
     */
	public Set<Player> getPlayers() {
		return players;
	}
    
    /**
     * Setter for the players 
     * @param players
     */
	public void setPlayers(Set<Player> players) {
		this.players = players;
	}
    
    /**
     * Tester method for the class
     * @param args
     */
    public static void main(String[] args) {
        PlayerManager manager = new PlayerManager();
        System.out.println(manager.getCurrentPlayer());
        System.out.println(manager.getCurrentPlayer());
    }
   
}
