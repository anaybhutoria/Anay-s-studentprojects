package minesweeper.display.board;

import minesweeper.models.board.Board;

/**
 * This interface contains
 * a method to display a game board. 
 * @author Marina McPeak
 * @version 1.0
 */
public interface BoardPainter {
	/**
	 * Uses the paint method of ConsoleBoardPainter to display a game board
	 * @param board the board that is currently being played
	 */
    void paint(Board board);
}
