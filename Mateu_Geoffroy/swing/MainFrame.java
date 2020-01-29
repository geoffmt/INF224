import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import static java.lang.System.exit;

public class MainFrame extends JFrame {

    private JButton displayButton ;
    private JButton playButton;
    private JButton quitButton ;
    private JTextArea textArea = new JTextArea(35,130);


    private static Client client;

    private static final long serialVersionUID = 1L;

    public static void main(String argv[]) {

        try {
            client = new Client("localhost", Client.DEFAULT_PORT);
        } catch (IOException e) {
            e.printStackTrace();
        }

        new MainFrame();
    }

/**
         * Conteneur principal
         * 
         */
    public MainFrame(){

        initPanel();
        initMenuBar();
        initToolBar();

        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setTitle("Main Window");
        this.pack();
        this.setVisible(true);
    }

/**
         * Conteneur de la zone de texte et des boutons
         * 
         */
    private void initPanel(){

        JPanel buttonsPanel = new JPanel();

        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        displayButton = new JButton(new DisplayAction("Display",this));
        playButton = new JButton(new PlayAction("Play",this));
        quitButton = new JButton(new QuitAction("Quit"));


        buttonsPanel.add(displayButton);
        buttonsPanel.add(playButton);
        buttonsPanel.add(quitButton);

        textArea.setBackground(Color.WHITE);
        add(scrollPane, BorderLayout.CENTER);
        add(buttonsPanel, BorderLayout.SOUTH);

    }

/**
         * Conteneur des items de la barre des tâches
         * 
         */
    private void initMenuBar(){
        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Menu");

        JMenuItem displayItem = new JMenuItem(new DisplayAction("Display",this));
        JMenuItem playItem = new JMenuItem(new PlayAction("Play",this));
        JMenuItem quitItem = new JMenuItem(new QuitAction("Quit"));

        menu.add(displayItem);
        menu.add(playItem);
        menu.add(quitItem);

        menuBar.add(menu);
        setJMenuBar(menuBar);
    }

/**
         * Initie la bar des tâches
         * 
         */
    private void initToolBar(){
        JToolBar toolBar = new JToolBar();
        toolBar.add(new DisplayAction("Display",this));
        toolBar.add(new PlayAction("Play",this));
        toolBar.add(new QuitAction("Quit"));
        add(toolBar, BorderLayout.NORTH);
    }

/**
         * Action effectuée lorsque l'on appuie sur display
         * 
         */
    class DisplayAction extends AbstractAction {
        JFrame parentFrame;
        public DisplayAction(String text, JFrame frame) {
            super(text);
            parentFrame = frame;
        }
        @Override
        public void actionPerformed(ActionEvent e){
            String name = JOptionPane.showInputDialog(parentFrame, "What object do you want to display informations ?", null);
            if (name != null){
                String message = "search " + name;
                String response = client.send(message);
                textArea.append(response + '\n');
            
            }
            else{
                return;
            }
        }
    }

/**
         * Action effectuée lorsque l'on appuie sur play
         * 
         */
    class PlayAction extends AbstractAction {
        Frame parentFrame;
        public PlayAction(String text, Frame frame) {
            super(text);
            parentFrame = frame;
        }

        @Override
        public void actionPerformed(ActionEvent e){
            String name = JOptionPane.showInputDialog(parentFrame, "What object do you want to play ?", null);
            if (name != null){
                String message = "play " + name;
                String response = client.send(message);
                textArea.append(response + '\n');
            }
            else{
                return;
            }
        }
    }

/**
         * Action effectuée lorsque l'on appuie sur quit
         * 
         */
    class QuitAction extends AbstractAction{

        public QuitAction(String text) {
            super(text);
        }
        @Override
        public void actionPerformed(ActionEvent e) {
            System.exit(0);
        }
    }

}
