package Sudoku;

import Sudoku.Exception.FileOperationException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ResourceBundle;

public class FileSudokuBoardDao implements Dao<SudokuBoard> {
    private final ResourceBundle bundle = ResourceBundle.getBundle("Sudoku.resources.Languages");
    private String filename;

    public FileSudokuBoardDao(String filename) {
        this.filename = filename + ".txt";
    }

    @Override
    public SudokuBoard read() throws FileOperationException {
        SudokuBoard obj;
        try (FileInputStream fIS = new FileInputStream(filename);
             ObjectInputStream objectInputStream = new ObjectInputStream(fIS)) {
            obj = (SudokuBoard) objectInputStream.readObject();
        } catch (ClassNotFoundException | IOException e) {
            throw new FileOperationException(bundle.getObject("wrongFieldValue").toString());
        }
        return obj;
    }

    @Override
    public void write(SudokuBoard obj) throws FileOperationException {
        try (FileOutputStream fOS = new FileOutputStream(filename);
             ObjectOutputStream objectOutputStream = new ObjectOutputStream(fOS)) {
            objectOutputStream.writeObject(obj);
        } catch (IOException e) {
            throw new FileOperationException(bundle.getObject("wrongFieldValue").toString());
        }
    }

}