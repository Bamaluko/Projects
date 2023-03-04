package Sudoku;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;

public class BacktrackingSudokuSolver implements  SudokuSolver, Serializable {
    @Override
    public void solve(SudokuBoard board) {
        this.backtrackingAlgorithm(board);
    }

    @Override
    public boolean backtrackingAlgorithm(SudokuBoard board) {
        //This simple method keeps on going through the table
        // inserting matching numbers into empty fields. If it
        // meets a dead end it makes a step back through recursion.
        ArrayList<Integer> table = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9));
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                for (int z = 0; z < 9; z++) {
                    int index1 = (int) (Math.random() * 8);
                    int index2 = (int)(Math.random() * 8);
                    int temp = table.get(index1);
                    table.set(index1, table.get(index2));
                    table.set(index2, temp);

                }
                if (board.get(i, j) == 0) {
                    for (int num = 0; num <= 8; num++) {
                        board.set(i, j, table.get(num));
                        if (board.checkSquare(i, j, table.get(num))
                                && board.checkRow(i, j, table.get(num))
                                && board.checkColumn(i, j, table.get(num))
                                && backtrackingAlgorithm(board)) {
                            return true;
                        }
                        board.set(i, j, 0);
                    }
                    return false;
                }
            }
        }
        return true;
    }
}
