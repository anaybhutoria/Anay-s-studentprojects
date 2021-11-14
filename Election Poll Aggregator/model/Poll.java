package model;

import java.util.Arrays;
import java.util.Comparator;

/**
 * A single poll
 * @version 1.0
 * @author Marina McPeak & Anay Bhutoria
 */
public class Poll {
	private String name = "Unnamed Poll";
	private Party[] parties;
	//The number of unique parties thathave been added to the poll to date
	private int numberOfParties = 0;

	/**
	 * Constructor
	 * @param name name of party
	 * @param maxNumberOfParties maximum number of parties
	 * @throws InvalidSetupDataException if maxNumberOfParties inputed is invalid
	 */
	public Poll(String name, int maxNumberOfParties) throws InvalidSetupDataException{
		this.name = name;
		if (maxNumberOfParties < 1) {
			throw new InvalidSetupDataException(); //throw a InvalidSetupDataException when the max number of parties is less than 1	
		}//chose to throw the exception so the application would not take a invalid number as an input
		parties = new Party[maxNumberOfParties];// and it would signal a throw instead
	}

	/**
	 * Add a new part
	 * @param aParty a single party
	 */
	public void addParty(Party aParty) {
		if (aParty == null) {
			System.out.println("Error: party can't be null!");
			return;
		}
		int index = getPartyIndex(aParty.getName());
		if (index == -1) {
			if (numberOfParties >= parties.length)  {
				System.out.println("Error: can't add new party, array full!");
				return;
			}
			parties[numberOfParties++] = aParty;
		}
		else{
			parties[index] = aParty;
		}
	}

	private int getPartyIndex(String name)  {
		for (int i = 0; i < numberOfParties; i++)  {
			if (parties[i].getName().equalsIgnoreCase(name))  {
				return i;
			}
		}
		return -1;
	}

	/**
	 * Get party name
	 * @param name party name
	 * @return null
	 */
	public Party getParty(String name) {
		int index = getPartyIndex(name);
		if (index >= 0)  {
			return parties[index];
		}
		return null;
	}

	/**
	 * Get parties and sort parties by the number of seats
	 * @return Array
	 */
	public Party[] getPartiesSortedBySeats() {
		Arrays.sort(parties, new Comparator<Party>() {
			@Override
			public int compare(Party party1, Party party2)  {
				if (party1 == null && party2 != null)  {
					return 1;
				}
				else if (party1 != null && party2 == null)  {
					return -1;
				}
				else if (party1 == null && party2 == null)  {
					return 0;
				}
				return Float.compare(party2.getProjectedNumberOfSeats(),
										party1.getProjectedNumberOfSeats());
			}
		});
		return Arrays.copyOfRange(parties, 0, numberOfParties);
	}

	/**
	 * Get parties and sort parties by the number of votes
	 * @return Array
	 */
	public Party[] getPartiesSortedByVotes() {
		Arrays.sort(parties, new Comparator<Party>() {
			@Override
			public int compare(Party party1, Party party2)  {
				return Float.compare(party2.getProjectedPercentageOfVotes(),
										party1.getProjectedPercentageOfVotes());
			}
		});
		return Arrays.copyOfRange(parties, 0, numberOfParties);
	}

	@Override
	/**
	 * @return the poll information
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder(name);
		sb.append("\n");
		for (int i = 0; i < numberOfParties; i++)  {
			sb.append(parties[i].toString() + "\n");
		}
		return sb.toString();
	}

	/**
	 * Get undetermined votes
	* @return the amount of undetermined seats from the poll
	*/

	public float getUndeterminedVotes()  {
		float totalVotes = 0;
		float takenVotes = 0;
		return totalVotes - takenVotes;
	}

	/**
	 * Getter
	 * @return name
	 */
	public String getPollName() {
		return name;
	}
	
	/**
	 * Setter
	 * @return number of parties
	 */
	public int getNumberOfParties() {
		return numberOfParties;
	}
}
