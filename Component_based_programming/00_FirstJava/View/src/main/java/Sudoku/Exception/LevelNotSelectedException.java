package Sudoku.Exception;

public class LevelNotSelectedException extends NullPointerException{
    public LevelNotSelectedException(Throwable cause) {
        super(String.valueOf(cause));
    }
}
