package com.kukhotskovolets;

import javafx.geometry.Point2D;
import javafx.scene.shape.Line;
import java.util.HashSet;

import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

class DrawerModel {

    private final HashSet<Line> lines = new HashSet<>();
    private Line maxLine;
    private double maxLineLength;

    void clear() {
        lines.clear();
        maxLineLength = 0;
        maxLine = null;
    }

    Line getMaxLine() {
        return maxLine;
    }

    double getMaxLineLength() {
        return maxLineLength;
    }

    HashSet<Line> getLines() {
        return lines;
    }

    HashSet<Point2D> getPoints() {
        HashSet<Point2D> points = new HashSet<>(lines.size() + 1);
        lines.forEach(line -> {
            points.add(new Point2D(line.getStartX(), line.getStartY()));
            points.add(new Point2D(line.getEndX(), line.getEndY()));
        });
        return points;
    }

    void addLine(Line line) {
        lines.add(line);
        if (maxLine == null) {
            maxLine = new Line(line.getStartX(), line.getStartY(), line.getEndX(), line.getEndY());
            maxLineLength = sqrt(pow(line.getEndX() - line.getStartX(), 2) + pow(line.getEndY() - line.getStartY(), 2));
        }
        else {
            double length = sqrt(pow(line.getEndX() - line.getStartX(), 2) + pow(line.getEndY() - line.getStartY(), 2));
            if (Double.compare(length, maxLineLength) > 0) {
                maxLineLength = length;
                maxLine = line;
            }
        }
    }
}
