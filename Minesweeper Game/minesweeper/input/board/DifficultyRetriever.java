package minesweeper.input.board;

import minesweeper.models.game.Difficulty;

/**
 * This interface is used to implement the minimum methods for the ConsoleDifficultyRetriver
 * @author Marina Mcpeak and Anay Bhutoria
 * @version 1.0
 */
public interface DifficultyRetriever {
    Difficulty retrieveDifficulty();
}
