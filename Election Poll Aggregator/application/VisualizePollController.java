/**
 * Controller for the VisualizePollView Class
 * Shows the results from a PollList used in the PollTrackerApp
 * @author Mikaela Ong
 * @version 1.0
 */

package application;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.chart.PieChart;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import model.*;

public class VisualizePollController extends PollTrackerController{
	private String[] partyNames;
	private PollList pollList;
	private Poll[] polls;
	private int numSeats;
	private int numPolls;
	private int numOfParties;
	
	@FXML
    private Label numOfSeats;
		
    @FXML
    private PieChart ProjectedSeats;

    @FXML
    private PieChart ProjectedVotes;
    
    @FXML
    private Label numOfPolls;

    @FXML
    private ComboBox<String> PollType;
        
    @FXML
    void initialize() {
    	PollType.getSelectionModel().selectedIndexProperty().addListener(
        		new ChangeListener<Number>() {
        			@Override
        			public void changed(ObservableValue observable, Number oldValue, Number newValue) {
        				//Shows the Poll data for the chosen Poll.
        				int index = newValue.intValue();
        				
        				if (index >= 0)
							try {
								setData(index);
							} catch (InvalidSetupDataException e) {
								
								
							}
        			}
        		}
        );
    }
    
    /**
     * Method from abstract parent
     * All variables initialized here
     */
	@Override
	public void refresh() {
		clearView();
		//Initialize variables needed to extract relevant data.
		if (getPollList() != null) {
			pollList = getPollList(); 
			polls = pollList.getPolls();
			numSeats = pollList.getNumOfSeats();
			partyNames = getFactory().getPartyNames();
			numPolls = 0;
			numOfParties = partyNames.length;
			for (Poll poll : polls) {
				numPolls ++;
			}
			numPolls ++;//For aggregate poll data
			//Generates a String list for the different polls and an aggregate poll and sets the list in PollType.
			String[] pollType = new String[numPolls];
			for (int pollNum = 1; pollNum < numPolls; pollNum++) {
				String pollName = polls[pollNum - 1].getPollName();
				pollType[pollNum-1] = pollName;
			}
			pollType[numPolls-1] = "Aggregate";
			PollType.setItems(FXCollections.observableArrayList(pollType)); 	
		}
	}
	
	/**
	 * Sorting parties by seats so both graphs use the same colour for each party.
	 * @param partyList the list of the parties in the poll.
	 * @return the list of sorted parties by who won the aggregate poll in seats.
	 */
	public String[] sortParties(Party[] partyList) {
		String[] sortedParties = new String[partyList.length];
		for (int index = 0; index < partyList.length; index++) {
			sortedParties[index] = partyList[index].getName();
		}
		return sortedParties;
	}
	
	/**
	 * Sets the data for the pie chart.
	 * @param index the index of the selected choice in poll type
	 * @throws InvalidSetupDataException 
	 */
	private void setData(int index) throws InvalidSetupDataException {
		setLabels();
        Poll currentPoll; 
        String[] sortedParties;
        PieChart.Data[] seatData = new PieChart.Data[numOfParties];
		PieChart.Data[] voteData = new PieChart.Data[numOfParties];
		if (index == numPolls-1) {
    		currentPoll = pollList.getAggregatePoll(partyNames);
    	} else {
    		currentPoll = polls[index];      			    		
    	}
		//Sorting the parties so each party has the same colour in all graphs. The colours are assigned by the results of the aggregate poll.
		sortedParties = sortParties(pollList.getAggregatePoll(partyNames).getPartiesSortedBySeats()); 
		for (int counter = 0; counter < numOfParties; counter ++) {
			Party currentParty = currentPoll.getParty(sortedParties[counter]);
			double seats = currentParty.getProjectedNumberOfSeats();
			double votes = currentParty.getProjectedPercentageOfVotes();
			double votesRounded = Math.round(votes *100.0);
			int seatsRounded = (int) seats;
			seatData[counter] = new PieChart.Data(sortedParties[counter] + "- " +  seatsRounded + " Seats", seats);
			voteData[counter] = new PieChart.Data(sortedParties[counter] + "- " +  votesRounded + " %", votes);
		}
		ProjectedSeats.setData(FXCollections.observableArrayList(seatData));
		ProjectedVotes.setData(FXCollections.observableArrayList(voteData));
	}
	
	/**
	 * Setting the labels to show the number of seats and polls.
	 */
	private void setLabels() {
		if (numSeats != 0) {
		numOfSeats.setText("Number of Seats: " + numSeats);
		numOfPolls.setText("Number of Polls: " + (numPolls -1));
		ProjectedSeats.setTitle("Projected Number of Seats");
		ProjectedVotes.setTitle("Projected Percentage of Votes");
		}
	}
	
	/**
	 * Clears the view of the pie charts and labels
	 */
	private void clearView() {
		numOfSeats.setText("");
		numOfPolls.setText("");
		ProjectedSeats.getData().clear();
		ProjectedVotes.getData().clear();
		ProjectedSeats.setTitle(null);
		ProjectedVotes.setTitle(null);
		PollType.getSelectionModel().clearSelection();
	}

}