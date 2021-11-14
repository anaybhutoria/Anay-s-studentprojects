package minesweeper.models.player;

import minesweeper.input.game.flag.ConsoleFlagRetriever;
import minesweeper.input.game.move.MoveInputRetriever;
import minesweeper.models.game.Move;

import java.io.Serializable;

/**
 * This class represents a player in Minesweeper.
 * A player is defined by their name and game points. 
 * @author  Huda Elbayok and Anay Bhutoria
 * @version 1.0
 */
public class Player implements Comparable<Player>, Serializable {
    private String name = "Player";
	private transient ConsoleFlagRetriever flagRetriever;
    private MoveInputRetriever moveInputRetriever;
    
    /**
     * Basic constructor for a player
     * @param name name of player
     */
    public Player(String name) {
        this.name = name;
    }

    /**
     * Constructor for a player with name and points
     * @param name name of player
     * @param points number of points player has
     */
    public Player(String name, int points) {
        this.name = name;
        this.points = points;
    }
	
    /**
     * Increments the points of the player
     * @param i integer amoount to increment points by
     */
	public void incrementPoints(int i)  {
        points += i;
    }

	/**
	 * Decrement the points of the player
	 * @param i integer amount to decrement the points by
	 */
    public void decrementPoints(int i)  {
        points -= i;
    }

    /**
     * The following two methods
     * are used to compare players.
     *
     * To players are equal if they have
     * the same name. The player names are not
     * case-sensitive: converting some of the
     * letters to the opposite case would not
     * make the name unique
     *
     */

    /**
     * This method compares the players.
     * Two players are compared by their names.
     *
     * @param p the other player.
     * @return 0 if two players are the equal,
     * a positive number of this player is greater
     * than the player passed as a method parameter
     * and a positive number if this player is less
     * than the other player.
     */
    @Override
    public int compareTo(Player p) {
        return Integer.compare(points, p.points);
    }

    /**
     * This method checks if two
     * players are equal.
     * Two players equal if their names
     * are equal.
     *
     * @param o the other player
     * @return true if two players are equal,
     * false otherwise.
     */
    @Override
    public boolean equals(Object o)  {
        if (o == null)  {
            return false;
        }
        if (!(o instanceof Player))  {
            return false;
        }
        Player p = (Player) o;
        return name.equalsIgnoreCase(p.name);
    }

    public void setMoveInputRetriever(MoveInputRetriever retriever) {
        moveInputRetriever = retriever;
    }
    
    /**
     * For each victory a number
     * of points is given;
     * for each defeat a number of points is deducted. 
     * The number of points a player has
     * determines the difficulty of the game
     * and the player's position in leaderboard
     */
    private int points;

    /**
     * Gets the next move of the player
     * @return the players move
     */
    public Move getNextMove() {
            return moveInputRetriever.retrieveNextMove();
    }
	
    /**
     * Gets the flag move of the player
     * @return flag move of the player
     */
	public Move getFlag()  {
        return flagRetriever.retrieveFlag();
    }

	/**
	 * Set toString of the player
	 */
    @Override
    public String toString()  {
        return String.format("Name: %s%nPoints: %d",
                name, points);
    }

    /**
     * gets the name of the player
     * @return name of player
     */
    public String getName() {
        return name;
    }

    /**
     * gets the points of the player
     * @return numebr of points the player has
     */
    public int getPoints() {
        return points;
    }
	
    /**
     * sets the flag retriever for the player
     * @param flagRetriever flad retriever of the player
     */
	 public void setFlagRetriever(ConsoleFlagRetriever flagRetriever) {
        this.flagRetriever = flagRetriever;
    }
}
