import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static java.lang.System.exit;

public class MainFrame extends JFrame {

    private static final long serialVersionUID = 1L;
    
    public static void main(String argv[]) {
        JFrame frame = new MainFrame();

    }

    public MainFrame(){



        initPanel();
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.pack();
        this.setVisible(true);
    }

    private void initPanel(){

        TextArea textArea = new TextArea(20,20);
        JPanel jPanel = new JPanel();

        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

        JButton quit = new JButton("Quit");
        quit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                exit(0);
            }
        });

        jPanel.add(quit);
        add(textArea, BorderLayout.CENTER);
        add(jPanel, BorderLayout.SOUTH);

    }

}
