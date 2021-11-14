package minesweeper.models.game;

import java.util.Scanner;

/**
 * Define what a point/coordinate on the
 * board is.
 * @author Marina McPeak
 * @version 1.0
 */
public class Point {
    private int row;
    private int column;
    
    /**
     * Constructor
     * @param row
     * @param column
     */
    public Point(int row, int column) {
        this.row = row;
        this.column = column;
    }
    
    /**
     * Get row
     * @return row
     */
    public int getRow() {
        return row;
    }

    /**
     * Get column
     * @return column
     */
    public int getColumn() {
        return column;
    }

    /**
     * toString of the point
     * @return coordinates of the point
     */
    @Override
    public String toString()  {
        return String.format("(%d, %d)",
                getRow(), getColumn());
    }
}

