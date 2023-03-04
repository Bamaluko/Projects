package Sudoku;

import Sudoku.Exception.DaoClassException;
import Sudoku.Exception.DatabaseException;
import Sudoku.Exception.FileOperationException;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import java.util.ResourceBundle;

import static org.junit.jupiter.api.Assertions.*;

public class FileSudokuBoardDaoTest {
    private final ResourceBundle bundle = ResourceBundle.getBundle("Sudoku.resources.Languages");
    private SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
    private SudokuBoard sudokuBoard = new SudokuBoard();
    private Dao<SudokuBoard> fileSudokuBoardDao;
    private SudokuBoard sudokuBoard2;

    @Test
    public void writeReadTest() throws DaoClassException {
        fileSudokuBoardDao = factory.getFileDao("filename");
        fileSudokuBoardDao.write(sudokuBoard);
        sudokuBoard2 = fileSudokuBoardDao.read();
        assertEquals(sudokuBoard, sudokuBoard2);
    }

    @Test
    public void readIOExceptionTest() {
        FileOperationException thrown = Assertions.assertThrows(FileOperationException.class, () -> {
            fileSudokuBoardDao = factory.getFileDao("filename1");
            fileSudokuBoardDao.read();
        });

        Assertions.assertEquals(bundle.getObject("wrongFieldValue").toString(), thrown.getMessage());
    }

    @Test
    public void writeIOExceptionTest() {
        FileOperationException thrown = Assertions.assertThrows(FileOperationException.class, () -> {
            fileSudokuBoardDao = factory.getFileDao("?");
            fileSudokuBoardDao.write(sudokuBoard);
        });

        Assertions.assertEquals(bundle.getObject("wrongFieldValue").toString(), thrown.getMessage());
    }

}
