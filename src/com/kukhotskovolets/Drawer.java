package com.kukhotskovolets;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.shape.Line;
import javafx.stage.Stage;
import java.io.IOException;
import java.util.Random;

import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

public class Drawer extends Application {

    private Stage primaryStage;

    private DrawerModel model;

    private Random random;

    @Override
    public void start(Stage primaryStage) {
        random = new Random();
        this.model = new DrawerModel();
        this.primaryStage = primaryStage;
        initRootLayout();
    }

    private void initRootLayout(){
        try {
            primaryStage.setWidth(700);
            primaryStage.setHeight(600);
            primaryStage.setTitle("Drawer");
            primaryStage.setResizable(false);
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("scene.fxml"));
            Scene scene = new Scene(loader.load());
            primaryStage.setScene(scene);
            DrawerController drawerController = loader.getController();
            drawerController.setMainApp(this);
            drawerController.initModel(model);

            primaryStage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    void generateRandomLines(int pointsAmount) {
        int startX = random.nextInt(510), endX;
        int startY = random.nextInt(555), endY;
        for (int i = 0; i < pointsAmount - 1; i++) {
            endX = random.nextInt(510);
            endY = random.nextInt(555);
            model.addLine(new Line(startX, startY, endX, endY));
            startX = endX;
            startY = endY;
        }
    }

    double getTotalLength() {
        double total = 0;
        for (Line line: model.getLines()) {
            total += sqrt(pow(line.getEndX() - line.getStartX(), 2) + pow(line.getEndY() - line.getStartY(), 2));
        }
        return total;
    }

    Line maxLine() {
        return  model.getMaxLine();
    }

    double maxLineLength() {
        return model.getMaxLineLength();
    }
}
