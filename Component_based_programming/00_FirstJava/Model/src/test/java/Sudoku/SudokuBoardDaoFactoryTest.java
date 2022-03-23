package Sudoku;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuBoardDaoFactoryTest {

    private SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();

    @Test
    public void getFileDaoTest() {
        assertNotNull(factory.getFileDao("filename"));
    }
}
