package Sudoku;

import Sudoku.Exception.DatabaseException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;

public class JdbcSudokuBoardDao implements Dao<SudokuBoard>, AutoCloseable {
    private String databaseName;
    private String filename;
    private final ResourceBundle bundle = ResourceBundle.getBundle("Sudoku.resources.Languages");

    public JdbcSudokuBoardDao(String name) throws DatabaseException {
        databaseName = "sudokuproject";
        filename = name;
    }

    private Connection prepareConnection(String jdbcUrl) throws DatabaseException {
        Connection connection;
        try {
            connection = DriverManager.getConnection(jdbcUrl,
                    "root", "Xkx200.!");
        } catch (SQLException e) {
            throw new DatabaseException(bundle.getString("connectionError"));
        }
        return connection;
    }

    @Override
    public SudokuBoard read() throws DatabaseException {
        SudokuBoard board = new SudokuBoard();
        String jdbcUrl = "jdbc:mysql://"
                + "localhost:3306/" + databaseName + "?serverTimezone=UTC";
        Connection connection = prepareConnection(jdbcUrl);
        String receivedData;
        ResultSet resultSet;
        String select = "select tableName, fields from sudokuboards_table where tableName=?";

        try (PreparedStatement preparedStatement = connection.prepareStatement(select)) {
            preparedStatement.setString(1,filename);
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                receivedData = resultSet.getString(2);
            } else {
                receivedData = null;
            }
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    board.set(i, j, Character.getNumericValue(receivedData.charAt(i * 9 + j)));
                }
            }
        } catch (SQLException | NullPointerException e) {
            throw new DatabaseException(bundle.getString("loadDB"));
        }
        return board;
    }

    @Override
    public void write(SudokuBoard board) throws DatabaseException {
        String jdbcUrl = "jdbc:mysql://"
                + "localhost:3306/" + databaseName + "?serverTimezone=UTC";
        Connection connection = prepareConnection(jdbcUrl);
        StringBuilder boardValues = new StringBuilder("");
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                boardValues.append(String.valueOf(board.get(i, j)));
            }
        }
        String insert = "INSERT INTO `sudokuproject`.`"
                + "sudokuboards_table`(`tableName`,`fields`) VALUES (?,?);";
        try (PreparedStatement preparedStatement = connection.prepareStatement(insert)) {
            preparedStatement.setString(1,filename);
            preparedStatement.setString(2,boardValues.toString());
            preparedStatement.executeUpdate();
        } catch (SQLException | NullPointerException e) {
            throw new DatabaseException(bundle.getString("saveDB"));
        }
    }

    @Override
    public void close() throws Exception {

    }
}
