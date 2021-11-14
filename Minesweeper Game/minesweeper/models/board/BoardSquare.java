package minesweeper.models.board;

/**
 * Abstract class to lay a blueprint
 * for subclasses that determine
 * the type for each square on the 
 * board (e.g. mine or safe space)
 * @author Marina McPeak
 * @version 1.0
 */
public abstract class BoardSquare {
    private boolean isOpened;
    private int neighbourMinesNumber;
    private boolean isFlagged;
    
    /**
     * The method checks to see if the square is opened.
     * @return isOpened bool
     */
    public boolean isOpened() {
        return isOpened;
    }
    
    /**
     * Opens the square
     */
    public void open() {
        isOpened = true;
    }
    
    /**
     * Returns toString of the square.
     * @return number or flag, otherwise unopened.
     */
    public String toString() {
        if (isOpened) {
            return symbol();
        }
        if (isFlagged)  {
            return "F";
        }
        return "*";
    }
    
    /**
     * Retrieves neighbouring mines 
     * @return neighbourMinesNumber
     */
    public int getNeighbourMinesNumber() {
        return neighbourMinesNumber;
    } 

    /**
     * Increment the number based on the
     * number of neighbouring mines
     */
    public void incrementNeighbourMinesCount()  {
        setNeighbourMinesNumber(getNeighbourMinesNumber() + 1);
    }

    /**
     * Sets the neihbourMinesNumber 
     * @param n number of mines next to square
     */
    public void setNeighbourMinesNumber(int n) {
        neighbourMinesNumber = n;
    }

    /**
     * Places a flag
     */
    public void flag()  {
        isFlagged = true;
    }

    /**
     * Checks if square is mine
     * @return if square is mine
     */
    public abstract boolean isMine();
    
    /**
     * Symbol of the square.
     * @return the symbol of the square
     */
    public abstract String symbol();
}
