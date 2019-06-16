package com.brogrammers.java;

import java.io.IOException;
import java.io.EOFException;
import javax.swing.*;
import java.awt.event.*;

public class AadharWriteService implements ActionListener{
	
	StartWindow parentWindow;
    
	JFrame frame;
	JButton button1, backButton;
	JTextField[] textFields;
	JLabel[] labels;
	JLabel labelFileStatus;
	
	AadharFile file;
	
	public AadharWriteService(StartWindow parentWindow) {
		this.parentWindow = parentWindow;
	    
		setWindow();
		try {
			file = new AadharFile("AadharFile.dat");
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
		setStatus("File Opened : " + file.getFileName());
	}
	
	private void setWindow () {
		
		frame = new JFrame("Aadhar Card Service");
		button1 = new JButton("Insert");
		backButton = new JButton("Cancel");
		textFields = new JTextField[4];
		labels = new JLabel[4];
		labelFileStatus = new JLabel();

		JButton testIndexButton = new JButton("Test Index File");
		testIndexButton.setBounds(450, 500, 100, 30);
		testIndexButton.addActionListener(new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			try {
			    file.test();
			    file.testIndex(1);
			    file.testIndex(2);
			    
			} catch (IOException ioe) {
			    ioe.printStackTrace();
			}
		    }
		});
		
		button1.setBounds(50, 500, 100, 30);
		button1.addActionListener(this);
		
		backButton.setBounds(450, 500, 100, 30);
		backButton.addActionListener(this);
		
		for(int i=0; i<3; i++) {
			textFields[i] = new JTextField();
			textFields[i].setBounds(200, 50*(i+2), 400, 30);
			frame.add(textFields[i]);
		}
		
		textFields[3] = new JTextField();
		textFields[3].setBounds(200, 350, 400, 30);
		frame.add(textFields[3]);
		
		textFields[0].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(textFields[1].getText().length() > 30)
					ke.consume();
			}
		});
		
		textFields[1].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(textFields[2].getText().length() > 30)
					ke.consume();
			}
		});
		
		textFields[2].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(textFields[2].getText().length() > 30)
					ke.consume();
			}
		});
		
		textFields[3].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				ke.consume();
			}		
		});
		
		for(int i=0; i<3; i++) {
			labels[i] = new JLabel();
			labels[i].setBounds(50, 50*(i+2), 100, 30);
			frame.add(labels[i]);
		}
		
		labels[3] = new JLabel();
		labels[3].setBounds(50, 350, 100, 30);
		frame.add(labels[3]);
		
		labels[3].setText("Aadhar ID");
		labels[0].setText("First Name");
		labels[1].setText("Middle Name");
		labels[2].setText("Last Name");
		
		labelFileStatus.setBounds(50, 50, 400, 30);
		
		frame.add(button1);
		frame.add(backButton);
		frame.add(labelFileStatus);
		frame.add(testIndexButton);
		
		frame.setSize(800, 600);
		frame.setLayout(null);
		frame.setVisible(true);
		
	}
	
	public void actionPerformed (ActionEvent e) {
		
		try {
			if(e.getSource() == button1) {
			    
				long id = Hashing.getId(textFields[0].getText() +  textFields[1].getText() + textFields[2].getText());
			    
				textFields[3].setText(String.valueOf(id));
				
				if(textFields[0].getText().length() == 0 || textFields[1].getText().length() == 0 || textFields[2].getText().length() == 0) {
					setStatus("All fields must be filled");
					return;
				}
				
				AadharRecord record = new AadharRecord(id, textFields[1].getText(), textFields[2].getText(), textFields[3].getText());
		
				file.insertRecord(record);
		
				System.out.println(record.toString());
		
				setStatus("Inserted record : " + record.getAadharId());
				
			} else if(e.getSource() == backButton) {
				
				frame.setVisible(false);
				this.parentWindow.backToStart();
			    
			}
		} catch (EOFException eofe) {
			setStatus("Record does not exist");
                        eofe.printStackTrace();
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
		
	}
	
	public void setStatus(String status) {
		labelFileStatus.setText(status);
	}

}