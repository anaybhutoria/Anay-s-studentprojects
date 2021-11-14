/**
 * This class is the controller for the SetupPollTrackerView.fxml file in
 * the Poll Tracker application, This class allow the user to create
 * a factory and PollList to their specifications and handles exceptions
 * @version 1.0
 * @author Anay Bhutoria
 */

package application;



import java.util.Scanner;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import model.Factory;
import model.InvalidSetupDataException;
import model.PollList;

public class SetupPollTrackerController extends PollTrackerController {

    @FXML
    private Label label_NumOfPolls;
    
    @FXML
    private ComboBox<Integer> combo_Parties;

    @FXML
    private ComboBox<Integer> combo_Polls;
    
    @FXML
    private TextField text_SeatNumber;
    
    @FXML
    private Button button_Reset;

    @FXML
    private Label label_NumOfSeats;

    @FXML
    private Label label_Welcome;

    @FXML
    private Label label_NumOfParties;

    @FXML
    private Button button_Submit;
    
    @FXML
    private Label label_Invalid;
    
    /**
     * makes sure that the application catches the invalid data exception 
     * @return 0 to make the submit not go through the application so it doesn't crash
     */
    public int getNumber(){ 
        	String textInput = text_SeatNumber.getText();
            try {
                return Integer.parseInt(textInput);
            }catch (Exception ne) {
                return 0;
            }
    }
    
   /**
    * Submitting the inputed combo-box values to the application
    * when User clicks submit button
    * @param event
    * @throws InvalidSetupDataException if invalid data has been added, but the GUI handles the input to make sure
    * the program does not throw exception 
    */
    @FXML
    void submission(ActionEvent event) throws InvalidSetupDataException  {
    	Integer inputPolls = combo_Polls.getValue();
    	Integer inputSeats = getNumber();
    	Integer inputParties = combo_Parties.getValue();
    	if (inputSeats <= 0 || inputPolls == null || inputParties == null) { // making the GUI handle the errors so exception is not thrown
    		label_Invalid.setTextFill(Color.RED);
    		if (inputSeats <=0 ) {// giving the user an appropriate message depending on the error
    			label_Invalid.setText( "**Invalid Action, seat number is less than 1 or invalid input has been entered, please try again");
    			text_SeatNumber.setText(""); 
    		}else if(inputPolls == null) {
    			label_Invalid.setText( "**Invalid Action, number of polls has not been selected, please try again");
    			combo_Polls.getSelectionModel().clearSelection();
    		}else { 
    			label_Invalid.setText( "**Invalid Action, number of parties has not been entered, please try again");
    			combo_Parties.getSelectionModel().clearSelection();
    		}
    		return;
    	}
    	// making the party names (String array) for the factory to set as names
    	String[] tempParties = new String[inputParties];
    		for (int i = 1; i <= inputParties; i++) {
    			String temp = String.valueOf(i);
    			tempParties[i-1] = temp;
    		}
    	//making a new factory to replace preset factory and making a random pollList
    	Factory inputFactory = new Factory(inputSeats);
    	inputFactory.setPartyNames(tempParties);
    	setPollList(inputFactory.createRandomPollList(inputPolls));
    	setFactory(inputFactory);
    	label_Invalid.setTextFill(Color.GREEN); //if the data inputed is valid it will submit and replace the text 
    	label_Invalid.setText( "Submitted!"); // to let the user know that the data inputed has gone through
    }
      
    /**
     * Clearing the selection of all combo-boxes and the text-box when reset button is clicked
     * @param event
     */ 
    @FXML
    void resetting(ActionEvent event) {
    	combo_Polls.getSelectionModel().clearSelection();
    	combo_Parties.getSelectionModel().clearSelection();
    	text_SeatNumber.setText("");
    }

    /**
     * This method from abstract parent, serves no purpose in this tab
     * Note: this was not chosen as the clear method since it would erase
     * the selection every time you switch the tab, and would be seen as a design flaw,
     *  since the user would have to re-input the data every time he switched the tab.
     */
	@Override
	public void refresh() {	
	}
	
/**
 * This method Initializes the tab by getting the items in the combo-boxes ready 
 */
	@FXML
	public void initialize() {
		//Initializing  Poll Combo-box items(list)  
		ObservableList<Integer> pollbox = FXCollections.observableArrayList();
		for(Integer pollInt = 1; pollInt <= 30; pollInt++) pollbox.add(pollInt);  
		combo_Polls.setItems(pollbox);
		//Initializing  Parties Combo-box items(list)
		ObservableList<Integer> partybox = FXCollections.observableArrayList(); 
		for(Integer partyInt = 1; partyInt <= 15; partyInt++) partybox.add(partyInt);  
		combo_Parties.setItems(partybox);
	}
}



