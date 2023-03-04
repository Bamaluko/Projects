package Sudoku;

import Sudoku.Exception.DatabaseException;

public class SudokuBoardDaoFactory {
    public Dao<SudokuBoard> getFileDao(String filename) {
        return new FileSudokuBoardDao(filename);
    }

    public Dao<SudokuBoard> getDatabaseDao(String filename) throws  DatabaseException {
        return new JdbcSudokuBoardDao(filename);
    }
}
