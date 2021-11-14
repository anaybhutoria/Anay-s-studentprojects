package model;
/**
 * 
 * This class is used to manipulate PollLists
 * Updated to have exceptions thrown
 * @version 1.0
 * @author Anay Bhutoria and Mika Ong
 */
public class PollList {
	private Poll[] polls;
	private int numOfSeats;
	
/**
 * This constructor makes sure the numberOfPolls and numberOfSeats is greater 
 * @param numOfPolls Used to initialize the number of polls in the PollList
 * @param numOfSeats Used to initialize the number of Seats in the PollList
 * @throws InvalidSetupDataException if number of polls or number of seats are less than or equal to zero
 */	
	public PollList(int inputNumOfPolls, int inputNumOfSeats) throws InvalidSetupDataException {	
		if (inputNumOfPolls <= 0 ) {
			System.out.println("Invalid Action: Number of Polls is less than 1 ");
			throw new InvalidSetupDataException();
		}
		if (inputNumOfSeats <= 0) {
			System.out.println("Invalid Action: Number of Seats in the election is less than 1 ");	
			throw new InvalidSetupDataException();
		}
		polls = new Poll[inputNumOfPolls];
		numOfSeats = inputNumOfSeats;
	}
	
	/**
	 * This method returns the number of seats
	 * @return number of seats to be used in other classes but not manipulated
	 */
	public int getNumOfSeats() {
		return numOfSeats;
	}
	
	/**
	 * This method returns the polls array   
	 * @return the polls array to be used in other classes but not manipulated
	 */
	public Poll[] getPolls() {	
		return polls;
	}

	/**
	 * This Method adds a poll to the PollList if there is space available,
	 * if the poll is not null, and doesn't already exist in the PollList
	 * @param newPoll that is going to be added to the pollList
	 */
	public void addPoll(Poll newPoll) {
		if (newPoll == null) {	//if poll argument added is null then print an error and return
			System.out.println("Error : Poll is null, poll has not been added");
			return;
		}
		int index = 0; //comparing the poll in the pollList with the argument
		for (;index < polls.length && polls[index] != null; index++) {
			if (polls[index].getPollName().equalsIgnoreCase(newPoll.getPollName())) {
				polls[index] = newPoll;
				return;
			}
		} //if array is full then print error and return
		if (index == polls.length) {
			System.out.println("List is full. No more polls can be added.\n");
			return;
		}
		polls[index] = newPoll;
		}
		
	/**
	 * This method gets an aggregate of the parties in the array given as an argument,
	 * It also makes sure the number of seats and percentage of votes do now collectively 
	 * exceed the maximums, and puts all of them in a poll and returns it
	 * @param partyNames an array of partyNames used to find the aggregate and normalize all of them 
	 * @return a poll to put all the aggregated and normalized parties into.
	 * @throws InvalidSetupDataException Exception that is thrown if the setting inputed data is invalid.
	 * 
	 */
	public Poll getAggregatePoll(String[] partyNames) throws InvalidSetupDataException {
		Poll aggregatePoll = new Poll("Aggregate", partyNames.length ); // creating a new poll and adding the averaged data of each party in it
		for(int indexParty = 0; indexParty < partyNames.length; indexParty++) { //then normalizing that poll and returning it
			String currentPartyName = partyNames[indexParty];
			Party averageOfParty = getAveragePartyData(currentPartyName);
			aggregatePoll.addParty(averageOfParty);
		}
		try {
			return adjustPollToMaximums(aggregatePoll);
		} catch (InvalidPartyDataException e) {
			System.out.println("Invalid party data inputed please check party data");
			return null;
		}
	}
	
