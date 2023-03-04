package Sudoku;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SudokuBoardTest {

    public SudokuBoardTest() {
    }

    @Test
    public void testConstructor() {
        SudokuBoard board = new SudokuBoard();
        for (int i = 0; i<9; i++) {
            for  (int j = 0; j < 9; j++) {
                assertEquals(board.get(i, j),0);
            }
        }
    }

    @Test
    public void testIfSudokuBoardCorrectColumn() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++)
            {
                boolean flag = true;
                int num = board.get(i, j);
                for (int k = 0; k < 9; k++) {
                    if (board.get(i, k) == num && k != j) {
                        flag = false;
                    }
                }
                assertTrue(flag);
            }
        }
    }

    @Test
    public void testIfSudokuBoardCorrectRow() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                boolean flag = true;
                int num = board.get(i, j);
                for (int k = 0; k < 9; k++) {
                    if (board.get(k, j) == num && k != i) {
                        flag = false;
                    }
                }
                assertTrue(flag);
            }
        }
    }

    @Test
    public void testIfSudokuBoardCorrectBox() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                boolean flag = true;
                int num = board.get(i, j);
                int a = i - i % 3;
                int b = j - j % 3;
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if ((board.get(l + a, k + b) == num && l + a != i && k + b != j)) {
                            flag = false;
                        }
                    }
                }
                assertTrue(flag);
            }
        }
    }

    @Test
    public void setterTest() {
        SudokuBoard board = new SudokuBoard();
        board.set(0, 0, 7);
        assertEquals(board.get(0, 0), 7);
        board.set(0, 0, 5);
        assertEquals(board.get(0, 0), 5);
    }

    @Test
    public void testEqualsMethod() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2;
        board1.solveGame();
        board2 = board1.clone();
        for(int j =0; j < 9; j++) {
            for(int i =0; i < 9; i++) {
                board2.set(i, j, board1.get(i, j));
            }
        }
        boolean assertion = board1.equals(board2);
        assertTrue(assertion);
    }

    @Test
    public void testEqualsNull() {
        SudokuBoard board1 = new SudokuBoard();
        board1.solveGame();
        boolean assertion = board1.equals(null);
        assertFalse(assertion);
    }

    @Test
    public void testEqualsDifferentObjectType() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuField field1 = new SudokuField();
        board1.solveGame();
        boolean assertion = board1.equals(field1);
        assertFalse(assertion);
    }

    @Test
    public void testEqualsMethodNegativeCase() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board1.solveGame();
        for(int j =0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                board2.set(i, j, 1);
            }
        }
        boolean assertion = board1.equals(board2);
        assertFalse(assertion);
    }

    @Test
    public void testTwoBoardsNotIdentical() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board1.solveGame();
        board2.solveGame();
        assertFalse(board1.equals(board2));
    }

    @Test
    public void testTwoBoardsNotIdenticalNegativeCase() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board1.solveGame();
        for(int j =0; j < 9; j++) {
            for(int i =0; i < 9; i++) {
                board2.set(i, j, board1.get(i, j));
            }
        }
        assertTrue(board1.equals(board2));
    }

    @Test
    public void testToStringMethod() {
        SudokuBoard board1 = new SudokuBoard();
        String napis;
        napis = """
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                -------------------
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                -------------------
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                0 0 0 |0 0 0 |0 0 0\s
                -------------------
                """;
        assertEquals(board1.toString(), napis);
        board1.solveGame();
    }

    @Test
    public void testHashCode() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board1.solveGame();
        for(int j =0; j < 9; j++) {
            for(int i =0; i < 9; i++) {
                board2.set(i, j, board1.get(i, j));
            }
        }
        assertEquals(board1.hashCode(), board2.hashCode());
    }

    @Test
    public void testHashCodeNegativeCase() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board1.solveGame();
        board2.solveGame();
        assertNotEquals(board1.hashCode(), board2.hashCode());
    }

    @Test
    public void testCloneMethod() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2;
        board1.solveGame();
        board2 = board1.clone();
        assertTrue(board1.equals(board2));
    }

}
