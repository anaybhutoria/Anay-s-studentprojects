package application;
	
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;

import model.Factory;
import model.PollList;

import javafx.scene.Scene;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TextArea;


public class PollTrackerApp extends Application {
	public static final int DEFAULT_NUMBER_OF_SEATS = 345;
	public static final String FXML_FILES_LOCATION = "src/view/";
	public static final int DEFAULT_NUMBER_OF_POLLS = 5;
	private PollList polls;
	private Factory factory = new Factory(DEFAULT_NUMBER_OF_SEATS);
	
	public PollList getPolls() {
		return polls;
	}
	
	public void setPolls(PollList aList) {
		polls = aList;
	}
	
	public Factory getFactory() {
		return factory;
	}
	
	public void setFactory(Factory aFactory) {
		factory = aFactory;
	}
	
	private Tab createTab(String tabName, String FXMLFilename) {
		Tab aTab = null;
		try {
			FXMLLoader loader = new FXMLLoader();
			aTab = new Tab(tabName, loader.load(new FileInputStream(FXMLFilename)));
			PollTrackerController controller = (PollTrackerController)loader.getController();
			aTab.setOnSelectionChanged (e -> controller.refresh());
			controller.setPollTrackerApp(this);
		} catch (IOException e1) {
			System.out.println("Problem loading FXML file " + FXMLFilename);
		}
		return aTab;
	}
	
	@Override
	public void start(Stage primaryStage) {
		primaryStage.setTitle("Poll Tracker");
		TabPane root = new TabPane(
				createTab("Setup Poll Tracker", FXML_FILES_LOCATION + "SetupPollTrackerView.fxml"),
				createTab("Edit Poll", FXML_FILES_LOCATION + "EditPollView.fxml"),
				createTab("Visualize Poll", FXML_FILES_LOCATION + "VisualizePollView.fxml")
									);
		Scene scene = new Scene(root,600,460);
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
