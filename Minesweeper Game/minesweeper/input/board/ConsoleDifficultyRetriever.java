package minesweeper.input.board;

import minesweeper.Utils;
import minesweeper.models.game.Difficulty;
import java.util.Scanner;

/**
 * This class is used in the text-based version of the game to retrieve the difficulty 
 * the player has inputed, this class has not been used in the user interface version.
 * 
 * @author Marina Mcpeak, Anay Bhutoria
 * @version 1.0 
 */
public class ConsoleDifficultyRetriever implements DifficultyRetriever{
    private Scanner scanner = new Scanner(System.in);

    /**
     * This  method is used to print the difficulty options in an easy to read list and prompt the user to 
     * input their preferred difficulty. then return the chosen difficulty.
     * @return difficulty
     */
    @Override
    public Difficulty retrieveDifficulty()  { 
        String[] values = new String[]	
           {"EASY (E)", "MEDIUM (M)",  //printing the text-based difficulty options
           "HARD (H)", "CUSTOM (C)"}; 
        String difficulty =					
            Utils.getValidInput(
            new String[] {"E", "M", "H", "C"},
            "Choose the game's difficulty: " +
            Utils.makeErrorMessageList(values) +
            "Preferred difficulty: ",
            Utils.makeErrorMessageList(values),  
            new Scanner(System.in));		// taking the input and using it to 
       		System.out.println("diff: " + difficulty);//set the difficulty of the game
        switch (difficulty.toUpperCase())  {
            case "E":					
                return Difficulty.EASY;
            case "M":
                return Difficulty.MEDIUM;
            case "H":
                return Difficulty.HARD;
            case "C":
                return retrieveCustomDifficulty();
        }
        return Difficulty.EASY;
    }
    
   /**
     * This method makes sure the input is an integer
     * @return int value.
     */
    public int getNumber(String prompt){ 
        System.out.println(prompt);
        Scanner sc = new Scanner(System.in);
        while (true) {
            String input = sc.next();
            try {
                int num =  Integer.parseInt(input);
                while (num < 5) {
                    System.out.println(prompt);
                    input = sc.next();
                    num =  Integer.parseInt(input);
                }
                return num;  
            } catch (NumberFormatException ne) {
                System.out.println("**Invalid Action,Try Again");
            }
        }
    }
    
    /**
     * This method retrieves the attributes for the custom difficulty and
     * sets it as the custom difficulty mode then retrieves it
     * @return Difficulty
     */
    private Difficulty retrieveCustomDifficulty()  {    
      
        int boardHeight = getNumber("Enter the board height : ");
       
        int boardWidth = getNumber("Enter the board width : ");	      
        
        int numOfMines = getNumber("Enter the board mines number : ");

        Difficulty difficulty = Difficulty.CUSTOM;	//setting the attributes of the custom difficulty
        difficulty.setColumns(boardWidth);	//and returning the difficulty
        difficulty.setRows(boardHeight);
        difficulty.setMinesNumber(numOfMines);
        difficulty.setPoints(Math.max(1,difficulty.getMinesNumber()/difficulty.getRows() * difficulty.getColumns()));
        return difficulty;
    }
    
	/**
	 * This method is used to test the class, and serves no function in test based version.
	 * @param args
	 */
    public static void main(String[] args) {
        ConsoleDifficultyRetriever difficultyRetriever =
                new ConsoleDifficultyRetriever();
        Difficulty difficulty = difficultyRetriever.retrieveDifficulty();
        System.out.println(difficulty);
    }
}
