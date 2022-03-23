package Sudoku;


public class SudokuRow extends SudokuElement {
    public SudokuRow() {
        super();
    }

    @Override
    public SudokuRow clone() {
        SudokuRow row = new SudokuRow();
        for (int i = 0; i < 9; i++) {
            SudokuField field = new SudokuField();
            field.setFieldValue(this.element.get(i).getFieldValue());
            row.setElement(i, field);
        }
        return row;
    }

}
