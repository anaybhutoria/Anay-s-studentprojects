package minesweeper;

import minesweeper.models.player.Player;
import java.util.List;

/**
 * This class is used as a simple test file
 * to test the functionality of other classes.
 * @author Marina McPeak
 * @version 1.0
 */
public class TestUtils {
    public static List<Player> testPlayers() {
        List<Player> players =
                Utils.listFromArray(
                        new Player("Matt"),
                        new Player("Mike"),
                        new Player("Mark", 104),
                        new Player("Mary", 12),
                        new Player("May", 34));
        return players;
    }

}
