package minesweeper.models.board;

/**
 * Class extension of BoardSquare
 * that defines a square with a mine
 * in it.
 * @author Marina McPeak
 * @version 1.0
 */
public class MineSquare extends BoardSquare {
    
	/**
	 * sets square to a mine
	 * @return that square is mine
	 */
    @Override 
    public boolean isMine() {
        return true;
    }
    
    /**
     * Sets symbol to and X for the text app
     * @return symbol for mine
     */
    @Override 
    public String symbol() {
        return "X";
    }
}
