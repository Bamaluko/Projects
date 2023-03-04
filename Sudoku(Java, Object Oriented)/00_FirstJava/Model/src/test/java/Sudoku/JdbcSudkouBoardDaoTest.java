package Sudoku;
import Sudoku.Exception.DaoClassException;
import Sudoku.Exception.DatabaseException;
import Sudoku.Exception.FileOperationException;
import org.apache.commons.lang3.SystemUtils;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import static org.junit.jupiter.api.Assertions.*;

public class JdbcSudkouBoardDaoTest {
    public JdbcSudkouBoardDaoTest() {
    }

    @Test
    void daoReadSaveDatabaseTest() throws DaoClassException {
        SudokuBoard board1 = new SudokuBoard();
        board1.solveGame();
        SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        String name = dtf.format(now).toString();
        factory.getDatabaseDao(name).write(board1);
        SudokuBoard board2 = factory.getDatabaseDao(name).read();
        assertEquals(board1, board2);
    }

    @Test
    void wrongInputTest() throws DaoClassException {
        DatabaseException thrown = Assertions.assertThrows(DatabaseException.class, () -> {
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();;
            if (SystemUtils.IS_OS_WINDOWS) {
                factory.getDatabaseDao("?").read();
            } else if (SystemUtils.IS_OS_LINUX) {
                factory.getDatabaseDao("/").read();
            } else {
                factory.getDatabaseDao("?").read();
            }
        });
    }

    @Test
    void databaseAlreadyExistsWriteScenario() throws DaoClassException {
        DatabaseException thrown = Assertions.assertThrows(DatabaseException.class, () -> {
            SudokuBoard board2 = new SudokuBoard();
            board2.solveGame();
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            String name = dtf.format(now).toString();
            name += "z";
            factory.getDatabaseDao(name).write(board2);
            factory.getDatabaseDao(name).write(board2);
        });
    }

    @Test
    void databaseDoesNotExistsReadScenario() throws DaoClassException {
        DatabaseException thrown = Assertions.assertThrows(DatabaseException.class, () -> {
            SudokuBoard board1 = new SudokuBoard();
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            String name = dtf.format(now).toString();
            name += "zz";
            board1 = factory.getDatabaseDao(name).read();
        });
    }
}
