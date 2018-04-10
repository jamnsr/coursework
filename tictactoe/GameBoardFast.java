package tictactoe;

/**
 * @invariant 0 < ROWS <= MAX_SIZE
 * @invariant 0 < COLS <= MAX_SIZE
 * @invariant WINCOUNT <= ROWS & WINCOUNT <= COLS
 * Correspondence NUM_ROWS = ROWS
 * Correspondence NUM_COLS = COLS
 * Correspondence this = board[0...ROWS-1][0...COLS-1]
 */
public class GameBoardFast implements IGameBoard {

    private int ROWS;
    private int COLS;
    private int WINCOUNT;

    private char[][] board = new char[MAX_SIZE][MAX_SIZE];

    /**
     * @requires 0 < r <= MAX_SIZE & 0 < c <= MAX_SIZE & w <= r & w <= c
     * @ensures New board, with ROWS = r & COLS = c & WINCOUNT = w, is empty
     * @param r number of rows to use in board
     * @param c number of columns to use in board
     * @param w number of tokens in a row to win
     */
    GameBoardFast(int r, int c, int w){
        ROWS = r;
        COLS = c;
        WINCOUNT = w;

        for(int i=0; i<r; i++)
            for(int j=0; j<c; j++)
                board[i][j] = ' ';
    }


    public boolean checkSpace(BoardPosition pos)
    {
        return  pos.getRow() < ROWS &&
                pos.getColumn() < COLS &&
                board[pos.getRow()][pos.getColumn()] == ' ';
    }

    public void placeMarker(BoardPosition marker)
    {
        board[marker.getRow()][marker.getColumn()] = marker.getPlayer();
    }


    public boolean checkForWinner(BoardPosition lastPos)
    {
        return checkHorizontalWin(lastPos) || checkVerticalWin(lastPos) || checkDiagonalWin(lastPos);
    }

    /**
     * @param lastPos
     * @requires n/a
     * @return checks to see if the last marker placed resulted in win (true) otherwise (false)
     * @ensures checks whether the player wins or not on the horizontal
     */
    private boolean checkHorizontalWin(BoardPosition lastPos)
    {
        int i = lastPos.getRow();
        int j = lastPos.getColumn();
        int count = 0;

        //Move to the first horizontal mark on current horizontal
        while(board[i][j] == lastPos.getPlayer() && j>0) {
            if(board[i][j-1] != lastPos.getPlayer()){
                break;
            }
            --j;
        }
        //Count all consecutive horizontal marks on current horizontal
        while(board[i][j] == lastPos.getPlayer() && j<= COLS - 1) {
            ++j;
            ++count;
            if(j == COLS)
                break;
        }


        return count >= WINCOUNT;

    }

    /**
     * @param lastPos
     * @requires n/a
     * @return checks to see if the last marker placed resulted in win (true) otherwise (false)
     * @ensures checks whether the player wins or not on the vertical
     */
    private boolean checkVerticalWin(BoardPosition lastPos)
    {
        int i = lastPos.getRow();
        int j = lastPos.getColumn();
        int count = 0;
        //Move to the first vertical mark on the current vertical
        while(board[i][j] == lastPos.getPlayer() && i>0) {
            if(board[i-1][j] != lastPos.getPlayer()){
                break;
            }
            --i;
        }
        //Count all consecutive vertical marks on the current vertical
        while(board[i][j] == lastPos.getPlayer() && i<= ROWS - 1) {
            ++i;
            ++count;
            if(i == ROWS)
                break;
        }


        return count >= WINCOUNT;
    }

    /**
     * @param lastPos
     * @return checks to see if the last marker placed resulted in win (true) otherwise (false)
     * @requires n/a
     * @ensures checks whether the player wins or not on the diagonal
     */
    private boolean checkDiagonalWin(BoardPosition lastPos)
    {
        int direction_row = 1, direction_col = -1, row, col, count;
        for ( int i = 0; i < 2; i++, direction_col *= -1){
            count = 1;
            for (int j= 0; j < 2; j++, direction_row *= -1, direction_col *= -1) {
                row = lastPos.getRow();
                col = lastPos.getColumn();
                while((row += direction_row) >= 0 && row < ROWS &&
                        (col += direction_col) >= 0 && col < COLS &&
                        board[row][col] == lastPos.getPlayer())
                    count++;
            }
            if(count >= WINCOUNT)
                return true;
        }
        return  false;
    }


    /**
     * @Override
     * @return string depicting entire board
     */
    public String toString(){
        String game = "";

        game += "    ";

        for(int i = 0; i < COLS; i++){
            if(i < 10)
                game += i + " |";
            else
                game += i + "|";

        }
        game += "\n";

        for(int j = 0; j < ROWS; j++){
            if(j < 10)
                game += " " + j;
            else
                game += j;
            for(int k = 0; k < COLS; k++){
                game += " |" + board[j][k];
                if(k == COLS - 1)
                    game += " |\n";
            }
        }

        return game;
    }
}
