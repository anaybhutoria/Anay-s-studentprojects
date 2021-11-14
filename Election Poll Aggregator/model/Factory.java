package model;

import java.util.Random;
import java.util.Arrays;
import java.util.*;


/**
 * This class creates Parties, Polls and PollLists either randomly or by prompting the end user for the data
 * for the polls and parties.
 * @version 1.0
 * @author Marina McPeak and Mika Ong
 */
public class Factory {
	/**
	 * The number of seats available in the election covered
	 * by the polls
	 */
	private int numOfSeats;
	/**
	 * The default names of all the parties participating in the
	 * election
	 */
	private String[] partyNames = {"BQ","CPC","Green","Liberal","NDP","PPC","Rhinoceros"};
	
	private InvalidSetupDataException a  ;
	public Factory(int numOfSeats) {
		this.numOfSeats = numOfSeats;
	}

	/**
	 * Creates a new party object with the name
	 * provided as an argument.
	 * @param partyName the name of the party
	 * @param maximumSeats the maximum number of seats for that party ([0; 100])
	 * @param maximumPercent
	 * @return the Party object
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	public Party createRandomParty(String partyName, int maximumSeats, int maximumPercent) {
		Random rand = new Random();
		int projectedSeats;
		float projectedVotes;
		while (true) {
			projectedSeats = rand.nextInt(maximumSeats);
			projectedVotes = (float) rand.nextInt(maximumPercent) / 100;
			if (projectedVotes - (float) projectedSeats / maximumSeats <= 0.05) {
				break; //Have to generate seats and votes again
			}
		}
		// At this point the party with correct votes and seats has been generated
		try {
			return new Party(partyName, projectedSeats, projectedVotes);
		} catch (InvalidPartyDataException ipde) {
			ipde.printStackTrace();
		}
		return null;
	}

	/**
	 * Creates and returns the random poll
	 * that contains a Party object for each party name
	 * in the partyNames list.
	 * @param name name of the poll
	 * @return the random poll created by the method
	 * @throws InvalidSetupDataException 
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	public Poll createRandomPoll(String name) throws InvalidSetupDataException {
		/*
		The poll is given the name
		and is limited to the number of parties
		in the partyNames list
		 */
		Poll poll = new Poll(name, partyNames.length);
		float remainingVotes = 1;
		int remainingSeats = numOfSeats;
		// The order of parties is re-arranged
		Collections.shuffle(Arrays.asList(partyNames));
		int i = 0;
		// Going through the parties array and generating a new party with that name.
		for (i = 0; i < partyNames.length - 1; i++) {
			/*
			A new party is going to have a random number
			of seats and votes; therefore it's not a given
			that all parties would make it into the poll:
			some party might get randomly assigned nearly 100% votes
			 */
			if ((int)(remainingVotes * 100) > 0) {
				Party newParty = createRandomParty(partyNames[i], remainingSeats, (int) (remainingVotes * 100));
				remainingVotes -= newParty.getProjectedPercentageOfVotes();
				remainingSeats -= newParty.getProjectedNumberOfSeats();
				// The party is added to the poll
				poll.addParty(newParty);
			}
		}
		// The last party with a given name has been generated and is added to the poll
		try {
			poll.addParty(new Party(partyNames[i], remainingSeats, remainingVotes));
		} catch (InvalidPartyDataException e) {
			e.printStackTrace();
		}
		//The constructed Poll object can be returned
		return poll;
	}

	/**
	 * Create a random PollList
	 * @param numOfPolls number of polls
	 * @return the list of polls
	 * @throws InvalidSetupDataException  if new pollList cannot be initialized.
	 */
	public PollList createRandomPollList(int numOfPolls) throws InvalidSetupDataException {
		PollList list = null;
		list = new PollList(numOfPolls, numOfSeats);
		for (int counter = 0; counter < numOfPolls; counter++) {
			list.addPoll(createRandomPoll("Poll" + counter));
		}
		return list;
	}

	/**
	 * A prompt for the poll list
	 * @param numOfPolls number of polls
	 * @param partiesNames the party names in a list
	 * @return results of the poll list
	 * @throws InvalidSetupDataException is thrown if new pollList cannot be initialized.
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	public PollList promptForPollList(int numOfPolls, String[] partiesNames) throws InvalidSetupDataException {
		Scanner scanner = new Scanner(System.in);
		System.out.println(">>>> Creating new poll list: <<<<\n");
		PollList resultPollList = new PollList(numOfPolls, numOfSeats);
		for (int i = 0; i < numOfPolls; i++) {
			System.out.println(">>> Creating new poll: <<<\n");
			System.out.print("Poll name: ");
			String name = scanner.nextLine();
			Poll poll = new Poll(name, numOfSeats);
			for (String partyName: partiesNames)  {
				boolean validInput = false;
				while (!validInput) {
					System.out.println(">> Creating new party result: " + partyName + " <<");
					System.out.print("Party expected vote percentage: ");
					float votes = scanner.nextFloat();
					scanner.nextLine();
					System.out.print("Party expected number of seats: ");
					float seats = scanner.nextFloat();
					scanner.nextLine();
					try {
						poll.addParty(new Party(partyName, seats, votes));
					} catch (InvalidPartyDataException e) {
						e.printStackTrace();
					}
					if (seats >= 0 && votes >=0 && votes <= 1) {
						validInput = true;
					}
				}		
			}
			resultPollList.addPoll(poll);
		}
		return resultPollList;
	}

	private static boolean contains(String[] a, String o, boolean caseSensitive)  {
		for (String s: a)  {
			if (caseSensitive) {
				if (s.equals(o))  {
					return true;
				}
			}
			else{
				if (s.equalsIgnoreCase(o))  {
					return true;
				}
			}
		}
		return false;
	}

	private static String arrayToString(String[] a)  {
		String result = "";
		for (int i = 0; i < a.length; i++)  {
			result += a[i];
			if (i < a.length - 1)  {
				result += "/";
			}
		}
		return result;
	}

	/**
	 * Check for integer value
	 * @param scanner to scan the integer and validate it as a number
	 * @param message to print a message if the number is not valid
	 * @return user input when valid number has been inputted
	 */
	public static int validateInt(Scanner scanner, String message) {
		int count = 0;
		System.out.print(message);
		while (!scanner.hasNextInt()) {
			if (count >= 1) {
				System.out.println("Please provide a numeric answer!");
				scanner.nextLine();
			}
			System.out.print(message);
			count++;
		}
		int input = scanner.nextInt();
		scanner.nextLine();
		return input;
	}

	/**
	 * Validate user input 
	 * @param scanner
	 * @param validInput
	 * @param message
	 * @return user input
	 */
	public static String validateInput(Scanner scanner, String[] validInput, String message)  {
		String input;
		int count = 0;
		do {
			if (count >= 1)  {
				System.out.println("Please provide only a " + arrayToString(validInput) + " answer!");
			}
			System.out.print(message);
			input = scanner.nextLine();
			count++;
		}while (!contains(validInput, input, false));
		return input;
	}

	/**
	 * Setter
	 * @param names
	 */
	public void setPartyNames(String[] names) {
		if (names != null) {
			partyNames = Arrays.copyOf(names, names.length);
		}	
	}

	/**
	 * Getter
	 * @return partyNames
	 */
	public String[] getPartyNames() {
		return partyNames;
	}
}