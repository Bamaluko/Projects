package Sudoku;

public class SudokuColumn extends SudokuElement {

    public SudokuColumn() {
        super();
    }

    @Override
    public SudokuColumn clone() {
        SudokuColumn column = new SudokuColumn();
        for (int i = 0; i < 9; i++) {
            SudokuField field = new SudokuField();
            field.setFieldValue(this.element.get(i).getFieldValue());
            column.setElement(i, field);
        }
        return column;
    }
}

