package Sudoku.resources;

import java.io.Serializable;
import java.util.ListResourceBundle;

public class Languages_pl extends ListResourceBundle implements Serializable {

    @Override
    protected Object[][] getContents() {
        return new Object[][]{
                {"wrongFieldValue", "Bledna wartosc dla pola."
                        + " Nalezy wybrac integer z przedzialu <1,9>."},
                {"fileOperationException", "Blad przy operacji na pliku."},
                {"loadDB", "Blad przy wczytywaniu z bazy danych."},
                {"saveDB", "Blad przy zapisie do bazy danych."},
                {"connectionError", "Nie mozna ustanowic polaczenia z baza danych."}
        };
    }
}
