package Sudoku;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import Sudoku.Exception.WrongFieldValueException;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuFieldTest {

    @Test
    public void constructorTest() {
        SudokuField field = new SudokuField();
        assertEquals(0, field.getFieldValue());
    }

    @Test
    public void setterProperValuesTest() {
        SudokuField field = new SudokuField();
        field.setFieldValue(9);
        assertEquals(9, field.getFieldValue());
        field.setFieldValue(0);
        assertEquals(0, field.getFieldValue());
    }

    @Test
    public void setterValueTooLowTest() {
        WrongFieldValueException thrown = Assertions.assertThrows(WrongFieldValueException.class, () -> {
            SudokuField field = new SudokuField();
            field.setFieldValue(-1);
        });
    }

    @Test
    public void setterValueTooHighTest() {
        WrongFieldValueException thrown = Assertions.assertThrows(WrongFieldValueException.class, () -> {
            SudokuField field = new SudokuField();
            field.setFieldValue(10);
        });
    }

    @Test
    public void equalsTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2;
        field2 = field1.clone();
        assertTrue(field1.equals(field2));
    }

    @Test
    public void equalsTestNegativeCase() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        field2.setFieldValue(9);
        assertFalse(field1.equals(field2));
    }

    @Test
    public void hashCodeTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        assertTrue(field1.hashCode() == field2.hashCode());
    }

    @Test
    public void hashCodeNegativeCaseTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        field2.setFieldValue(9);
        assertFalse(field1.hashCode() == field2.hashCode());
    }

    @Test
    public void toStringTest() {
        SudokuField field1 = new SudokuField();
        assertEquals("0", field1.toString());
    }

    @Test
    public void compareToIsEqualTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        field2.setFieldValue(9);
        field1.setFieldValue(9);
        assertEquals(field1.compareTo(field2), 0);
    }

    @Test
    public void compareToIsGreaterTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        field2.setFieldValue(8);
        field1.setFieldValue(9);
        assertEquals(field1.compareTo(field2), 1);
    }

    @Test
    public void compareToIsSmallerTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = new SudokuField();
        field2.setFieldValue(9);
        field1.setFieldValue(8);
        assertEquals(field1.compareTo(field2), -1);
    }

    @Test
    public void compareToNullPointerExceptionTest() {
        NullPointerException thrown = Assertions.assertThrows(NullPointerException.class, () -> {
            SudokuField field1 = new SudokuField();
            int useless = field1.compareTo(null);
        });
        assertNull(thrown.getMessage());
    }

    @Test
    public void cloneMethodTest() {
        SudokuField field1 = new SudokuField();
        SudokuField field2;
        field1.setFieldValue(8);
        field2 = field1.clone();
        assertEquals(field1.compareTo(field2), 0);
    }
}
