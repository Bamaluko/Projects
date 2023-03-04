package Sudoku;

public interface SudokuSolver {

    void solve(SudokuBoard board);

    boolean backtrackingAlgorithm(SudokuBoard board);
}
