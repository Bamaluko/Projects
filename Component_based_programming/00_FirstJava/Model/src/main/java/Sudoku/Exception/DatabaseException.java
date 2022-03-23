package Sudoku.Exception;

public class DatabaseException extends DaoClassException {
    public DatabaseException(String cause) {
        super(String.valueOf(cause));
    }
}
