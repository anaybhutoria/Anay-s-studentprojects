package application;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import minesweeper.models.game.Minesweeper;
import minesweeper.models.player.Player;

/**
 * Abstract controller class that is extended by the welcome and game controllers
 * @author Mika Ong & Anay Bhutoria
 * @version 1.0
 */
public abstract class MainController {
	private GameApp app;
	private boolean firstTimer = true;
	private boolean addPlayers = true;
	private boolean shouldMake = true;
	private static boolean reset = false;
	private static Player currentPlayer = new Player("Player", 0);
	
	/**
	 * abstract method that is used in child classes
	 */
	public abstract void refresh();
	
	/**
	 * Sets the game app being used
	 * @param app the app being used
	 */
	public void setGameApp(GameApp app) {
		this.app = app;
		refresh();
	}
	
	/**
	 * Gets the game app 
	 * @return current game app
	 */
	public GameApp getGameApp() {
		return app;
	}
	
	
	/**
	 * Gets the mineweeper game being used in the app
	 * @return the minesweeper instance that is being used in the app
	 */
	protected Minesweeper getMinesweeper() {
		return getGameApp().getMinesweeper();
	}
	
	/**
	 * Set the minesweeper game that is used in the app 
	 * @param minesweeperGame game instance that will be used throughout the app
	 */
	protected void setMinesweeper(Minesweeper minesweeperGame) {
		getGameApp().setMinesweeper(minesweeperGame);
	}
	
	/**
	 * Sets the size for the window according to the difficulty
	 * @param width, width of the window
	 * @param height, height of the window
	 */
	protected void setSize(int width, int height) {
		getGameApp().getPrimaryStage().setHeight(height);
		getGameApp().getPrimaryStage().setWidth(width);
	}
	
	/**
	 * Switches from the welcome to the game tab.
	 */
	protected void switchTab() {
		setFirstTimer(true);
		setShouldMake(true);
		getGameApp().root.getSelectionModel().selectNext();
	}
	
	/**
	 * Checks if the game should be started.
	 * @return is game should be started.
	 */
	protected boolean getStartGame() {
		return getGameApp().getStartGame();
	}
	
	/**
	 * set the start game variable
	 * @param start start game value
	 */
	protected void setStartGame(boolean newbool) {
		getGameApp().setStartGame(newbool);
	}
	
	/**
	 * gets firstTimer.
	 * @return if a timer is running
	 */
	protected boolean getFirstTimer() {
		return firstTimer;
	}
	
	/**
	 * set firstTimer.
	 * @param if there is only one timer running
	 */
	protected void setFirstTimer(boolean timer) {
		firstTimer = timer;
	}

	/**
	 * gets the player list
	 * @return the player list
	 */
	public Set<Player> getPlayers() {
		return getGameApp().getPlayerManager().getPlayers() ;
	}

	/**
	 * Gets the leaderboard save file and add the players to a set
	 * If no file exists an error message is shown.
	 */
	public void getSaveFile() {
		File retrievePlayers = new File("players.bin");
		Set<Player> playerSet = getGameApp().getPlayerManager().getPlayers();
		if (retrievePlayers.isFile() && addPlayers) {				
				try {
					DataInputStream in = new DataInputStream( new FileInputStream("players.bin"));
					int playerSize = in.readInt();
					for (int i = 0; i < playerSize; i++) { //adding all the players from the file to the heap
						String	tempName = in.readUTF();
						int	tempPoints = in.readInt();
						Player tempPlayer = new Player(tempName, tempPoints);
						playerSet.add(tempPlayer);
					}
					in.close();
					addPlayers = false;	
				} catch(Exception e) {		
				}	
		} else if ( (!retrievePlayers.isFile()) && addPlayers) {
			addPlayers = false;
			System.out.println("Could not find save file making a new save file "+
			"\n, if save file already exists please make sure it is placed in: \n" + 
			System.getProperty("user.dir"));
		}
	}
	
	/**
	 * Sets the current player of the game
	 * @param the current player
	 */
	public void setPlayer(Player player) {
		currentPlayer = new Player(player.getName(), player.getPoints());
	}
	
	/**
	 * Gets the current player 
	 * @return the current player
	 */
	public Player getPlayer() {
		return currentPlayer;
	}

	/**
	 * Saves the player data onto the existing file 
	 * If no file exists one is created.
	 */
	public void saveGame() {
    	Set<Player> playerSet = getGameApp().getPlayerManager().getPlayers();
    	try {
    	FileOutputStream myFile = new FileOutputStream("Players.bin", false);
    	DataOutputStream out = new DataOutputStream(myFile);
    	out.writeInt(playerSet.size());
    		for (Player current : playerSet) {
    			out.writeUTF(current.getName());
    			out.writeInt(current.getPoints());
    		}
    		out.close();
    	} catch(Exception e) {
    	System.out.println("Unable to save data");
    	}
    }
	
	/**
	 * Checks if new board should be made
	 * @return if new board should be made
	 */
	public boolean getShouldMake() {
		return shouldMake;
	}
	
	/**
	 * Sets shouldMake
	 * @param make if a new board should be made
	 */
	protected void setShouldMake(boolean make) {
		shouldMake = make;
	}
	
	/**
	 * Sets reset variable
	 * @param If the game should be reset
	 */
	protected void setReset(boolean shouldReset) {
		reset = shouldReset;
	}
	
	/**
	 * Gets reset variable
	 * @return if game should be reset
	 */
	protected boolean getReset() {
		return reset;
	}
}