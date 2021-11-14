package minesweeper.input.game.action;

import minesweeper.models.game.Action;
import java.util.Scanner;

/**
 * This class is used to print a statement to prompt the user for an action
 * then retrieve the action of the player,
 * whether it is a flag placement or button reveal
 * @author Marina Mcpeak and Anay Bhutoria
 * @version 1.0
 */
public class ConsoleActionRetriever
                    implements ActionRetriever  {
    private Scanner scanner = new Scanner(System.in);

    /**
     * This method makes sure the input is an integer.
     * @return int which is valid so program doesnt break
     */
    public int getNumber(){ 
        Scanner sc = new Scanner(System.in);
        while (true) {
            String input = sc.next();
            try {
                return Integer.parseInt(input);
            }catch (NumberFormatException ne) {
                System.out.println("**Invalid Action,Try Again");
            }
        }
    }
    
    /**
     * this method is used to print a statement to prompt the user for an action
     * then retrieve the action of the player
     * @return Action
     */
    @Override
    public Action retrieveAction()  { // printing the prompt for the player to input a number 
        System.out.println("Next move:");
        System.out.println("1. Place Flag");
        System.out.println("2. Choose Coordinate");
        int action = getNumber();
        while ( action !=1 && action !=2) {
        	System.out.println("**Invalid Action, Try Again");
        	action = scanner.nextInt(); // if input is a possible action, the action will be returned
        }
        if (action == 1) {    	
           	 return Action.FLAG;
        }           
        else{   	
           	return Action.MOVE;       
        }
    }
   
    /**
     * This method serves no purpose and is only used to test this class
     * @param args
     */
    public static void main(String[] args) {
        ConsoleActionRetriever actionRetriever = new ConsoleActionRetriever();
        System.out.println(actionRetriever.retrieveAction());
    }
}
