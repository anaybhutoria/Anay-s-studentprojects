package minesweeper.models.board;

/**
 * Class extension of BoardSquare
 * that defines a safe square.
 * @author Marina McPeak
 * @version 1.0
 */
public class SafeSquare extends BoardSquare {
	
	/**
	 * Sets safe squares to not mines
	 * @return that square is not a mine
	 */
    @Override 
    public boolean isMine() {
        return false;
    }
    
    /**
     * Set the symbol for the safe square
     * @return the symbol for the safe square
     */
    @Override 
    public String symbol() {
        return String.valueOf(
            getNeighbourMinesNumber());
    }
}
