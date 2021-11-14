package minesweeper.input.game.flag;

import minesweeper.models.board.Board;
import minesweeper.models.game.Move;

/**
 * Abstract class that provides blueprint for the consoleFlagRetriever
 * Rettieves flag data and places on board
 * @author Marina McPeak
 * @version 1.0
 */
public abstract class FlagRetriever {
    protected Board board;

    /**
     * Basic Constructor
     * @param board board being played
     */
    public FlagRetriever(Board board) {
        this.board = board;
    }

    /**
     * Abstract method used in console retriever
     * @return flag Move
     */
    public abstract Move retrieveFlag();

}
