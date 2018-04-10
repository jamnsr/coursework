package tictactoe;

public class BoardPosition {
    private int row;
    private int column;
    private char player;

    /**
     * @param r number to set object's row value
     * @param c number to set object's column value
     * @param p character to set object's player value
     * @requires r = int, c = int, p = char
     * @ensures BoardPosition object is initialized with given params
     */
    BoardPosition(int r, int c, char p){
        row = r;
        column = c;
        player = p;
    }

    /**
     *
     * @return BoardPosition object's row variable
     * @ensures getRow = BoardPosition.row
     */
    public int getRow(){ return row; }

    /**
     *
     * @return BoardPosition object's column variable
     * @ensures getColumn = BoardPosition.column
     */
    public int getColumn(){
        return column;
    }

    /**
     *
     * @return BoardPosition object's player variable
     * @ensures getPlayer = BoardPosition.player
     */
    public char getPlayer(){
        return player;
    }

    // Overriding equals() to compare two BoardPosition objects
    @Override
    public boolean equals(Object obj) {

        // If the object is compared with itself then return true
        if (obj == this) {
            return true;
        }

        // Check if obj is an instance of BoardPosition or not
        if (!(obj instanceof BoardPosition)) {
            return false;
        }

        // typecast o to Complex so that we can compare data members
        BoardPosition c = (BoardPosition) obj;

        // Compare the data members and return accordingly
        return this.row == c.row &&
                this.column == c.column &&
                this.player == c.player;
    }

}
