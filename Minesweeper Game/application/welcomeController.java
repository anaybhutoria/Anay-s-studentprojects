package application;

import java.util.Iterator;
import java.util.Set;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import minesweeper.models.game.Difficulty;
import minesweeper.models.game.Minesweeper;
import minesweeper.models.player.Player;
import minesweeper.models.player.PlayerManager;
import java.util.ConcurrentModificationException;

/**
 * The welcome controller contains 
 * the instructions to the game 
 * and sets the difficulty
 * to the user's input.
 * This controller class extends the main controller.
 * 
 * @version 1.0
 * @author Izzah and Mika
 * 
 */
public class welcomeController extends MainController{
	private Minesweeper minesweeper = new Minesweeper();

    @FXML
    private TextArea instructions;
    
    @FXML
    private Label welcomeLabel;
    
    @FXML
    private Label instructionsLabel;
    
    @FXML
    private Label difficultyLabel;

    @FXML
    private TextArea difficulty;
    
    @FXML
    private BorderPane welcome_Borderpane;

	@FXML
	private ComboBox<String> setDifficulty;

    @FXML
    private Button setsDifficulty;

    @FXML
    private TextField PlayerName;
    
    /**
     * The button sets the difficulty according to the user's liking, and changes the size of the scene.
	 * Checks to see if the player name provided is already in set and gets player data.
	 * If no player exists it creates a new player with 0 points.
     */
    @FXML
    void set(ActionEvent event) {	
    	setShouldMake(true);
    	setStartGame(true);
    	setFirstTimer(true);
    	setReset(true);
    	if (setDifficulty.getValue() == null) {
    		welcome_Borderpane.setMaxWidth(600);
			welcome_Borderpane.setMaxHeight(600);
			setSize(600,900);
			minesweeper.setDifficulty(Difficulty.EASY);
    	} else {
    		String difficultySetting = setDifficulty.getValue(); //setting the window size depending on difficulty
    		if (difficultySetting.equalsIgnoreCase("easy")) {
    			welcome_Borderpane.setMaxWidth(600);
    			welcome_Borderpane.setMaxHeight(600);
    			setSize(600,900);
    			minesweeper.setDifficulty(Difficulty.EASY);
    		} else if (difficultySetting.equalsIgnoreCase("medium")) {
    			welcome_Borderpane.setMaxWidth(900);
    			welcome_Borderpane.setMaxHeight(900);
    			setSize(900,900);
    			minesweeper.setDifficulty(Difficulty.MEDIUM);
    		} else if (difficultySetting.equalsIgnoreCase("hard")) {
    			welcome_Borderpane.setMaxWidth(1200);
    			welcome_Borderpane.setMaxHeight(900);
    			setSize(1200,900);
    			minesweeper.setDifficulty(Difficulty.HARD);
    		}
    	}
		boolean playerFound = false;
		Set<Player> playerSet = getGameApp().getPlayerManager().getPlayers();
		String name = PlayerName.getText();
		if (name == null || name.equals("")) {
			name = "Player";
		}
		Player newPlayer;
		try {//grabbing player if player already exists
			for (Iterator<Player> iterator = playerSet.iterator(); iterator.hasNext();) {
				Player player = (Player) iterator.next();
				if (player.getName().equals(name)) {
					newPlayer = new Player(name, player.getPoints());
					playerSet.remove(player);
					playerSet.add(newPlayer);
					playerFound = true;
					setPlayer(newPlayer);
				}
			}	
		}
		catch (ConcurrentModificationException cme) {
			//Error is thrown but game is still fully functional 
		}
		if (!playerFound) {
			newPlayer = new Player(name, 0);
			playerSet.add(newPlayer);
			setPlayer(newPlayer);
		}
		PlayerManager playerManager = getGameApp().getPlayerManager();
		playerManager.setPlayers(playerSet);
		getGameApp().setPlayerManager(playerManager);
		saveGame();
		setMinesweeper(minesweeper);
		switchTab();
    }
 
	/**
	 * initializing combo box to contain difficulty.
	 */
	@Override
	public void refresh() {
		getSaveFile();
		String[] values = new String[] {"EASY", "MEDIUM", "HARD"};
		setDifficulty.setItems(FXCollections.observableArrayList(values));
	}
}
