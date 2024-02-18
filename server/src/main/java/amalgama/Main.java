package amalgama;

import amalgama.chat.gui.MainWindow;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {
    public static void main(String[] args) throws IOException {
        Logger.getLogger("org.hibernate").setLevel(Level.OFF);
        ServerLoader.loadDatabase();
        MainWindow w = new MainWindow();
    }
}