package Sudoku;

import java.util.ListResourceBundle;

public class Authors extends ListResourceBundle {
    protected Object[][] getContents() {
        return new Object[][] {
                {"imie1", "Kacper"},
                {"imie2", "Mikolaj"},
                {"nazwisko1", "Kuchciak"},
                {"nazwisko2", "Dzikowski"}
        };
    }
}
