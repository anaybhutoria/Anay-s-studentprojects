package minesweeper.input.player;

import minesweeper.models.player.Player;
import java.util.List;

/**
 * This abstract class provides a blueprint for
 * concrete child classes that would extend it. 
 * 
 * A PlayerRetriever gets a new Player data from a user.
 * To avoid having duplicate players from being provided
 * it has access to the list of players
 * to the corresponding Player object.
 * @version 1.0
 * @author Anay Bhutoria
 */
public abstract class PlayerRetriever {
    protected List<Player> players;

    /**
     * A PlayerRetriever takes in a list of players and assigns it to 
     * an instance of the class using this method.
     * @param List of existing players
     */
    public PlayerRetriever(List<Player> players) {
        this.players = players;
    }
    
    /**
     * This method is used to be implemented 
     * by child  of PlayerRetriever classes. 
     */
    public abstract Player retrievePlayer();
}
