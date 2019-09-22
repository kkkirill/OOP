package com.kukhotskovolets;

import javafx.application.Application;

public class Main {

    public static void main(String[] args) {
        try {
            Application.launch(Drawer.class, args);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
