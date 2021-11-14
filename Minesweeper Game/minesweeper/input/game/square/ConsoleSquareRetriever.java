package minesweeper.input.game.square;

import minesweeper.display.board.ConsoleBoardPainter;
import minesweeper.models.board.Board;
import minesweeper.models.game.Point;
import java.util.Scanner;

/**
 * Retrieves square data from the console and checks if the square is a valid option.
 * @author Marina McPeak
 * @version 1.0
 */
public class ConsoleSquareRetriever extends SquareRetriever {
    private Scanner scanner = new Scanner(System.in);
    
	/**
 	 * Retrieves the square from the board. 
	 * @param board  
	 *
	 */
    public ConsoleSquareRetriever(Board board) {
        super(board);
    }

    /**
     * Gets the player input from the console
     * @return returns a point where the player selected
     */
    @Override
    public Point retrieveSquare()  {
        String point;
        do { System.out.print("Enter square " + "coordinates: ");
            point = scanner.nextLine();
        } while (!checkValid(point));
        char column = point.charAt(0);
        int row = Integer.parseInt(point.substring(1));
        return new Point(board.rows() - row,
                column - 'a');
    }

    /**
     * Checks if the players move is valid
     * @param move the player move
     * @return boolean if the move is valid
     */
    private boolean checkValid(String move)  {
        char column = move.charAt(0);
        if (column < 97 || column > 122)  {
            System.out.println("Column must be a letter!");
            return false;
        }
        if (!board.isValidColumn(column - 'a'))  {
            System.out.println("Invalid column!");
            return false;
        }
        int row;
        try  {
            row = Integer.parseInt(
                    move.substring(1));
        }
        catch (Exception e)  {
            System.out.println("Row must be numeric!");
            return false;
        }
        if (!board.isValidRow(board.rows() - row)) {
            System.out.println("Invalid row!");
            return false;
        }
        return true;
    }
    
    /**
     * This is a tester method for this class, serves no purpose in either game
     */
    public static void main(String[] args) {
        Board board = new Board(5,5);
        board.generate(2);
        ConsoleBoardPainter boardPainter =
                new ConsoleBoardPainter();
        boardPainter.paint(board);
        ConsoleSquareRetriever squareRetriever =
                new ConsoleSquareRetriever(board);
        System.out.println(squareRetriever.retrieveSquare());
    }
}
