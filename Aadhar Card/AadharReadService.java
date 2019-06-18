package fileManagement;

import java.io.IOException;
import java.io.EOFException;
import javax.swing.*;
import java.awt.event.*;
import java.util.ArrayList;

public class AadharReadService implements ActionListener {
    
	StartWindow parentWindow;
	
    	JFrame frame;
	JButton button1, button2, button3, backButton,reset;
	JTextField[] textFields;
	JLabel[] labels;
	JLabel labelFileStatus;
	JTextArea textArea;
	
	AadharFile file;
	
	public AadharReadService(StartWindow parentWindow) {
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
		button1 = new JButton("Search ID");
		button2 = new JButton("Search by Middle Name");
		button3 = new JButton("Search by Last Name");
		backButton = new JButton("Cancel");
		reset = new JButton("Reset");
		textFields = new JTextField[3];
		textArea = new JTextArea();
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
		
		button1.setBounds(150, 150, 200, 30);
		button1.addActionListener(this);
		
		button2.setBounds(150, 250, 200, 30);
		button2.addActionListener(this);
		
		button3.setBounds(150, 350, 200, 30);
		button3.addActionListener(this);
		
		reset.setBounds(150,450,200,30);
		reset.addActionListener(this);
		
		backButton.setBounds(450, 500, 100, 30);
		backButton.addActionListener(this);
		
		for(int i=0; i<3; i++) {
			textFields[i] = new JTextField();
			textFields[i].setBounds(150, 100*(i+1), 300, 30);
			frame.add(textFields[i]);
		}
		
		textArea.setBounds(500, 150, 250, 300);
		frame.add(textArea);
		
		textFields[0].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(ke.getKeyChar() < '0' || ke.getKeyChar() > '9' || textFields[0].getText().length() >= 12)
					ke.consume();
			}
		});
	
		textFields[1].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(textFields[1].getText().length() > 30)
					ke.consume();
			}
		});
		
		textFields[2].addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent ke) {
				if(textFields[2].getText().length() > 30)
					ke.consume();
			}
		});
		
		
		for(int i=0; i<3; i++) {
			labels[i] = new JLabel();
			labels[i].setBounds(50, 100*(i+1), 100, 30);
			frame.add(labels[i]);
		}
		
		labels[3] = new JLabel();
		labels[3].setBounds(500, 100, 100, 30);
		frame.add(labels[3]);
		
		labels[0].setText("Aadhar ID");
		labels[1].setText("Middle Name");
		labels[2].setText("Last Name");
		labels[3].setText("Records");
		
		labelFileStatus.setBounds(50, 50, 400, 30);
		
		frame.add(button1);
		frame.add(button2);
		frame.add(button3);
		frame.add(backButton);
		frame.add(reset);
		frame.add(labelFileStatus);
		frame.add(testIndexButton);
		
		frame.setSize(800, 600);
		frame.setLayout(null);
		frame.setVisible(true);
		
	}
	
	public void actionPerformed (ActionEvent e) {
		
		try {
			if (e.getSource() == button1) {	
				if(textFields[0].getText().length() != 12) {
					setStatus("Invalid ID");
					return;
				}
				AadharRecord record  = file.readRecord(Long.parseLong(textFields[0].getText()));
				if(record.getAadharId() != 0) {	
					textArea.setText(record.getFirstName() + " " + record.getMiddleName() + " " + record.getLastName());
				} else {
					textArea.setText("RECORD NOT FOUND");
				}
				
				setStatus("Reading record");
			} else if(e.getSource() == button2) {
			    
			    ArrayList<AadharRecord> recList = file.searchByMiddleName(textFields[1].getText());
			    String output = "";
			    for(AadharRecord record : recList) {
				output = output + "\n" + record.getFirstName() + " " + record.getMiddleName() + " " + record.getLastName();
			    }
			    textArea.setText(output);
			    
			} else if(e.getSource() == button3) {
			    ArrayList<AadharRecord> recList = file.searchByLastName(textFields[2].getText());
			    String output = "";
			    for(AadharRecord record : recList) {
				output = output + "\n" + record.getFirstName() + " " + record.getMiddleName() + " " + record.getLastName();
			    }
			    textArea.setText(output);
			    
			} else if(e.getSource() == backButton) {
				
				frame.setVisible(false);
				this.parentWindow.backToStart();
			    
			} else if(e.getSource() == reset){
				textArea.setText("");
				textFields[0].setText("");
				textFields[1].setText("");
				textFields[2].setText("");
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
