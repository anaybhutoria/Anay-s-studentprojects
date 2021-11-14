package minesweeper;

import minesweeper.models.player.Player;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * This class contains
 * utility methods that
 * are used by other classes
 * @author Marina McPeak and Mika Ong
 */
public class Utils {
    public static void main(String[] args) {
        writePlayerToFile(new Player("w", 100));
        List<Player> players = getPlayersFromFile();
        System.out.println();
        writePlayerToFile(new Player("z", 10));
        players = getPlayersFromFile();
        System.out.println();
    }

    /**
     * Gets player Data from a text file
     * @return player list 
     */
    public static List<Player> getPlayersFromFile()  {
        try {
            List<Player> players = new ArrayList<>();
            FileInputStream file = new FileInputStream("players.txt");
            ObjectInputStream reader = new ObjectInputStream(file);
            while (true) {
                try {
                    Player player = (Player)reader.readObject();
                    players.add(player);
                } catch (Exception ex) {
                    System.err.println("end of reader file ");
                    break;
                }
            }
            return players;
        } catch (Exception ex) {
            System.err.println("failed to read players.txt ");
        }
        return null;
    }

    /**
     * Writes the new player to the files
     * @param player new player to save
     */
    public static void writePlayerToFile(Player player)  {
      try {
          File f = new File("players.txt");
          FileOutputStream fos =
                        new FileOutputStream(f, true);
          ObjectOutputStream oos =
                        new ObjectOutputStream(fos);
          oos.writeObject(player);
          oos.close();
      }
      catch (Exception e)  {
          e.printStackTrace();
      }
    }

    /**
     * Gets the player from the player list
     * @param name name of wanted player
     * @param players the player list 
     * @return player
     */
    public static Player getPlayerFromList(String name,
                                           List<Player> players)  {
        for (Player p: players)  {
            if (p.getName().equalsIgnoreCase(name))  {
                return p;
            }
        }
        return null;
    }

    /**
     * Turns an array into a list
     * @param a player array
     * @return player list
     */
    public static List<Player> listFromArray(Player... a)  {
        List<Player> players = new ArrayList<>();
        for (Player p: a)  {
            players.add(p);
        }
        return players;
    }

    /**
     * Checks if the player input is valid
     * @param values player input
     * @param message message to be printed out if valid
     * @param errorRange range of valid inputs
     * @param scanner scanner where player input is stored
     * @return message on whether player input is valid
     */
    public static String getValidInput(String[] values,
               String message,
               String errorRange,
               Scanner scanner)  {
        String value;
        String errorMessage = "Enter " +
                "one of the following: " +
                errorRange;
        boolean wasError = false;
        do  {
            if (wasError)  {
                System.out.println(errorMessage);
            }
            wasError = false;
            System.out.print(message);
            value = scanner.nextLine();
            if (!arrayContains(values, value))  {
                wasError = true;
            }
        } while (wasError);
        return value;
    }

    /**
     * Makes a list of error messages
     * @param values error messsages
     * @return String of error messages
     */
    public static String makeErrorMessageList(String[] values)  {
        String result = "\n";
        for (int i = 0; i < values.length; i++)  {
            result += ((i + 1) + ". " +
            values[i] + "\n");
        }
        return result;
    }

    /**
     * Makes an error message
     * @param values
     * @return error message
     */
    public static String makeErrorMessage(String[] values)  {
        String result = "";
        for (int i = 0; i < values.length; i++)  {
            result += values[i];
            if (i < values.length - 1)  {
                result += ", ";
            }
        }
        return result;
    }

    /**
     * Checks if array contains value
     * @param a array to check
     * @param value wanted value
     * @return if value is in array
     */
    public static boolean arrayContains(String[] a, String value)  {
        for (String s: a)  {
            if (value.equalsIgnoreCase(s))  {
                return true;
            }
        }
        return false;
    }
}
