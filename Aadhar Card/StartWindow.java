package fileManagement;

import java.io.IOException;
import java.io.EOFException;
import javax.swing.*;
import java.awt.event.*;
import javax.security.auth.login.AppConfigurationEntry;

public class StartWindow implements ActionListener {
    
    AadharWriteService aws;
    AadharReadService ars;
    
    JFrame frame;
    JButton button1, button2;
    JLabel label;

    public static void main (String args[]) {
		
	StartWindow sw = new StartWindow();
	
    }
    
    public StartWindow() {
	
	frame = new JFrame("Aadhar Card Service");
	button1 = new JButton("Insert");
	button2 = new JButton("Search");
	label = new JLabel("Select the required service");
	
	button1.setBounds(50, 200, 100, 30);
	button1.addActionListener(this);
		
	button2.setBounds(250, 200, 100, 30);
	button2.addActionListener(this);
	
	label.setBounds(100, 100, 500, 30);
	
	frame.add(button1);
	frame.add(button2);
	frame.add(label);
	
	frame.setSize(800, 600);
	frame.setLayout(null);
	frame.setVisible(true);
	
    }

    @Override
    public void actionPerformed(ActionEvent e) {
	
	if(e.getSource() == button1) {
	    
	    aws = new AadharWriteService(this);
	    frame.setVisible(false);
	    
	} else if(e.getSource() == button2) {
	    
	    ars = new AadharReadService(this);
	    frame.setVisible(false);
	    
	}
	
    }
    
    public void backToStart () {
	
	frame.setVisible(true);
	
	aws = null;
	ars = null;
	
    }
    
}
