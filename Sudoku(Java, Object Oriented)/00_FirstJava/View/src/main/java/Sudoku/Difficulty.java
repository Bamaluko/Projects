package Sudoku;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class Difficulty {

    public int base = 5;
    public int[] multiplier = {1, 2, 3};

    private Random rand = new Random();
    private Set<FieldCoordinates> randomPositions = new HashSet<>();

    private void fillRandomPositionsList(int capacity) {
        for (int i = 0; i < capacity; i++) {
            boolean isAdded = false;

            while (!isAdded) {
                int X = rand.nextInt(9);
                int Y = rand.nextInt(9);
                isAdded = randomPositions.add(new FieldCoordinates(X, Y));
            }
        }
    }

    public SudokuBoard chooseLevel(SudokuBoard sudokuBoard, String level) {

        switch (level) {

            case "Latwy":
            case "Easy": {
                fillRandomPositionsList(base * multiplier[0]);
                break;
            }
            case "Sredni":
            case "Intermediate": {
                fillRandomPositionsList(base * multiplier[1]);
                break;
            }
            case "Trudny":
            case "Hard": {
                fillRandomPositionsList(base * multiplier[2]);
                break;
            }
            default: {
                fillRandomPositionsList(base * multiplier[0]);
            }
        }

        for (FieldCoordinates coordinates : randomPositions) {
            sudokuBoard.set(coordinates.getX(), coordinates.getY(), 0);
        }

        return sudokuBoard;
    }
}
