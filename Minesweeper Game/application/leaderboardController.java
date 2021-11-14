package application;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import minesweeper.models.player.*;

/**
 * This class is the controller for leaderboardView.fxml and is used to 
 * initialize the leaderboard and print the scores for the leaderboard.
 * @author Izzah and Mika
 * @version 1.0
 */
public class leaderboardController extends MainController{

    @FXML
    private TableView<Player> leaderboardTable;

    @FXML
    private TableColumn<Player, String> nameCol;

    @FXML
    private TableColumn<Player, Integer> pointCol;
   /**
    * The refresh method is used to print out the scores for the players 
    * and sorts the scores in ascending order.
    */
    @Override
	public void refresh() {
    	leaderboardTable.getItems().clear();
		saveGame();
		nameCol.setCellValueFactory(new PropertyValueFactory<>("name"));
		pointCol.setCellValueFactory(new PropertyValueFactory<>("points"));
		Set<Player> playerSet = getGameApp().getPlayerManager().getPlayers();
		List<Player> players = new ArrayList<Player>();
		for (Player player : playerSet) {
			players.add(player);
		}
		Collections.sort(players, Collections.reverseOrder());
		for (Player player : players) {
			leaderboardTable.getItems().add(player);
		}
	}
}
