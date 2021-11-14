package minesweeper.models.board;

import minesweeper.models.game.Move;
import java.util.Random;

/**
 * This class represents a game board. 
 * It contains an array of BoardSquare objects 
 * and methods for creating and updating 
 * the board. 
 * @author Marina McPeak and Mika Ong
 * @version 1.0
 */
public class Board {
    private static final int MIN_ROWS = 1;
    private static final int MIN_COLUMNS = 1;
    private int rows;
    private int columns;
    private BoardSquare[][] board;
    private int freeSquares;
    
    /**
     * This is a default constructor. 
     * It creates a board with default 
     * minimum with and height. 
     */
    public Board() {
        this(MIN_ROWS, MIN_COLUMNS);
    }

    /**
     * Clears the board of all squares
     */
    public void clear()  {
        board = new BoardSquare[rows][columns];
        freeSquares = rows * columns;
    }

    /**
     * This constructor accepts the number of rows and 
     * columns as parameters and initializes the board
     * attribute with an array of appropriate size. 
     * @param rows the height of the board 
     * @param columns the width of the board
     */
    public Board(int rows, int columns) {
      rows = Math.max(MIN_ROWS, rows);
      columns = Math.max(MIN_COLUMNS, columns);
      this.rows = rows;
      this.columns = columns;
      board = new BoardSquare[rows][columns];
      freeSquares = rows * columns;
    }
    
    /**
     * gets the board square
     * @param row row of boardsquare 
     * @param column of boardsquare
     * @return the boardsquare
     */
    public BoardSquare get(int row, int column) {
        return board[row][column];
    }
    
    /**
     * returns the number of rows in the board
     * @return number of rows
     */
    public int rows() {
    	return rows;
    }

    /**
     * returns the number of columns in the board
     * @return number of columns
     */
    public int columns()  {
    	return columns;
    }

    /**
     * Changes the row provided into a boardsquare value.
     * @param row given row of boardsquare
     * @return row as boardsquare value
     */
    public BoardSquare[] getRow(int row) {
        return board[row];
    }
    
    /**
     * Changes the column provided into a boardsquare value
     * @param columnIndex column to change
     * @return column column as boardsquare value.
     */
    public BoardSquare[] getColumn(int columnIndex) {
        BoardSquare[] column = new BoardSquare[columns];
        int count = 0;
        for (BoardSquare[] row: board) {
            column[count++] = row[columnIndex];
        }
        return column;
    }
    
    /**
     * This method generates a random
     * game board with a given number of mines. 
     * 
     * It is randomly decided whether a particular square 
     * is a mine or not; each square's number of mine neighbours 
     * is set.
     * 
     * @param minesCount the initial
     * number of mines on the game board.
     */
    public void generate(int minesCount) {
        Random random = new Random();
        int count = 0;
        while (count < minesCount) {
            int row = random.nextInt(rows());
            int column = random.nextInt(columns());
            if (get(row, column) != null) {
                continue;
            }
            count++;
            board[row][column] = new MineSquare();
            setNeighbours(row, column);
        }
        for (int i = 0; i < rows; i++)  {
            for (int j = 0; j < columns; j++)  {
                if (get(i, j) == null)  {
                    board[i][j] = new SafeSquare();
                }
            }
        }
    }

    /**
     * Sets the neighbours of given squares to safeSquares and increment the given square mine count if found
     * @param row row of given square
     * @param column column of given square
     */
    private void setNeighbours(int row, int column)  {
        for (int i = Math.max(0, row - 1);
                i <= Math.min(rows - 1, row + 1); i++)  {
            for (int j = Math.max(0, column - 1);
                 j <= Math.min(columns - 1, column + 1); j++)  {
                if (get(i, j) == null)  {
                    board[i][j] = new SafeSquare();
                }
                BoardSquare square = board[i][j];
                square.incrementNeighbourMinesCount();
            }
        }
    }

    /**
     * This method takes a Move parameter 
     * and applies that game to the board.
     * 
     * @return the BoardSquare object that
     * corresponds to the game's coordinates.
     */
    public BoardSquare makeMove(Move move) {
        BoardSquare square = board[move.getRow()][move.getColumn()];
        square.open();
        return square;
    }

    /**
     * This method checks whether the board
     * has unopened squares left. 
     * If all squares are open then the game should finish. 
     */
    public boolean hasFreeSquares() {
        return freeSquares == rows * columns;
    }
    
    /**
     * The following methods are used by the InputRetriever 
     * object to validate user input
     */
    
    /**
     * Checks if the move has been done before.
     * 
     * @param move a move to check
     * @return true if the square is already opened, 
     * false otherwise. 
     */
    public boolean isDuplicateMove(Move move) {
        return board[move.getRow()][move.getColumn()].isOpened();
    }  

    /**
     * Checks if the square is open
     * @param move move to check
     * @return is square is open
     */
    public boolean isOpen(Move move)  {
        return get(move.getRow(),
                move.getColumn()).isOpened();
    }

    /**
     * Flags the given move
     * @param move move to flag
     */
    public void flag(Move move)  {
        get(move.getRow(),
                move.getColumn()).flag();
    }

    /**
     * Checks if the integer given is valid
     * @param n the row inputed
     * @return if the row is valid
     */
    public boolean isValidRow(int n) {
        return n >= 0 && n < this.rows;
    }
    
    /**
     * Checks if the integer given is valid
     * @param n the column inputed.
     * @return if the column is valid.
     */
    public boolean isValidColumn(int n) {
        return n >= 0 && n < this.columns;
    }

    /**
     * Opens all squares on the board
     */
    public void openAll()  {
        for (BoardSquare[] row: board)  {
            for (BoardSquare square: row)  {
                if (!square.isOpened())  {
                    square.open();
                }
            }
        }
    }

    /**
     * This method demonstrates the usage of
     * the Board's methods.
     * @param args none expected.
     */
    public static void main(String[] args) {
        Board board = new Board(); //creating the default game board
        board.generate(2);
    }

    /**
     * Necessary accessor and mutator methods
     */
    public int getFreeSquares()  {
        return freeSquares;
    }
}
