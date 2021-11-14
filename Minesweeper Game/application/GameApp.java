package application;

import minesweeper.models.game.Minesweeper;
import minesweeper.models.player.PlayerManager;

import java.io.FileInputStream;
import java.io.IOException;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;

/**
 * The game application that is used to run the minesweeper GUI.
 * @author Mika Ong & Anay Bhutoria
 * @version 1.0
 */
public class GameApp extends Application {
	private Stage primaryStage;
	private boolean startGame = false;
	private Minesweeper minesweeper = new Minesweeper();
	TabPane root ;
	private PlayerManager playerManager = minesweeper.getPlayerManager() ;
	
	/**
	 * gets the minesweeper instance being used
	 * @return minesweeper instance being used
	 */
	public Minesweeper getMinesweeper() {
		return minesweeper;
	}
	
	/**
	 * Checks if the game tab is selected and start the game if it is.
	 * @return startGame
	 */
	public boolean getStartGame() {
		return startGame;
	}
	
	/**
	 * Sets the start game variable
	 * @param newbool new value for startGame.
	 */
	public void setStartGame(boolean newbool) {
		startGame = newbool;
	}
	
	/**
	 * set the minesweeper instace being used
	 * @param minesweeperGame new minesweeper instance that will be used
	 */
	public void setMinesweeper(Minesweeper minesweeperGame) {
		minesweeper = minesweeperGame;
	}
	
	/**
	 * Creates a tab for the scene
	 * @param tabName the name of the tab.
	 * @param FXMLFilename the name of the FXML file that will be portrayed
	 * @return the new tab.
	 */
	private Tab createTab(String tabName, String FXMLFilename) {
		Tab aTab = null;
		try {
			FXMLLoader loader = new FXMLLoader();
			aTab = new Tab(tabName, loader.load(new FileInputStream(FXMLFilename)));
			MainController controller = (MainController)loader.getController();
			aTab.setOnSelectionChanged (e -> controller.refresh());
			controller.setGameApp(this);
		} catch (IOException e1) {
			System.out.println("Problem loading FXML file " + FXMLFilename);
		}
		return aTab;
	}
	
	/**
	 * Makes the scene and stage to be presented
	 */
	@Override
	public void start(Stage mystage) throws Exception {
		setPrimaryStage(mystage);
		getPrimaryStage().setTitle("Minesweeper");
		root = new TabPane (
			createTab("Welcome", "src/view/welcomeView.fxml"),
			createTab("Game", "src/view/gameView.fxml"),
			createTab("LeaderBoard","src/view/leaderboardView.fxml")
			);
		root.getSelectionModel().selectedIndexProperty().addListener((obs,ov,nv)->{
			if(nv.intValue() == 1) {
				startGame = true;
			}
		});
		Scene scene = new Scene(root,900,900);
		getPrimaryStage().setScene(scene);
		getPrimaryStage().setResizable(true);
		getPrimaryStage().show();
	}
	
	public static void main(String[] args) {
		launch(args);
	}

	/**
	 * Gets the stage being used in the application.
	 * @return the stage in the app
	 */
	public Stage getPrimaryStage() {
		return primaryStage;
	}

	/**
	 * Sets the stage used in the application
	 * @param primaryStage new stage for the application.
	 */
	public void setPrimaryStage(Stage primaryStage) {
		this.primaryStage = primaryStage;
	}
	
	/**
	 * gets the playerManager of the application
	 * @return playerManager of application
	 */
	public PlayerManager getPlayerManager() {
		return playerManager;
	}

	/**
	 * Sets the playerManager
	 * @param playerManager new playerManager for app
	 */
	public void setPlayerManager(PlayerManager playerManager) {
		this.playerManager = playerManager;
	}
}

