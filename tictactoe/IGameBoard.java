package tictactoe;

/**
 * IGameBoard represents a 2-dimensional gameboard that has characters
 * on it as markers (X, O). No space on the board can have multiple
 * players, and there can be a clear winner. Board is NUM_ROWS x
 NUM_COLS in size
 *
 * Initialization ensures: the Board does not have any markers on it
 * Defines: NUM_ROWS: Z
 * Defines: NUM_COLS: Z
 * Constraints: 0< NUM_ROWS <= MAX_SIZE
 * 0< NUM_COLS <= MAX_SIZE
 */
public interface IGameBoard {
    int MAX_SIZE = 100;

    /**
     * @param pos BoardPosition object to check
     * @return Check if board space is available for marker placement (true), otherwise (false)
     * @requires 0 <= pos.getRow(), 0 <= pos.getColumn()
     * @ensures boolean = true if space is available
     *          boolean = false if space is unavailable/invalid
     */
    boolean checkSpace(BoardPosition pos);

    /**
     * @param lastPos
     * @requires checkSpace(marker) = true
     * @ensures marker is placed in specified board space
     */
    void placeMarker(BoardPosition lastPos);

    /**
     * @param lastPos
     * @requires n/a
     * @return true/false
     * @ensures check whether the player wins on the diagonal, horizontal, or vertical
     */
    boolean checkForWinner(BoardPosition lastPos);
}
