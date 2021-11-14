package minesweeper.input.game.move;

import minesweeper.display.board.ConsoleBoardPainter;
import minesweeper.input.game.square.ConsoleSquareRetriever;
import minesweeper.input.game.square.SquareRetriever;
import minesweeper.models.board.Board;
import minesweeper.models.game.Move;
import java.util.Scanner;

/**
 * This MoveInputRetriever supports
 * getting data from console.
 * @author Izzah Nazir Ahmad 
 * @version 1.0
 */
public class ConsoleMoveInputRetriever extends MoveInputRetriever {

     // A Scanner is used for getting console input. 
    private Scanner scanner = new Scanner(System.in);
    private SquareRetriever squareRetriever =
            new ConsoleSquareRetriever(board);
    /**
     * This method interprets if the move 
     * is already present is the board.
     * If the move is not duplicated then a new move 
     * is created using the row and column.
     * The row and column are retrieved by their 
     * respective methods.  
     */
    @Override 
    public Move retrieveNextMove() {
        Move move;
        do  {
            move = new Move(squareRetriever.retrieveSquare());
        } while (board.isDuplicateMove(move));
        return move;
    }
    
    /**
     * The Board object is necessary to 
     * validate user input: a user should not be able 
     * to pick a row or column outside of Board bounds
     * and the game square can't be already opened.
     *@param board 
     */
    public ConsoleMoveInputRetriever(Board board) {
        super(board);
    }
    
    /**
     * This method shows the use of the
     * ConsoleMoveInputRetriever
     * @param args no command-line arguments expected
     */
    public static void main(String[] args) {
        Board board = new Board(10, 10);
        board.generate(3);
        ConsoleBoardPainter boardPainter =
                new ConsoleBoardPainter();
        boardPainter.paint(board);
        ConsoleMoveInputRetriever consoleRetriever =
            new ConsoleMoveInputRetriever(board);
        Move move = consoleRetriever.retrieveNextMove();
        System.out.println(move);
     }
}
