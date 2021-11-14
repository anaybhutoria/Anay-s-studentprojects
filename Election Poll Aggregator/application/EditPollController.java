/**
 * This is the controller class for EditPollView.fxml file
 * in the poll tracker application
 * @version 1.0
 * @author Izzah Nazir Ahmad and Mika Ong
 */

package application;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.paint.Color;
import model.*;

public class EditPollController extends PollTrackerController  {
	
	@FXML
    private Label ErrorLabel;

    @FXML
    private Label PercentageOfVotesLabel;

    @FXML
    private ComboBox<Integer> NoOfSeats_combo;

    @FXML
    private Label SeatsLabel;

    @FXML
    private ComboBox<Integer> PercentageOfVotes_combo;

    @FXML
    private Button ClearButton;

    @FXML
    private Label PollToEditLabel;

    @FXML
    private Label NoOfSeatsLabel;

    @FXML
    private Button UpdatePartyButton;

    @FXML
    private ComboBox<String> EditParty_combo;

    @FXML
    private Label percent;

    @FXML
    private ComboBox<String> EditPoll_combo;

    @FXML
    private Label PartyToUpdateLabel;
    
    @FXML
    private TextField text_ProjNumOfSeats;
    
    /**
     *This method clears all the section in the combo boxes 
     *when clicked. 
     * @param event
     */ 
    @FXML
    void ClearPoll(ActionEvent event) {
     	EditPoll_combo.getSelectionModel().clearSelection();
    	EditParty_combo.getSelectionModel().clearSelection();
    	text_ProjNumOfSeats.clear();
    	PercentageOfVotes_combo.getSelectionModel().clearSelection();
    }
    
    /**
     * This method updates the information in Poll 
     * that is selected by the user. 
     * If invalid data is inputed the user will be prompted to reinput valid data.
     * @param event
     * @throws InvalidSetupDataException 
     */ 
    @FXML
    void UpdateParty(ActionEvent event) throws InvalidSetupDataException {
    	if (getPollList() != null) {  
	    	String PollInput = EditPoll_combo.getValue();
	    	String PartyInput = EditParty_combo.getValue();
	    	Integer VoteInput = PercentageOfVotes_combo.getValue();
	    	PollList myPollList = getPollList();
	    	Poll[] myPolls = myPollList.getPolls();
	    	PollList newPollList = new PollList(myPolls.length, myPollList.getNumOfSeats());
	    	for (int n = 0; n< myPolls.length; n++ ) {
				if (myPolls[n].getPollName().equals(PollInput)) {
					Poll iterPoll = myPolls[n];
					Poll newPoll = new Poll(iterPoll.getPollName(), iterPoll.getNumberOfParties());
					for (int i = 0; i < iterPoll.getNumberOfParties(); i++) {
						String [] partyNames = getFactory().getPartyNames();
						String partyName = Character.toString(PartyInput.charAt(0));
							if (partyNames[i].equals(partyName)) {
								float voteDecimal = (float) (VoteInput/100.0);
								Party newParty = new Party(partyNames[i]);
								try {
									newParty.setProjectedPercentageOfVotes(voteDecimal);
								} catch (InvalidPartyDataException e1) {
									//Error will not occur because vote input is a combo box
								}
								boolean validInput = false;
								while (!validInput) {
									String seats = text_ProjNumOfSeats.getText();
									try {
										Integer.parseInt(seats);
									} catch(NumberFormatException e1) {
										ErrorLabel.setText("Invalid data inputed. Seats must be a positive integer!");
										text_ProjNumOfSeats.clear();
										return;
									}
									Integer SeatInput = Integer.parseInt(seats);
									if (SeatInput > myPollList.getNumOfSeats()) {
										ErrorLabel.setText("Invalid data inputed. Seats must be below " + myPollList.getNumOfSeats() + "!");
										text_ProjNumOfSeats.clear();
										return;
									}
									try {
										newParty.setProjectedNumberOfSeats(SeatInput);
									} catch (Exception e) {
										ErrorLabel.setText("Invalid data inputed. Seats must be a positive integer!");
										text_ProjNumOfSeats.clear();
										return;
									}
									if (SeatInput >= 0) {
										validInput = true;
									} 
								}
								ErrorLabel.setTextFill(Color.GREEN);
								ErrorLabel.setText("Submitted");
								newPoll.addParty(newParty);
							} else {
								newPoll.addParty(iterPoll.getParty(partyNames[i]));
							}
					}	
					newPollList.addPoll(newPoll);
				} else {
					newPollList.addPoll(myPolls[n]);
				}
			}
	    	setPollList(newPollList);   	
    	}
    }
    
    /**
     * This method is used for initializing 
     * and putting in the values for 
     * the combo boxes. 
     */
	@Override
	public void refresh() {
		if (getPollList()!=null) {
			SeatsLabel.setText("/" + String.valueOf(getPollList().getNumOfSeats()));
			//Initializing poll names in the combo box 
			ObservableList<String> pollArray = FXCollections.observableArrayList();
			Poll[] currentPoll = getPollList().getPolls();
			for (int i = 0; i< currentPoll.length; i++) {
				String pollIter = currentPoll[i].getPollName();
				pollArray.add(pollIter);
				String [] currentParty = getPollList().getPartyNames();			
			}
			EditPoll_combo.setItems(pollArray);
			//Initializing party names in the combo box	
			EditPoll_combo.getSelectionModel().selectedIndexProperty().addListener(
					new ChangeListener<Number>() {
						@Override
						public void changed(ObservableValue observable, Number oldValue, Number newValue) {
							int index = newValue.intValue();
							setPartySelect(index, currentPoll);
						}
					}
			);
			//Initializing votes for user friendly combo box 
			ObservableList<Integer> votes = FXCollections.observableArrayList(); 
			for(Integer voteInt = 0; voteInt <= 100; voteInt++) {
				votes.add(voteInt);  
			}
			PercentageOfVotes_combo.setItems(votes);
		}
	}
	
	/**
	 * Sets the items for EditParty_combo
	 * @param index index of poll selected
	 * @param currentPoll Polls currently being used
	 */
	private void setPartySelect(int index, Poll[] currentPoll) {
		ObservableList<String> partyArray = FXCollections.observableArrayList();
		for (int i = 0; i< currentPoll.length; i++) {
			String pollIter = currentPoll[i].getPollName();
			String [] currentParty = getPollList().getPartyNames();
			if (i == index) {
				for (int j = 0; j< currentParty.length; j++) {
					Party party = currentPoll[i].getParty(currentParty[j]);
					String partyIter = currentParty[j];
					partyArray.add(partyIter + " (" + Math.round(party.getProjectedPercentageOfVotes()*100) + "% of votes, "
						+ party.getProjectedNumberOfSeats()+ " seats"+")");
					EditParty_combo.setItems(partyArray);
				} 
			} 				
		}
	}
}
