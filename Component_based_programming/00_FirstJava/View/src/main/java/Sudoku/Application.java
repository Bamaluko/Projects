package Sudoku;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.apache.log4j.Logger;
import org.apache.log4j.LogManager;

import java.io.IOException;

public class Application extends javafx.application.Application {
    private static final Logger log = LogManager.getRootLogger();
    @Override
    public void start(Stage stage) throws IOException {
        log.info("Starting the application.");
        FXMLLoader fxmlLoader = new FXMLLoader(Application.class.getResource("application-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 655, 226);
        stage.setTitle("Setup");
        stage.setScene(scene);
        stage.setResizable(false);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}