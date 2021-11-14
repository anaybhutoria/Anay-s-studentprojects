package minesweeper.input.game.action;

import minesweeper.models.game.Action;

/**
 * This interface is used to make sure the ConsoleActionRetriever
 * have these functions when edits are made to make sure the game still works properly 
 * @author Marina Mcpeak and Anay Bhutoria
 * @version 1.0
 */
public interface ActionRetriever {
    Action retrieveAction();
}
