package tictactoe;

/**
 * The TicTacToe controller class will handle communication between our TicTacToeView and our Model (IGameBoard and BoardPosition)
 */
public class TicTacToeController {
    //our current game that is being played
    private IGameBoard curGame;
    //to track who's turn it is
    private char curPlayer;
    //The screen that provides our view
    private TicTacToeView screen;


    /**
     *
     * @param model the number of rows you want in the tic tac toe grid
     * @param view the number of columns you want in the tic tac toe grid
     * @ensures a functional controller for the given view and model will be created;
     *           and first player to move is 'X'
     */
    TicTacToeController(IGameBoard model, TicTacToeView view)
    {
        curGame = model;
        screen = view;
        curPlayer = 'X';

    }

    /**
     *
     * @param row row number user has clicked on
     * @param col column number user has clicked on
     * @ensures game screen will be updated accordingly;
     *          if the space is unavailable or a player wins,
     *          user will be notified
     */
    public void processButtonClick(int row, int col)
    {
        BoardPosition currPlayerMove = new BoardPosition(row, col, curPlayer);

        if(!(curGame.checkSpace(currPlayerMove)))
            screen.setMessage("That space is unavailable, please pick again.");
        else{
            curGame.placeMarker(currPlayerMove);
            screen.setMarker(row,col,curPlayer);

            if(curGame.checkForWinner(currPlayerMove))
                screen.setMessage("Player " + curPlayer + " wins!");
            else {
                curPlayer = curPlayer == 'X' ? 'O' : 'X';
                screen.setMessage("Player " + curPlayer + ", it is your turn.");
            }

        }




    }
}
