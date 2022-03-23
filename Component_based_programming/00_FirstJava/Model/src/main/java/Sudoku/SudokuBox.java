package Sudoku;

public class SudokuBox extends SudokuElement {

    public SudokuBox() {
        super();
    }

    @Override
    public SudokuBox clone() {
        SudokuBox box = new SudokuBox();
        for (int i = 0; i < 9; i++) {
            SudokuField field = new SudokuField();
            field.setFieldValue(this.element.get(i).getFieldValue());
            box.setElement(i, field);
        }
        return box;
    }
}
