package minesweeper.display.board;

import minesweeper.models.board.Board;

/**
 * This class prints a given board to the console.
 * @author Mikaela Ong
 * @version 1.0
 */
public class ConsoleBoardPainter implements BoardPainter{
	
    /**
	 *  Prints the board to the console
	 *  If the square has been opened then it shows the squares symbol
	 *  @param board the board that is currently being played
     */
	public void paint(Board board)  {
        String spaces = board.rows() > 9 ? "  " : " "; // painting the board after every move
        for (int i = 0; i < board.rows(); i++) {
            String rowlabel = (board.rows() - i) + "";
            System.out.print(board.rows() > 9 &&
                    (board.rows() - i) < 10 ? " " : "");
            System.out.print(rowlabel + " ");
            for (int j = 0; j < board.getRow(i).length; j++) {
                System.out.print(board.get(i,j) + " ");
            }
            System.out.println();
        }
        System.out.print(spaces + " ");
        char c = 'a';
        for (int k = 0;
             k < board.getRow(0).length; k++) {
            System.out.print(c++ + " ");
        }
        System.out.println();
    }
	
	/**
     * This method shows the usage
     * of the ConsoleBoardPainter class.
     * @param args none expected.
     */
    public static void main(String[] args) {
        Board board = new Board(15,15);
        board.generate(6);
        ConsoleBoardPainter painter = new ConsoleBoardPainter();
        painter.paint(board);
    }
}