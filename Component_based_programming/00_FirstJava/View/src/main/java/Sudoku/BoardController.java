package Sudoku;

import Sudoku.Exception.DaoClassException;
import Sudoku.Exception.DatabaseException;
import Sudoku.Exception.FileOperationException;
import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputDialog;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import org.apache.commons.lang3.math.NumberUtils;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;

import java.util.Optional;
import java.util.ResourceBundle;

public class BoardController {

    @FXML
    private GridPane sudokuBoardGrid;
    @FXML
    private Button verifyButton;
    @FXML
    private Button loadButton;
    @FXML
    private Button saveButton;
    @FXML
    private Button loadDatabase;
    @FXML
    private Button saveDatabase;
    private final ResourceBundle bundle = ResourceBundle.getBundle("languages");

    private MessageBox popOutWindow = new MessageBox();
    private SudokuBoard sudokuBoard = new SudokuBoard();
    private SudokuBoard sudokuBoardCopy = new SudokuBoard();
    private BacktrackingSudokuSolver solver = new BacktrackingSudokuSolver();
    private Difficulty difficulty = new Difficulty();
    private static final Logger log = LogManager.getRootLogger();

    @FXML
    private void initialize() {
        verifyButton.setText(bundle.getString("verify"));
        loadButton.setText(bundle.getString("load"));
        saveButton.setText(bundle.getString("save"));
        loadDatabase.setText(bundle.getString("loadDB"));
        saveDatabase.setText(bundle.getString("saveDB"));
        solver.solve(sudokuBoard);
        difficulty.chooseLevel(sudokuBoard, ApplicationController.getLevel());
        sudokuBoardCopy = sudokuBoard.clone();
        fillGrid();
    }


    @FXML
    private void updateBoard() {
        ObservableList<Node> gridList = sudokuBoardGrid.getChildren();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                TextField textField = (TextField) gridList.get(i + 9 * j);
                if (NumberUtils.isParsable(textField.getText())) {
                    int valueToSet = Integer.parseInt(textField.getText());
                    sudokuBoard.set(j, i, valueToSet);
                } else {
                    sudokuBoard.set(j, i, 0);
                }
            }
        }
    }

    private void fillGrid() {
        if (sudokuBoardGrid.getChildren() != null) {
            sudokuBoardGrid.getChildren().clear();
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                TextField textField = new TextField();
                textField.setMinSize(50, 50);
                textField.setFont(Font.font(11));
                if (sudokuBoard.get(i, j) != 0) {
                    if(sudokuBoardCopy.get(i,j) != 0) {
                        textField.setDisable(true);
                    }
                    textField.setText(String.valueOf(sudokuBoard.get(i, j)));
                }
                textField.textProperty().addListener((observable, oldValue, newValue) -> {
                    if (textField.getText().matches("[1-9]") || textField.getText().matches("")) {
                        updateBoard();
                    } else {
                        Platform.runLater(textField::clear);
//                        popOutWindow.messageBox("Warning",
//                                "The inserted value must be an integer in range: (1-9)", Alert.AlertType.WARNING);
                    }
                });
                sudokuBoardGrid.add(textField, i, j);

            }
        }
    }

    @FXML
    private void saveGame(ActionEvent actionEvent) throws DaoClassException {
        SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
        Dao<SudokuBoard> file;
        file = factory.getFileDao("save");
        updateBoard();
        try {
            file.write(sudokuBoard);
            log.info("Game saved.");
        } catch (FileOperationException e) {
            popOutWindow.messageBox("Error",
                    "Couldn't save the game progress.", Alert.AlertType.WARNING);
            log.error("Saving failed.");
        }
    }


    @FXML
    private void loadGame(ActionEvent actionEvent) throws DaoClassException {
        try {
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
            Dao<SudokuBoard> file;
            file = factory.getFileDao("save");
            sudokuBoard = file.read();
            fillGrid();
            log.info("Game loaded.");
        } catch (FileOperationException e) {
            popOutWindow.messageBox("Error",
                    "Couldn't load the game progress.", Alert.AlertType.WARNING);
            log.error("Loading failed.");
        }

    }

    @FXML
    public void onActionButtonCheck(ActionEvent actionEvent) {
        boolean isSolved = true;
        for(int i = 0; i < 9; i++) {
            if (!sudokuBoard.getSudokuColumn(i).verify() || !sudokuBoard.getSudokuRow(i).verify()) {
                isSolved = false;
                break;
            }
        }
        for(int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                if(! sudokuBoard.getSudokuBox(3*i, 3*j).verify()) {
                    isSolved = false;
                    break;
                }
            }
        }
        if(isSolved){
            popOutWindow.messageBox("Win",
                    "You won.", Alert.AlertType.WARNING);
        } else {
            popOutWindow.messageBox("Fail",
                    "It's not the right solution.", Alert.AlertType.WARNING);
        }
    }

    @FXML
    public void onActionButtonLoadDatabase(ActionEvent actionEvent) {
        TextInputDialog td = new TextInputDialog("enter any text");
        td.setTitle("o7planning");
        td.setHeaderText("Enter the name of the board");
        td.setContentText("Name:");
        Optional<String> result = td.showAndWait();
        result.ifPresent(name -> {
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
            try {
                sudokuBoard = factory.getDatabaseDao(name).read();
                String names = name + "s";
                sudokuBoardCopy = factory.getDatabaseDao(names).read();
                fillGrid();
            } catch (FileOperationException | DatabaseException e) {
                popOutWindow.messageBox("Error",
                        "Can't load such board from the database.", Alert.AlertType.WARNING);
                log.error("Loading from database failed.");
            } catch (DaoClassException e) {
                e.printStackTrace();
            }
        });
    }

    @FXML
    public void onActionButtonSaveDatabase(ActionEvent actionEvent) {
        TextInputDialog td = new TextInputDialog("enter any text");
        td.setTitle("o7planning");
        td.setHeaderText("Enter the name of the board");
        td.setContentText("Name:");
        Optional<String> result = td.showAndWait();
        result.ifPresent(name -> {
            SudokuBoardDaoFactory factory = new SudokuBoardDaoFactory();
            try {
                factory.getDatabaseDao(name).write(sudokuBoard);
                String names = name + "s";
                factory.getDatabaseDao(names).write(sudokuBoardCopy);
            } catch (FileOperationException | DatabaseException e) {
                popOutWindow.messageBox("Error",
                        "Couldn't save the board to the database. Make sure that entry with such name isn't present.", Alert.AlertType.WARNING);
                log.error("Saving to database failed.");
            }
        });
    }

}
