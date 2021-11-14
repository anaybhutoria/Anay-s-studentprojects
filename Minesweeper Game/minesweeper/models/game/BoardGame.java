package minesweeper.models.game;

/**
 * Abstract class that lays a blueprint
 * for the board and game. Includes 
 * difficulty and play method.
 * @author Marina McPeak & Anay Bhutoria
 * @version 1.0
 */
public abstract class BoardGame {
    private Difficulty difficulty = Difficulty.EASY;
    
    /**
     * This method should be overriden
     * by various kinds of board game classes that
     * would extend this class. 
     */
    public abstract void play();
    
    /**
     * Accessor and mutator methods
     * for the difficulty attribute. 
     */
    public void setDifficulty(Difficulty difficulty) {
        this.difficulty = difficulty;
    }
    
    /**
     * Getter for difficulty
     * @return difficulty
     */
    public Difficulty getDifficulty() {
        return difficulty;
    }
}
