package application;

import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import minesweeper.models.board.Board;
import minesweeper.models.board.BoardSquare;
import minesweeper.models.game.Minesweeper;
import minesweeper.models.game.Move;
import minesweeper.models.player.Player;
import minesweeper.models.player.PlayerManager;
import java.util.ConcurrentModificationException;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;

import javafx.application.Platform;

/**
 * This class is the controller for GameView.fxml and is used to initialize the minesweepergame 
 * and start it once the player is ready
 * @author Mika, Anay and Izzah
 * @version 1.0
 */
public class GameController extends MainController {
	private boolean loseGame = false;
	private boolean winGame = false;
	private int minesNumber;
	private int rows;
    private int columns;
	private Minesweeper minesweeper;
	private Board board;
	int flagCounter = 0;
	private int correctFlag = 0;
	private Thread timerThread;
	
	@FXML
	private HBox resetArea;
	
	@FXML
    private Label flag;
	
	@FXML
	private HBox display;

    @FXML
    private VBox main;
	   
	@FXML
    private Label label_Timer;
	
	@FXML
    void initialize() {
	
	}

	/**
	 * Generates the game instance.
	 */
	public void generate() {
		loseGame = false;
		winGame = false;
		addResetButton();
		setup();
		setLabel();
		makeBoard();
		if (getFirstTimer()) {
			makeTimer();
		}
	}
	
	/**
	 * Makes the timer
	 */
	public void makeTimer() {
		//creating a local thread to start the timer and run it once game is started.
		timerThread = new Thread(() -> {
	    	long currentTime = new Date().getTime(); 
	    		while (getStartGame()) {
		            try {
		                Thread.sleep(1000); //1 second
		            } catch (InterruptedException e) {
		                e.printStackTrace();
		            }
		            final String time = String.valueOf(((new Date().getTime())-currentTime)/1000);
		            Platform.runLater(() -> {
		                label_Timer.setText("Time taken: " + time + " seconds");
		            });
		        }
	    });   
		timerThread.start(); 	
		setFirstTimer(false);
	}
   
    /**
     * Adds a reset button that clears the board and starts the generate function.
     */
	public void addResetButton() {
    	resetArea.getChildren().clear();
    	Button reset = new Button("Reset Game/Timer");
		reset.setOnMouseClicked(event -> {
			reset();
			refresh();
		});
		resetArea.getChildren().add(reset);
		correctFlag = 0;
    	flagCounter = 0;
    	if (winGame||loseGame) {
    		reset.setText("Play Again?");
    	}
    }
	
	/**
	 * This method resets the game.
	 */
	public void reset() {
		timerThread.stop();
		main.getChildren().clear();
    	board.clear();
    	setShouldMake(true);
    	setStartGame(true);
    	setFirstTimer(true);
    	setReset(false);
    	refresh();
	}
    
    
    /**
     * Sets the label for the number of mines remaining.
     */
    public void setLabel() {
    	if (!winGame) {
    		flag.setText("Number of mines remaining: " + (minesNumber - flagCounter));
    	}
    }
    
    /**
     * This method gets the ID and sets the button text to how many mines are surrounding it when clicked
     * to essentially make a move in the Minesweeper game,
     * @param clickedButton
     */
    public void getID(Button clickedButton) {
    	if (clickedButton.getTextFill() != Color.GREEN) {
    		String buttonID = clickedButton.getId();// turn the ID of the button into integers
    		String split[] = buttonID.split(",", 2);
    		String rowStr = split[0];
    		String columnStr = split[1];
    		int rowInt = Integer.valueOf(rowStr); 
    		int columnInt = Integer.valueOf(columnStr);    	
    		Move buttonMove = new Move(rowInt,columnInt);
    		BoardSquare square = getBoard().makeMove(buttonMove);
    		if (square.isMine()) {
    			clickedButton.setFont(Font.font("Verdana", FontWeight.BOLD, 12)); // change the color of the mine depending on
    			clickedButton.setText("\uD83D\uDCA3");							 //what the button contains
    			loseGame = true;
    		} else if (square.getNeighbourMinesNumber() != 0){ 
				clickedButton.setFont(Font.font("Verdana", FontWeight.BOLD, 14));
    			clickedButton.setText(String.valueOf(square.getNeighbourMinesNumber()));
				if (square.getNeighbourMinesNumber() == 1){
					clickedButton.setTextFill(Color.BLUE);		
				} else if (square.getNeighbourMinesNumber() == 2){
    				clickedButton.setTextFill(Color.DARKGREEN);	
				} else if (square.getNeighbourMinesNumber() == 3){
					clickedButton.setTextFill(Color.DARKMAGENTA);
				} else if (square.getNeighbourMinesNumber() == 4){
					clickedButton.setTextFill(Color.DARKBLUE);
				}
    		} else {
    			clickedButton.setText("  ");
    		}
    	}
    }
    	
    /**
     * Function that runs once the tab is opened.
     * Gets the needed information from the welcome tab. 
     */
    @Override
	public void refresh() {
    	minesweeper = getMinesweeper();
    	rows = minesweeper.getDifficulty().getRows();
    	columns = minesweeper.getDifficulty().getColumns();
    	if (getReset()) {
    		reset();
    	}
    	if (getShouldMake()) {
    		generate();
    	}
	}
    
