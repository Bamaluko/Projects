package Sudoku;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;


public class SudokuBoard implements Serializable, Cloneable {

    private List<List<SudokuField>> board;

    private final BacktrackingSudokuSolver solver;

    public SudokuBoard() {
        //Creates a board.For now, it's just filled with 0.
        this.solver = new BacktrackingSudokuSolver();
        //Creating a list of lists with nine SudokuFields
        board = Arrays.asList(new List[9]);

        //Ensuring that the internal list will contain nine SudokuFields
        for (int i = 0; i < 9; i++) {
            board.set(i, Arrays.asList(new SudokuField[9]));
        }

        //Filling the board with default sudoku fields (they have 0 as their default value)
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                this.board.get(i).set(j, new SudokuField());
            }
        }
    }

    public int get(int i, int j) {
        //This method returns value from given index.
        return board.get(i).get(j).getFieldValue();
    }

    public void set(int i, int j, int num) {
        //This method returns value from given index.
        this.board.get(i).get(j).setFieldValue(num);
    }

    public void solveGame() {
        solver.solve(this);
    }

    public boolean checkRow(int i, int j, int num) {
        //Checks if the row that contains given field meets the game rules.
        for (int k = 0; k < 9; k++) {
            if (board.get(k).get(j).getFieldValue() == num && k != i) {
                return false;
            }
        }
        return true;
    }

    public boolean checkColumn(int i, int j, int num) {
        //Checks if the row that contains given field meets the game rules.
        for (int k = 0; k < 9; k++) {
            if (board.get(i).get(k).getFieldValue() == num && k != j) {
                return false;
            }
        }
        return true;
    }

    public boolean checkSquare(int i, int j, int num) {
        //Checks if the box that contains given field meets the game rules.
        int a = i - i % 3;
        int b = j - j % 3;
        for (int k = 0; k < 3; k++) {
            for (int l = 0; l < 3; l++) {
                if (board.get(l + a).get(k + b).getFieldValue()
                        == num && l + a != i && k + b != j) {
                    return false;
                }
            }
        }
        return true;
    }

    public SudokuElement getSudokuBox(int i, int j) {
        //Returns the sudoku box of given field.
        int a = i - i % 3;
        int b = j - j % 3;
        int counter = 0;
        SudokuBox element = new SudokuBox();
        for (int k = 0; k < 3; k++) {
            for (int l = 0; l < 3; l++) {
                    element.setElement(counter, board.get(l + a).get(k + b));
                    counter++;
            }
        }
        return  element;
    }


    public SudokuElement getSudokuRow(int j) {
        //Returns the row of given field.
        SudokuRow element = new SudokuRow();
        for (int i = 0; i < 9; i++) {
            element.setElement(i, board.get(i).get(j));
        }
        return  element;
    }

    public SudokuElement getSudokuColumn(int i) {
        //Returns the column of given field.
        SudokuColumn element = new SudokuColumn();
        for (int j = 0; j < 9; j++) {
            element.setElement(j, board.get(i).get(j));
        }
        return  element;
    }

    @Override
    public String toString() {
        StringBuilder napis = new StringBuilder();
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                napis.append(this.get(i, j)).append(" ");
                if (i % 3 == 2 && i != 8) {
                    napis.append("|");
                }
            }
            napis.append("\n");
            if (j % 3 == 2) {
                napis.append("-".repeat(19));
                napis.append("\n");
            }
        }
        return napis.toString();
    }

    @Override
    public boolean equals(final Object obj) {
        if (obj == null) {
            return  false;
        } else if (!(obj instanceof SudokuBoard)) {
            return false;
        } else {
            return new EqualsBuilder().append(board, ((SudokuBoard) obj).board).isEquals();
        }
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37)
                .append(board).toHashCode();
    }

    @Override
    public SudokuBoard clone() {
        SudokuBoard sudokuBoard = new SudokuBoard();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sudokuBoard.set(i, j, get(i, j));
            }
        }

        return sudokuBoard;
    }

}

