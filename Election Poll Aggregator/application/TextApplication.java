package application;

import java.util.Scanner;

import model.InvalidSetupDataException;
import model.Factory;
import model.Party;
import model.Poll;
import model.PollList;

/**
 * Runs the entire application and gathers user input
 * @version 1.0
 * @author Marina Mcpeak and Izzah Nazir Ahmad 
 */
public class TextApplication {
	public static final int MAX_NUMBER_OF_STARS = 25;
	private PollList polls;
	private int seatsNumber;
	private float SEATS_PER_STAR;
	private float REAL_MAX_SEATS;
	private int STARS_FOR_MAJORITY;
	private boolean isInitialized;

	/**
	 * Constructor
	 * @throws InvalidSetupDataException 
	 */
	public TextApplication() throws InvalidSetupDataException {
		polls = new PollList(2, 2);
	}
	
	/**
	 * Constructor
	 * @param polls
	 */
	public TextApplication(PollList polls) {
		this.polls = polls;
	}

	/**
	 * This method visualizes the date in the poll provided as an argument to allow the user to compare the parties
	 * @param aPoll the poll with data
	 */
	public void displayPollDataBySeat(Poll aPoll) {
		System.out.println(aPoll.getPollName());
		Party[] parties = aPoll.getPartiesSortedBySeats();
		for (Party party: parties)  {
			System.out.println(party.textVisualizationBySeats(MAX_NUMBER_OF_STARS,
					STARS_FOR_MAJORITY, SEATS_PER_STAR));
		}
	}

	private float findMaxSeat(Party[] parties) {
		float result = 0;
		for (Party party: parties) {
			if (party.getProjectedNumberOfSeats() > result) {
				result = party.getProjectedNumberOfSeats();
			}
		}
		return result;
	}

	private void initializeSeatsConstants(PollList pollList) throws InvalidSetupDataException {
		REAL_MAX_SEATS = 0;
		for (Poll poll: pollList.getPolls()) {
			float maxPartySeats = findMaxSeat(poll.getPartiesSortedBySeats());
			if (maxPartySeats > REAL_MAX_SEATS) {
				REAL_MAX_SEATS = maxPartySeats;
			}
		}
		SEATS_PER_STAR = REAL_MAX_SEATS / MAX_NUMBER_OF_STARS;
		if (REAL_MAX_SEATS / SEATS_PER_STAR > 3) {
			SEATS_PER_STAR *= 2;
		}
		STARS_FOR_MAJORITY = 1 + (int) ((seatsNumber) / SEATS_PER_STAR) / 2;
		isInitialized = true;
	}
	
	/**
	 * Display the polls by seat
	 * @param partyNames
	 * @throws InvalidSetupDataException 
	 */
	public void displayPollsBySeat(String[] partyNames) throws InvalidSetupDataException {
 		for (String partyName: partyNames) {
 			Poll poll = polls.getAggregatePoll(partyNames);
 			displayPollDataBySeat(poll);
		}
	}
	
    /**
     * This method makes sure that the application catches the invalid data exception. 
     * @return input 
     */
	  public int getNumber(){ 
        Scanner sc = new Scanner(System.in);
        while (true) {
            String input = sc.next();
            try {
				 return Integer.parseInt(input);
            }catch (NumberFormatException ne) {
                System.out.println("**Invalid number, please try Again");
            }
        }
    }
	  
	/**
	 * Runs application and gathers user input. 
	 * If user input is invalid it prompts the user to input again.
	 * Also catches InvalidSetupDataException.
	 */
	public void run() throws InvalidSetupDataException {
		try {
		Scanner scanner = new Scanner(System.in);
		boolean redo;
		do {
			redo = false;
			isInitialized = false;
			System.out.println("Welcome to the poll tracker");
			System.out.println("How many seats are available in the election? ");
			seatsNumber = getNumber(); //checks to see if if invalid number is entered 
				while(seatsNumber <=0){
					System.out.println("**Invalid number was inputed, please input a valid number ");
					seatsNumber = getNumber();
				}
			System.out.print("Which parties are in the election (provide names, comma separated): ");
			String[] partiesNames = scanner.nextLine().split(",");
			while (partiesNames.length == 0 || partiesNames[0].equals("")) {  //checks to see if if invalid number is entered 
				System.out.println("Number of parties is 0. Please try again.");
				 partiesNames = scanner.nextLine().split(",");
			}
			System.out.println(	"How many polls do you want to track with this application? ");
			int pollsNumber = getNumber();
			while(pollsNumber <=0){ //checks to see if if invalid number is entered 
				System.out.println("**Invalid number was inputed, please input a valid number");
				pollsNumber = getNumber();
			}
			boolean createRandom = Factory.validateInput(scanner, new String[]{"yes", "no"},
					"Would you like me to create a random set of polls? (yes/no): ")
					.equalsIgnoreCase("yes");
					Factory factory = new Factory(seatsNumber);
				System.out.println("Invalid entry");	
			factory.setPartyNames(partiesNames);
			if (createRandom) {
				polls = factory.createRandomPollList(pollsNumber);
			} else {
				polls = factory.promptForPollList(pollsNumber, partiesNames);
			}
			// Gets user input to decide what data to present
			boolean shouldQuit = false;
			while (!shouldQuit) {
				System.out.println("Options: all (show result of all polls), aggregate (show aggregate result), " +
						"quit (end application) or redo (start tracker again)");
				String option = Factory.validateInput(scanner,
						new String[]{"quit", "aggregate", "all", "redo"}, "Choose an option: ");
				System.out.println(option);
				switch (option) {
					case "quit": {
						shouldQuit = true;
						break;
					}
					case "aggregate": {
						Poll aggregate = polls.getAggregatePoll(partiesNames);
						if (!isInitialized) {
							initializeSeatsConstants(polls);
						}
						displayPollDataBySeat(aggregate);
						break;
					}
					case "all": {
						if (!isInitialized) {
							initializeSeatsConstants(polls);
						}
						for (Poll poll : polls.getPolls()) {
							displayPollDataBySeat(poll);
						}
						break;
					}
					case "redo": {
						redo = true;
						shouldQuit = true;
						break;
					}
				}
			}
		}while (redo);
		}catch (InvalidSetupDataException isde) {
			System.out.println("Invalid integer, try again!");
			throw isde;
		}
	}

	/**
	 * This method creates an instance of TextApplication and calls the method run to get the entire application running
	 * @param args no command-line arguments expected
	 * @throws InvalidSetupDataException 
	 */
	public static void main(String[] args) throws InvalidSetupDataException {
		// Default constructor is used
		TextApplication app = new TextApplication();
		app.run();
 	}

}