    /**
     * Makes the visuals for the board.
     */
    public void makeBoard() {
    	if (timerThread!=null) {
    		timerThread.stop();
    		makeTimer();
    	}
    	main.getChildren().clear();
    	for (int row = 0; row < rows; row++) { //makes rows of buttons
			HBox rowContainer = new HBox();
			rowContainer.setSpacing(3);
			main.setSpacing(3);
			for (int column = 0; column < columns; column++) { //makes columns of buttons
				Button space = new Button("?");
				space.setPrefSize(35,35);
				space.setTextFill(Color.BLACK);
				space.setId(row +"," + column);
				space.setOnAction(e -> getID(space));
				space.setOnMouseClicked(event ->
				{
					//Sets action if button is left clicked.
					if (event.getButton() == MouseButton.PRIMARY) {
						setShouldMake(false);
						if(space.getTextFill() == Color.GREEN) {
							return;
						}
						space.setDisable(true);
						// If the conditions are met calls the win/lose method
						if (board.getFreeSquares() == minesNumber ) {
							winGame();	
			    		}
						if (loseGame == true) {
							gameLost();
						}
					//Sets action if button is right clicked.
					} else if (event.getButton() == MouseButton.SECONDARY) {
						if(space.getTextFill() == Color.GREEN) {							
							space.setTextFill(Color.BLACK);
							space.setText("?");
							flagCounter--;
							mineCheck(space);
						} else {
							space.setTextFill(Color.GREEN);
							space.setText("F");
							flagCounter ++; 
							mineCheck(space);
						}
						setLabel(); 
					}
				}				 
				);
				rowContainer.getChildren().add(space);
			}
			main.getChildren().add(rowContainer);
			rowContainer.setAlignment(Pos.CENTER);
		}
    }
    
    /**
     * Sets up the minesweper board instance that the visuals pull from.
     */
    private void setup() {
        board = new Board(rows, columns);
        minesNumber = minesweeper.getDifficulty().getMinesNumber();
        board.generate(minesNumber);
        setBoard(board);
    }
    
    /**
     * Function that runs when the game is lost.
     * Opens the entire board and prompts to play again instead of reset 
	 * also calls the game end method.
     */
    private void gameLost() {
    	board.openAll();
    	main.getChildren().clear();
    	for (int row = 0; row < rows; row++) {
			HBox rowContainer = new HBox();
			rowContainer.setSpacing(3);
			main.setSpacing(3);		
			for (int column = 0; column < columns; column++) {
				Button space = new Button();
				space.setPrefSize(30,30);
				space.setId(row +"," + column);
				space.setTextFill(Color.BLACK);
				space.setFont(Font.font("Verdana", FontWeight.BOLD, 14));
				space.setDisable(true);
				getID(space);
				rowContainer.getChildren().add(space);
			}
			main.getChildren().add(rowContainer);
			rowContainer.setAlignment(Pos.CENTER);
		}
    	flag.setText("You Lost :(");
    	resetArea.getChildren().clear();
    	addResetButton();
		setStartGame(false);
		gameEnd();	
    }
    
    /**
     * Function that runs when the game is won.
     * Prompts the player to play again instead of reset.
	 * Also calls the game end method.
     */
    private void winGame() {
    	flag.setText("You WON !!!!!");
    	board.openAll();
    	winGame = true; 
    	resetArea.getChildren().clear();
    	addResetButton();
		setStartGame(false);
		gameEnd();
    }

    /**
     * Function to get the board being played.
     * @return returns the board currently being played.
     */
    private Board getBoard() {
    	return this.board;
    }
    
    /**
     * Sets the board that is being played.
     * @param newBoard the new board that will be played.
     */
    private void setBoard(Board newBoard) {
	    board = newBoard;
    }
    
    /**
     * Checks if the flag that is placed or removed was actually a mine.
     * If the player is correct the number of correct flags is added to a counter
     * If the player flags all the mines correctly the player wins.
     * @param clickedButton the Button that is clicked.
     */
    private void mineCheck(Button clickedButton ) {
	    String buttonID = clickedButton.getId();
		String split[] = buttonID.split(",", 2);
		String rowStr = split[0];
		String columnStr = split[1];
		int rowInt = Integer.valueOf(rowStr);
		int columnInt = Integer.valueOf(columnStr);
		Move buttonMove = new Move(rowInt,columnInt);
		BoardSquare square = getBoard().makeMove(buttonMove);
		if (square.isMine()) {
			if (clickedButton.getTextFill()==Color.GREEN) {
				correctFlag++;
			} else {
				correctFlag--;
			}
		}
		if (correctFlag == minesNumber && flagCounter == minesNumber) {
			winGame();
		}
    }
    
    /**
     * The game end method checks to see if the player already exists 
     * in the file if they do then it uses the same name, 
     * if not it then adds the new player to the file. 
     * It also increments and decrements the points depending if the 
     * the player has won or lost the game.
     * It then saves the players name and new points to the file.
     */
    public void gameEnd() {
    	int points = minesweeper.getDifficulty().getPoints();
		Player player = getPlayer();
		if (winGame == true) {
    		player.incrementPoints(points);
    	}
    	if(loseGame == true) {
    		player.decrementPoints(points);
    	}
		try {
			Set<Player> playerSet = getGameApp().getPlayerManager().getPlayers();
    		for (Iterator<Player> iterator = playerSet.iterator(); iterator.hasNext();) {
				Player current = (Player) iterator.next();
    			if (current.getName().equals(player.getName())) {
    				playerSet.remove(current);
    				playerSet.add(player);
    			}
    		}
    		PlayerManager playerManager = getGameApp().getPlayerManager();
			playerManager.setPlayers(playerSet);
			getGameApp().setPlayerManager(playerManager);
		}
		catch (ConcurrentModificationException cme) {
			//Error is thrown but game is still fully functional. 
		}
    	saveGame();
    } 
   
}