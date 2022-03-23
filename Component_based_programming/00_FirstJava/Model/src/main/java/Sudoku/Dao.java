package Sudoku;

import Sudoku.Exception.DaoClassException;
import Sudoku.Exception.DatabaseException;
import Sudoku.Exception.FileOperationException;

public interface Dao<T> {

    T read() throws DaoClassException;

    void write(T obj) throws FileOperationException, DatabaseException;

}