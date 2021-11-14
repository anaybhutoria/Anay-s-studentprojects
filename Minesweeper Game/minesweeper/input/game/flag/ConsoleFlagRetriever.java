package minesweeper.input.game.flag;

import minesweeper.input.game.square.ConsoleSquareRetriever;
import minesweeper.input.game.square.SquareRetriever;
import minesweeper.models.board.Board;
import minesweeper.models.game.Move;
import java.util.Scanner;

/**
 * Retrieves flag data from the console
 * @author Marina McPeak
 * @version 1.0
 */
public class ConsoleFlagRetriever extends FlagRetriever{
    private Scanner scanner = new Scanner(System.in);
    private SquareRetriever squareRetriever = new ConsoleSquareRetriever(board);
    
    public ConsoleFlagRetriever(Board board) {
        super(board);
    }
    
    /*
     * Checks if flag move is valid and performs move is valid.
     * @return null
     * @return move
     */
    @Override
    public Move retrieveFlag()  {
        if (board.getFreeSquares() <= 0)  {
            System.out.println("No closed squares to flag!");
            return null;
        }
        Move move;
        do{
            move = new Move(squareRetriever.retrieveSquare());
        } while (board.isOpen(move));
        return move;
    }
}
