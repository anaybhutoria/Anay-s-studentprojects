package minesweeper.display.player;

import minesweeper.models.player.Player;
import java.util.List;

/**
 * This class is an interface used to hold the methods 
 * which will be used by instances of ConsolePlayerPainter
 * @version 1.0
 * @author Anay Bhutoria
 */
public interface PlayerPainter {
    void paint(Player player);
    void paint(List<Player> players);
}
