package com.kukhotskovolets;

import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.*;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;

import java.net.URL;
import java.util.ResourceBundle;

public class DrawerController implements Initializable {


    public Spinner<Integer> pointsSpinner;
    public Label pointsSpinnerLabel;
    public Label outputWindowLabel;
    public TextArea outputWindow;
    public Button drawButton;
    public SplitPane splitPane;
    public Pane canvasPane;
    public Pane controlsPane;
    public Canvas canvas;
    public Button clearButton;
    public Rectangle coordinatePlane;
    private GraphicsContext graphicsContext;

    private DrawerModel drawerModel;
    private Drawer mainApp;

    private final int CANVASWIDTH = 516; //505
    private final int CANVASHEIGHT = 562; //552
    private final int step = 50;

    void initModel(DrawerModel drawerModel) {
        this.drawerModel = drawerModel;
    }

    void setMainApp(Drawer mainApp) {
        this.mainApp = mainApp;
    }

    public int getCANVASHEIGHT() {
        return CANVASHEIGHT;
    }

    public int getCANVASWIDTH() {
        return CANVASWIDTH;
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        graphicsContext = canvas.getGraphicsContext2D();
        graphicsContext.setStroke(Color.rgb(20, 20, 20));
        graphicsContext.setFill(Color.rgb(248, 249, 219));
        graphicsContext.setLineWidth(2);
        splitPane.setDividerPositions(0.75f, 0.25f);
        pointsSpinner.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(2, 30, 2));
        canvas.setHeight(CANVASHEIGHT);
        canvas.setWidth(CANVASWIDTH);
        coordinatePlane.setHeight(CANVASHEIGHT);
        coordinatePlane.setWidth(CANVASWIDTH);
        drawRectangleLines();
        drawButton.setOnAction(event -> {
            clear();
            mainApp.generateRandomLines(pointsSpinner.getValue());
            draw();
        });
        clearButton.setOnAction(event -> clear());
    }

    private void drawRectangleLines() {
        double linewidth = graphicsContext.getLineWidth();
        graphicsContext.setLineWidth(0.8);
        for (int i = 0; i < CANVASHEIGHT; i+=step) {
            graphicsContext.strokeLine(0, i, 7, i);
            if (i % step == 0 && i != 0) {
                graphicsContext.strokeText(Integer.toString(i), 9, i + 5, 15);
            }
        }
        for (int j = 0; j < CANVASWIDTH; j+=step) {
            graphicsContext.strokeLine(j, 0, j, 7);
            if (j % step == 0 && j != 0) {
                graphicsContext.strokeText(Integer.toString(j), j - 7, 20, 15);
            }
        }
        graphicsContext.setLineWidth(linewidth);
    }

    private void clear() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
        drawerModel.clear();
        outputWindow.clear();
        graphicsContext.clearRect(0, 0, CANVASWIDTH, CANVASHEIGHT);
        drawRectangleLines();
    }

    private void draw() {
        drawerModel.getPoints().forEach(point2D -> System.out.println(point2D.getX() + " " + point2D.getY()));
        drawerModel.getLines().forEach((line2D) -> {
            graphicsContext.strokeOval(line2D.getStartX(), line2D.getStartY(), 2, 2);
            graphicsContext.strokeOval(line2D.getEndX(), line2D.getEndY(), 2, 2);
            graphicsContext.strokeLine(line2D.getStartX(), line2D.getStartY(), line2D.getEndX(), line2D.getEndY());
        });
        showResults();
    }

    private void showResults() {
        double totalLength, maxLength;
        totalLength = mainApp.getTotalLength();
        maxLength = mainApp.maxLineLength();
        Line line = mainApp.maxLine();
        String output = String.format("Max line cords:\n(%.0f, %.0f) (%.0f, %.0f)\nMax length:\n%f\nTotal length:\n%f\n",
                line.getStartX(), line.getStartY(), line.getEndX(), line.getEndY(), maxLength, totalLength);
        outputWindow.setText(output);
        System.out.println("\n" + output);
    }
}
