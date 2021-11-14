package minesweeper.models.game;

/**
 * Enum for the different difficulties
 * @author Marina McPeak
 * @version 1.0
 */
public enum Difficulty {
    EASY(10, 10, 10, 10), MEDIUM(16, 16, 40, 40),
    HARD(16, 30, 80, 100), CUSTOM(5, 5, 5, 5);

    private int rows;
    private int columns;
    private int minesNumber;
    private int points;
    
    /**
     * Constructor for the difficulty class
     * @param rows number of rows on the board
     * @param columns number of columns on the board
     * @param minesNumber number of mines on the board
     * @param points how many points each game is worth
     */
    Difficulty(int rows, int columns,
               int minesNumber, int points) {
        this.rows = rows;
        this.columns = columns;
        this.minesNumber = minesNumber;
        this.points = points;
    }

    /**
     * Get the number of mines
     * @return minesNumber
     */
    public int getMinesNumber()  {
        return minesNumber;
    }

    /**
     * Set the number of rows on the board
     * @param rows int
     */
    public void setRows(int rows) {
        this.rows = rows;
    }

    /**
     * Set the number of columns on the board
     * @param columns int
     */
    public void setColumns(int columns) {
        this.columns = columns;
    }

    /**
     * Set the number of mines
     * @param minesNumber number of mines
     */
    public void setMinesNumber(int minesNumber) {
        this.minesNumber = minesNumber;
    }

    /**
     * Get the number of rows
     * @return rows
     */
    public int getRows() {
        return rows;
    }

    /**
     * Get the number of columns
     * @return columns
     */
    public int getColumns() {
        return columns;
    }

    /**
     * Get the number of points
     * @return points
     */
    public int getPoints() {
        return points;
    }

    /**
     * Set the number of points
     * @param points int
     */
    public void setPoints(int points) {
        this.points = points;
    }

    /**
     * Create string of rows, columns, mines, and points
     * @return the string 
     */
    public String toString()  {
        return name() + ":\n(" + rows + ", " +
                columns + "), " +
                "mines: " + minesNumber +
                ", points: " + points;
    }
}
