package tictactoe;

/**
 * This class exists to declare our model, view, and controller objects, connect them, and start the game
 *
 */
public final class TicTacToeGame {

    /**
     * This is the entry point for our tic tac toe game
     * @param args ignored in this program
     */
    public static void main(String[] args)
    {
        int row = 10;
        int col = 10;
        int win = 5;

        IGameBoard model = new GameBoardFast(row, col, win); //Can easily swap implementation
        TicTacToeView view = new TicTacToeView(row, col);
        TicTacToeController controller = new TicTacToeController(model, view);

        view.registerObserver(controller);
    }
}
