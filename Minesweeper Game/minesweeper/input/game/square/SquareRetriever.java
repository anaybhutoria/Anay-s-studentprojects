package minesweeper.input.game.square;

import minesweeper.models.board.Board;
import minesweeper.models.game.Point;

/**
 * Abstract class for the square retriever
 * Provides blueprint to 
 * @author Marina McPeak
 * @version 1.0
 */
public abstract class SquareRetriever {
    protected Board board;
    
    /**
     * Basic Constructor 
     * @param board board being played
     */
    public SquareRetriever(Board board) {
        this.board = board;
    }

    /**
     * Abstract used in console retriever
     * @return point of square
     */
    public abstract Point retrieveSquare();

}
