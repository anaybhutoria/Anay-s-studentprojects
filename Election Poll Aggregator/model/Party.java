package model;

/**
 * Class that represents a single political party
 * @author Mikaela Ong
 * @version 1.0
 */
public class Party {
	private String name;
	private float projectedNumberOfSeats;
	private float projectedPercentageOfVotes;
	
	/**
	 * Default constructor that sets the party name
	 * @param partyName
	 */
	public Party(String partyName) {
		name = partyName;
	}
	
	/**
	 * Constructor that sets the party name, projected number of seats and projected percentage of votes.
	 * @param partyName
	 * @param theProjectedNumberOfSeats
	 * @param theProjectedPercentageOfVotes
	 * @throws InvalidPartyDataException  Exception that is thrown if the inputed data is invalid.
	 */
	public Party(String partyName, float theProjectedNumberOfSeats, float theProjectedPercentageOfVotes) throws InvalidPartyDataException {
		name = partyName;
		if (theProjectedNumberOfSeats >= 0) {
			projectedNumberOfSeats = theProjectedNumberOfSeats;
		} else {
			throw new InvalidPartyDataException();
		}
		if (theProjectedPercentageOfVotes <= 1 && theProjectedPercentageOfVotes >= 0) {
			projectedPercentageOfVotes = theProjectedPercentageOfVotes;
		} else {
			throw new InvalidPartyDataException();
		}
	}
	
	/**
	 * @return the party name
	 */
	public String getName() {
		return name;
	}
	
	/**
	 * Set the party name.
	 * @param partyName.
	 */
	public void setName(String partyName) {
		name = partyName;
	}
	
	/**
	 * @return the projected number of seats.
	 */
	public float getProjectedNumberOfSeats() {
		return projectedNumberOfSeats;
	}
	
	/**
	 * Sets the projected number of seats as a positive number. 
	 * If the method is given a negative number the projected number of seats is set to 0.
	 * @param theProjectedNumberOfSeats.
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	 public void setProjectedNumberOfSeats(float theProjectedNumberOfSeats) throws InvalidPartyDataException {
		if (theProjectedNumberOfSeats >= 0) {
			projectedNumberOfSeats = theProjectedNumberOfSeats;
		} else {
			throw new InvalidPartyDataException();
		}
	}
	
	/**
	 * @return the projected percentage of votes.
	 */
	public float getProjectedPercentageOfVotes() {
		return projectedPercentageOfVotes;
	}
	
	/**
	 * Sets the projected percentage of votes as a decimal between 0 and 1.
	 * @param theProjectedPercentageOfVotes
	 * @throws InvalidPartyDataException Exception that is thrown if the inputed data is invalid.
	 */
	public void setProjectedPercentageOfVotes(float theProjectedPercentageOfVotes) throws InvalidPartyDataException {
		if (theProjectedPercentageOfVotes <= 1 && theProjectedPercentageOfVotes >= 0) {
			projectedPercentageOfVotes = theProjectedPercentageOfVotes;
		} else {
			throw new InvalidPartyDataException();
		}
	}
	
	/**
	 * @return the party information
	 */
	@Override 
	public String toString() {
		int percentOfVotesAsWholeNumber = (int) (projectedPercentageOfVotes*100);
		return name + " (" + percentOfVotesAsWholeNumber + "% of votes, " + projectedNumberOfSeats + " seats)";
	}
	
	/**
	 * This method finds the projected percentage of seats the party will win.
	 * @param totalNumberOfSeats
	 * @return the projected percentage of seats the party will win.
	 */
	public double projectedPercentOfSeats(int totalNumberOfSeats) {
		if (totalNumberOfSeats > 0) {
			return projectedNumberOfSeats/totalNumberOfSeats;
		} else {
			return 0;
		}
	}
	
	/**
	 * Shows a visualization of the projected number of seats won by the party and if they reached majority.
	 * Calculates the amount of stars the party won then runs the commonCodeForVisualization.
	 * @param maxStars the maximum amount of stars the party can win.
	 * @param starsNeededForMajority the amount of stars needed to win a majority.
	 * @param numOfSeatsPerStar the number of seats that equate to one star.
	 * @return visualization of party results
	 */
	public String textVisualizationBySeats(int maxStars, int starsNeededForMajority, double numOfSeatsPerStar) {
		int numOfStars = (int) (projectedNumberOfSeats / numOfSeatsPerStar); 
		return commonCodeForVisualization(numOfStars, maxStars, starsNeededForMajority);
	}
	
	/**
	 * Shows a visualization of the projected percentage of votes won by the party and if they reached majority.
	 * Calculates the amount of stars the party won then runs the commonCodeForVisualization.
	 * @param maxStars the maximum amount of stars the party can win.
	 * @param starsNeededForMajority the amount of stars needed to win a majority.
	 * @param percentOfVotesPerStar the percentage of votes that equate to one star.
	 * @return visualization of party results
	 */
	public String textVisualizationByVotes(int maxStars, int starsNeededForMajority, double percentOfVotesPerStar) {
		int numOfStars = (int) ((projectedPercentageOfVotes*100) / percentOfVotesPerStar);
		return commonCodeForVisualization(numOfStars, maxStars, starsNeededForMajority);
	}
	
	/**
	 * The common code used for the visualizations. 
	 * Creates the visualization.
	 * @param numOfStars the amount of stars the party won.
	 * @param maxStars the maximum amount of stars the party can win.
	 * @param starsNeededForMajority the amount of stars needed to win a majority.
	 * @return visualization of party results
	 */
	public String commonCodeForVisualization(int numOfStars, int maxStars, int starsNeededForMajority) {
		String visuals = "";
		int star = 1;
		while (star <= numOfStars) {
			visuals = visuals + "*";
			if (star == starsNeededForMajority) {
				visuals = visuals + "|";
			}
			star++;
		}
		if (numOfStars < maxStars ) {
			for (int index = star; index <= maxStars; index++) {
				visuals = visuals +" ";
				if (index == starsNeededForMajority) {
					visuals = visuals + "|";
				}
			}
		}
		return visuals + " " + this.toString();
	}
}
