package Sudoku;

import java.util.Arrays;
import java.util.List;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;

public class SudokuElement implements Cloneable {

    protected List<SudokuField> element = Arrays.asList(new SudokuField[9]);

    public boolean verify() {
        //We need to have 1,2,3,4,5,6,7,8,9 as values in every box, column, row. If we multiply
        // those values we can easily check if all these numbers are present.
        int aimValue = 362880;
        int counter = 1;
        for (int i = 0; i < 9; i++) {
            counter *= element.get(i).getFieldValue();
        }
        return counter == aimValue;

    }

    public void setElement(int i, SudokuField field) {
        element.set(i, field);
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37).append(element).toHashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return new EqualsBuilder().append(element, ((SudokuElement) obj).element).isEquals();
    }

    @Override
    public String toString() {
        StringBuilder napis = new StringBuilder();
        for (int i = 0; i < 9; i++) {
            napis.append(element.get(i)).append(" ");
        }
        return napis.toString();
    }
}