	/**
	 * This method takes in a string for the party name and gets the average party data throughout all polls
	 *  then returns a party
	 * @param partyName is used to find the average party data for that string
	 * @return a party which has the same name but now has the data averaged from all the polls 
	 */
	public Party getAveragePartyData(String  partyName) {
		//adding up all the data for the party from all the polls
		Party partyInput = new Party(partyName);
		float averageSeats = 0;
		float averagePercentVotes = 0;
		int partiesInPollCount = 0;
		for (int index = 0; index < polls.length && polls[index] != null ; index++) {	
			Poll pollIteration = polls[index];
			Party partyInPoll = pollIteration.getParty(partyName);
			if(partyInPoll != null) { 
				partiesInPollCount++;
				averageSeats += partyInPoll.getProjectedNumberOfSeats();
				float indexPercentVotes = partyInPoll.getProjectedPercentageOfVotes();
				averagePercentVotes += indexPercentVotes;
			}
		}// dividing the total seats and votes by how many polls contained that party
		if (partiesInPollCount == 0) partiesInPollCount = 1; 
		averageSeats = averageSeats / partiesInPollCount;
		averagePercentVotes = averagePercentVotes/partiesInPollCount;
		try {
			partyInput.setProjectedNumberOfSeats(averageSeats);
			partyInput.setProjectedPercentageOfVotes(averagePercentVotes);
		} catch (InvalidPartyDataException e) {
			e.printStackTrace();
		}			
		return partyInput;
	}
	
	/**
	 * This method is used to normalize number of seats and percentage of votes 
	 * of each party in the poll to reflect the total numbers 
	 * @param aPoll that need to be adjusted/normalized to the maximums 
	 * @return the same poll as the argument but with the data normalized within each party
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	public Poll adjustPollToMaximums(Poll aPoll) throws InvalidPartyDataException {
		float maximumVotes = 0;
		float maximumSeats = 0; //calculating the total votes and seats by adding up every party's data
		Party[]	pollArray = aPoll.getPartiesSortedBySeats();
		for(int indexParty = 0; indexParty < pollArray.length ;indexParty++) {
			Party currentParty = pollArray[indexParty];
			float seatsIteration = currentParty.getProjectedNumberOfSeats();
			float percentVotesIteration = currentParty.getProjectedPercentageOfVotes();
			maximumSeats += seatsIteration;
			maximumVotes += percentVotesIteration;
		}//normalizing the data only if the calculated total it is above the actual total
		for(int iteration = 0 ; iteration < pollArray.length ;iteration++) {	
			Party currentParty = pollArray[iteration];
			float divisionPercentVotes = (currentParty.getProjectedPercentageOfVotes() );
			if(maximumVotes > 1.0) {
				divisionPercentVotes = divisionPercentVotes/ maximumVotes; 
			}
			currentParty.setProjectedPercentageOfVotes(divisionPercentVotes);
			float divisionSeats = (currentParty.getProjectedNumberOfSeats());
			if(maximumSeats > this.numOfSeats) {
				divisionSeats = (divisionSeats / maximumSeats)*this.numOfSeats;	
			}
			currentParty.setProjectedNumberOfSeats(divisionSeats);
		}
		return aPoll;
	}
	
	/**
	 * This method returns an array of all the parties seen in the PollList 
	 * in order to be able to see all choices to vote for in the election
	 * @return string array for all parties in the pollList
	 */	
	public String[] getPartyNames() {
		String[] nameArray = new String[50]; // this block iterates through the pollList then the parties in the poll to add them to the new array 
		for(int index = 0; index < polls.length && polls[index] != null; index++) {
			Poll pollIteration = polls[index];
			Party[] partyArray = pollIteration.getPartiesSortedBySeats();
			for(int partyindex = 0; partyindex < pollIteration.getNumberOfParties(); partyindex++) {
				String currentPartyName = partyArray[partyindex].getName();
				int  temp = 0;
				int nameArrayIndex = 0;
					for(; nameArrayIndex < nameArray.length && nameArray[nameArrayIndex] != null ; nameArrayIndex++) {
						if (nameArray[nameArrayIndex].equalsIgnoreCase(currentPartyName)) {
							temp = 1;	
						}
					}
				if (temp == 0) {
					nameArray[nameArrayIndex] = currentPartyName;
				}		
			}
		}  // making a new array of the same size as the amount of parties in the previous array then transferring them to this array
		int newIndex = 0;  
		String[] newArray = new String[newIndex];
		for(int i = 0; i < newIndex; i++) {
			newArray[i] = nameArray[i];	
		}	
		return newArray;	
	}
	
	/**
	 * This method is used to return the instance values in this class when called in a 
	 * print function
	 * @return number of seats in the pollList as a string
	 */
	@Override
	public String toString() {
		return "Number of seats: " + numOfSeats;
	}
}
