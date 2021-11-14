package minesweeper.input.game.move;

import minesweeper.models.board.Board;
import minesweeper.models.game.Move;

/**
 * This interface declares methods
 * for retrieving input
 * from the user. 
 * @author Izzah Nazir Ahmad
 * @version 1.0
 */
public abstract class MoveInputRetriever { 
   
   /**
     * Is used to determine whether 
     * the next move is valid or not. 
     */
   protected Board board;
    
   /**
    * This method takes an object of type board.
    * The method is used to reference board from the 
    * Board class. 
    * @param board
    */
   public MoveInputRetriever(Board board) {
        this.board = board;
    }  
   
   /**
    * This method is used in the ConsoleMoveInputRetriever 
    * to retrieve the user's next move in the game. 
    */
   public abstract Move retrieveNextMove();   
}
