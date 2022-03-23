package Sudoku;

import Sudoku.Exception.SudokuElementIndexOutOfBoundsException;
import Sudoku.Exception.WrongFieldValueException;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuElementTest {
    public SudokuElementTest() {
    }

    @Test
    void sudokuRowCheckPositive() {
        SudokuBoard board1 = new SudokuBoard();
        for(int i = 0; i < 9; i++) {
            board1.set(i, 1, i+1);
        }
        assertTrue(board1.getSudokuRow(1).verify());
    }

    @Test
    void sudokuRowCheckNegative() {
        SudokuBoard board1 = new SudokuBoard();
        for(int i = 0; i < 9; i++) {
            board1.set(i, 1, i+1);
        }
        board1.set(1, 1, 9);
        assertFalse(board1.getSudokuRow(1).verify());
    }

    @Test
    void sudokuColumnCheckPositive() {
        SudokuBoard board1 = new SudokuBoard();
        for(int j = 0; j < 9; j++) {
            board1.set(1, j, j+1);
        }
        assertTrue(board1.getSudokuColumn(1).verify());
    }

    @Test
    void sudokuColumnCheckNegative() {
        SudokuBoard board1 = new SudokuBoard();
        for(int j = 0; j < 9; j++) {
            board1.set(1, j, j+1);
        }
        board1.set(1, 1, 9);
        assertFalse(board1.getSudokuRow(1).verify());
    }
    @Test
    void sudokuBoxCheckPositive() {
        SudokuBoard board = new SudokuBoard();
        board.set(0, 0, 1);
        board.set(1, 0, 2);
        board.set(2, 0, 3);
        board.set(0, 1, 4);
        board.set(1, 1, 5);
        board.set(2, 1, 6);
        board.set(0, 2, 7);
        board.set(1, 2, 8);
        board.set(2, 2, 9);
        assertTrue(board.getSudokuBox(1, 2).verify());
    }

    @Test
    void sudokuBoxCheckNegative() {
        SudokuBoard board = new SudokuBoard();
        board.set(3, 6, 1);
        board.set(4, 6, 2);
        board.set(5, 6, 3);
        board.set(3, 7, 4);
        board.set(4, 7, 4);
        board.set(5, 7, 6);
        board.set(3, 8, 7);
        board.set(4, 8, 8);
        board.set(5, 8, 9);
        assertFalse(board.getSudokuBox(3, 8).verify());
    }

    @Test
    void toStringTest() {
        SudokuBoard board = new SudokuBoard();
        assertEquals("0 0 0 0 0 0 0 0 0 ", board.getSudokuBox(0,0).toString());
    }

    @Test
    void equalsTest() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        assertTrue(board1.getSudokuBox(0,0).equals(board2.getSudokuBox(0,0)));
    }

    @Test
    void equalsNegativeCaseTest() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board2.set(0,0,1);
        assertFalse(board1.getSudokuBox(0,0).equals(board2.getSudokuBox(0,0)));
    }

    @Test
    void hashCodeTest() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        assertTrue(board1.getSudokuBox(0,0).hashCode() == board2.getSudokuBox(0,0).hashCode());
    }

    @Test
    void hashCodeNegativeCaseTest() {
        SudokuBoard board1 = new SudokuBoard();
        SudokuBoard board2 = new SudokuBoard();
        board2.set(0,0,1);
        assertFalse(board1.getSudokuBox(0,0).hashCode() == board2.getSudokuBox(0,0).hashCode());
    }

    @Test
    void sudokuRowCloneTest() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        SudokuRow row1;
        row1 = (SudokuRow)board.getSudokuRow(2);
        SudokuRow row2 = row1.clone();
        assertTrue(row1.equals(row2));
    }

    @Test
    void sudokuColumnCloneTest() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        SudokuColumn column1;
        column1 = (SudokuColumn) board.getSudokuColumn(2);
        SudokuColumn column2 = column1.clone();
        assertTrue(column1.equals(column2));
    }

    @Test
    void sudokuBoxCloneTest() {
        SudokuBoard board = new SudokuBoard();
        board.solveGame();
        SudokuBox box1;
        box1 = (SudokuBox) board.getSudokuBox(2,2);
        SudokuBox box2 = box1.clone();
        assertTrue(box1.equals(box2));
    }

}

