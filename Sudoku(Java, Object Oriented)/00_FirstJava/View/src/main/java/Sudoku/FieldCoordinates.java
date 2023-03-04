package Sudoku;

import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;
import org.apache.commons.lang3.builder.ToStringBuilder;

public class FieldCoordinates {

    private final int X;
    private final int Y;

    public FieldCoordinates(int X, int Y) {
        this.X = X;
        this.Y = Y;
    }

    public int getX() {
        return X;
    }

    public int getY() {
        return Y;
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("X", X)
                .append("Y", Y)
                .toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }

        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        FieldCoordinates that = (FieldCoordinates) o;

        return new EqualsBuilder()
                .append(X, that.X)
                .append(Y, that.Y)
                .isEquals();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37)
                .append(X)
                .append(Y)
                .toHashCode();
    }
}
