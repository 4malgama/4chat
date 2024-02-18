package amalgama.chat.gui;

import amalgama.chat.network.Server;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.logging.Logger;

public class MainWindow {
    private JFrame frame;
    private JPanel layout;

    public MainWindow() {
        frame = new JFrame("Amalgama Chat server-console");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(400, 300));
        initGui();
        frame.pack();
        frame.setVisible(true);
        frame.addWindowListener(new MainWindowListener());
        Logger.getGlobal().info("Window show is true.");
    }

    private void initGui() {
        layout = new JPanel();

        JButton btnStart = new JButton("Start");
        btnStart.setCursor(new Cursor(Cursor.HAND_CURSOR));
        btnStart.setFocusable(false);
        btnStart.addActionListener(e -> {
            new Thread(Server::start).start();
            btnStart.setEnabled(false);
        });

        layout.add(btnStart);

        frame.setContentPane(layout);
    }
}
