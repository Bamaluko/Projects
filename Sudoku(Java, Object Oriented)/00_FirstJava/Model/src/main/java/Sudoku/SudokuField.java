package Sudoku;

import Sudoku.Exception.WrongFieldValueException;
import java.io.Serializable;
import java.util.ResourceBundle;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;

public class SudokuField implements  Serializable, Cloneable, Comparable<SudokuField> {
    private final ResourceBundle bundle = ResourceBundle.getBundle("Sudoku.resources.Languages");
    private int value = 0;

    public SudokuField() {
    }

    public int getFieldValue() {
        return value;
    }

    public void setFieldValue(int value) {
        if (value >= 0 && value <= 9) {
            this.value = value;
        } else {
            throw new WrongFieldValueException(bundle.getObject("wrongFieldValue").toString());
        }
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37).append(value).toHashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return new EqualsBuilder().append(value, ((SudokuField) obj).value).isEquals();
    }

    @Override
    public String toString() {
        return String.valueOf(this.getFieldValue());
    }

    @Override
    public int compareTo(SudokuField field) {
        if (field == null) {
            throw new NullPointerException();
        } else {
            return Integer.compare(this.getFieldValue(), field.getFieldValue());
        }
    }

    @Override
    public SudokuField clone() {
        SudokuField sudokuField = new SudokuField();
        sudokuField.value = this.value;
        return sudokuField;
    }

}

