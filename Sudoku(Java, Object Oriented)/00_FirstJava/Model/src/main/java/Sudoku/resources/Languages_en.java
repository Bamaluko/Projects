package Sudoku.resources;

import java.io.Serializable;
import java.util.ListResourceBundle;

public class Languages_en extends ListResourceBundle implements Serializable {

    @Override
    protected Object[][] getContents() {
        return new Object[][]{
                {"wrongFieldValue", "Wrong field value. "
                        + "Proper number should be an integer from section <1,9>."},
                {"fileOperationException", "Couldn't perform an operation on the file."},
                {"loadDB", "Couldn't load from database."},
                {"saveDB", "Couldn't save to database."},
                {"connectionError", "Cannot connect to database."}
        };
    }
}