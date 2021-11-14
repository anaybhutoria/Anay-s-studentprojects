package minesweeper.models.game;

import minesweeper.models.player.Player;

/**
 * Players move
 * @author Marina McPeak
 * @version 1.0
 */
public class Move  {
   private Player player;
   private Point point;

   /**
    * Basic constructor for moves
    * @param point point to make move on
    */
   public Move(Point point) {
       this.point = point;
   }

   /**
    * Constructor that turns coordinates into a point to make move
    * @param row row of point
    * @param column column of point
    */
   public Move(int row, int column) {
        point = new Point(row, column);
    }

    /**
     * At a speicifc coordinate/point get row
     * @return get row
     */
   public int getRow() {
      return point.getRow();
   }

   /**
    * At a speicifc coordinate/point get column
    * @return get column
    */
   public int getColumn() {
      return point.getColumn();
   }

   /**
    * toString for the move
    * @return move
    */
    @Override
    public String toString() {
        return point.toString();
    }
}
