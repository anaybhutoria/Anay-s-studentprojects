package minesweeper;

import minesweeper.models.game.Minesweeper;

/**
 * @author Marina McPeak
 * @version 1.0
 */
public class Main {
  
  /**
   * Generates the minesweeper game
   * @param args no command line arguments expected.
   */
  public static void main(String[] args) {
    Minesweeper minesweeper = new Minesweeper();
    minesweeper.play();
  }
} 