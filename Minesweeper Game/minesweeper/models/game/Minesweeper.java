package minesweeper.models.game;

import minesweeper.Utils;
import minesweeper.display.board.BoardPainter;
import minesweeper.display.board.ConsoleBoardPainter;
import minesweeper.input.board.ConsoleDifficultyRetriever;
import minesweeper.input.board.DifficultyRetriever;
import minesweeper.input.game.action.ActionRetriever;
import minesweeper.input.game.action.ConsoleActionRetriever;
import minesweeper.input.game.flag.ConsoleFlagRetriever;
import minesweeper.input.game.flag.FlagRetriever;
import minesweeper.input.game.move.ConsoleMoveInputRetriever;
import minesweeper.models.board.Board;
import minesweeper.models.board.BoardSquare;
import minesweeper.models.player.Player;
import minesweeper.models.player.PlayerManager;

import java.util.Scanner;

/**
 * This class represents an instance of
 * a Minesweeper game. 
 * @author Marina McPeak & Anay Bhutoria
 * @version 1.0
 */
public class Minesweeper extends BoardGame {
    private Board board;
    private int minesNumber;
    private BoardPainter painter = new ConsoleBoardPainter();
    private Player player;
    private PlayerManager playerManager = new PlayerManager();
    private DifficultyRetriever difficultyRetriever = new ConsoleDifficultyRetriever();
    private ActionRetriever actionRetriever =
            new ConsoleActionRetriever();

    /**
     * Basic constructor for the Minesweeper game
     */
    public Minesweeper() {
        board = new Board();
    }
    
    /**
     * Minesweeper game with set rows and columns
     * @param rows number of rows on board
     * @param columns number of columns on board
     */
    public Minesweeper(int rows, int columns) {
        board = new Board(rows, columns);
    }

    /**
     * Sets up the board of the game
     */
    private void setup() {
        board = new Board(getDifficulty().getRows(),
                getDifficulty().getColumns());
        minesNumber = calculateMinesNumber();
        board.generate(minesNumber);
    }
    
    /**
     * Plays the game 
     */
    @Override
    public void play() {
        displayWelcomeMessage();
        boolean shouldPlay = true;
        boolean lose  = false;
        while (shouldPlay) {
            boolean hasWon = true;
            player = getPlayerManager().getCurrentPlayer();
            setDifficulty(difficultyRetriever.retrieveDifficulty());
            setup();
            player.setMoveInputRetriever(new ConsoleMoveInputRetriever(board));
            player.setFlagRetriever(new ConsoleFlagRetriever(board));
            while (board.getFreeSquares() > minesNumber && !lose) {
                painter.paint(board);
                Action action = actionRetriever.retrieveAction();
                if (action == Action.FLAG)  {
                    Move flag = player.getFlag();
                    board.flag(flag);
                } else {
                	Move move = player.getNextMove();
                    BoardSquare square = board.makeMove(move);
                    if (square.isMine()) {
                        hasWon = false;
                        lose = true;
                    }
                }
            }
            board.openAll();
            painter.paint(board);
            if (hasWon) {
                displayWinMessage();
                player.incrementPoints(
                    getDifficulty().getPoints());
            } else {
                displayLoseMessage();
                player.decrementPoints(getDifficulty().getPoints());
            }
            displayPlayerPoints();
            shouldPlay = askPlayAgain();
            board.clear();
        }
    }

    /**
     * Asks the player if they want to play again
     * @return if the player wants to play again
     */
    private boolean askPlayAgain()  {
        String[] values = new String[] {"y", "n"};
        String input = Utils.getValidInput(
                values,
                "Would you like to play again? (y/n): ",
                Utils.makeErrorMessage(new String[] {"y", "n"}),
                new Scanner(System.in));
        return input.equalsIgnoreCase("y");
    }

    /**
     * displays the welcome messgae to the board.
     */
    private void displayWelcomeMessage() {
        System.out.println(
            ">>>> Welcome to Minesweeper! <<<<\n");
    }
    
    /**
     * Displays the win message to the board
     */
    private void displayWinMessage() {
        System.out.printf("Congratulations, %s, you won!\n",
                player.getName());
    }
    
    /**
     * Displays the loss message to the board
     */
    private void displayLoseMessage() {
        System.out.printf("Sorry, %s, you lose!\n",
                player.getName());
    }
    
    /**
     * Prints player points to the leaderboard
     */
    private void displayPlayerPoints() {
        System.out.printf("You now have %d points!\n",
                player.getPoints());
    }
    
    /**
     * This method determines the number 
     * of mines based on the game's difficulty. 
     * 
     * @return int the number of mines. 
     */
    private int calculateMinesNumber() {
        return getDifficulty().getMinesNumber();
    }
    /**
     * This method is a getter for PlayerManager
     * @return playerManager
     */
    public PlayerManager getPlayerManager() {
		return playerManager;
	}

    /**
     * Test method 
     * @param args
     */
    public static void main(String[] args) {
        Minesweeper minesweeper =
                new Minesweeper();
        minesweeper.play();
    }

	

} 