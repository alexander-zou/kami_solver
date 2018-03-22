package kami_maker;

import java.awt.Color;
import java.awt.Component;
import java.awt.EventQueue;

import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JTextArea;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

public class MainUi extends JFrame implements KeyListener, ActionListener, MouseListener, DocumentListener  {

	/**
	 * 
	 */
	private static final long serialVersionUID = -4814580048100474908L;
	
	public static final int TILE_WIDTH = 40;
	public static final int TILE_HEIGHT = 40;
	public static final int ROW_COUNT = 29;
	public static final int COL_COUNT = 10;
	
	public static final int COLOR_COUNT = 8;
	
	private JPanel contentPane;
	private GameBoard boardPanel;
	private JTextArea outputText;
	private JTextField colorText[] = new JTextField[ COLOR_COUNT];
	private JRadioButton colorRadio[] = new JRadioButton[ COLOR_COUNT];
	private int currRadio = -1;

	/**
	 * Create the frame.
	 */
	public MainUi() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		boardPanel = new GameBoard();
		boardPanel.setBounds(6, 6, TILE_WIDTH * COL_COUNT, ( ROW_COUNT - 1) / 2 * TILE_HEIGHT);
		boardPanel.addMouseListener( this);
		contentPane.add(boardPanel);
		
		outputText = new JTextArea();
		outputText.setLineWrap(true);
		outputText.setFont( new Font("STIXGeneral", outputText.getFont().getStyle(), 12));
		outputText.setText( "");
		outputText.setBounds( boardPanel.getBounds().width + 12, 6, 160, boardPanel.getHeight());
		outputText.getDocument().addDocumentListener( this);
		contentPane.add(outputText);
		
		for ( int i = 0; i < COLOR_COUNT; i ++) {
			colorRadio[ i] = new JRadioButton( "");
			colorRadio[ i].setBounds( outputText.getWidth() + outputText.getX(), 30 * i, 28, 26);
			colorRadio[ i].addActionListener( this);
			contentPane.add( colorRadio[ i]);
			
			colorText[ i] = new JTextField();
			colorText[ i].setBounds( colorRadio[ i].getWidth() + colorRadio[ i].getX(), colorRadio[ i].getY(), 50, colorRadio[ i].getHeight());
			colorText[ i].setText( "*");
			colorText[ i].setColumns( 1);
			colorText[ i].setBackground( Color.WHITE);
			colorText[ i].setHorizontalAlignment( JTextField.CENTER);
			colorText[ i].setEditable( false);
			colorText[ i].addKeyListener( this);
			colorText[ i].addMouseListener( this);
			contentPane.add( colorText[ i]);
		}
		
		setBounds(100, 100, colorText[ 0].getX() + colorText[ 0].getWidth() + 12, outputText.getHeight() + outputText.getY() + 100);
	}
	
	private void setColors() {
		String str = outputText.getText();
		int idx = 0, row = 0, col = 0;
		while ( idx < str.length() && row < ROW_COUNT) {
			int matched_color = -1;
			for ( int i = 0; i < COLOR_COUNT; i ++) {
				if ( str.toUpperCase().charAt( idx) == colorText[ i].getText().charAt( 0)) {
					matched_color = i;
					break;
				}
			}
			if ( matched_color >= 0) {
				boardPanel.colors[ row][ col] = colorText[ matched_color].getBackground();
				if ( ++ col >= COL_COUNT) {
					col = 0;
					row ++;
				}
			}
			idx ++;
		}
		while ( row < ROW_COUNT) {
			boardPanel.colors[ row][ col] = Color.WHITE;
			if ( ++ col >= COL_COUNT) {
				col = 0;
				row ++;
			}
		}
		boardPanel.repaint( 200);
	}
	
	private void updateTile( int change_row, int change_col, int to_which) {
		//System.out.println( "update: " + change_row + "," + change_col + "   :" + to_which);
		char text[][] = new char[ ROW_COUNT][ COL_COUNT];
		int idx = 0, row = 0, col = 0;
		String oriText = outputText.getText();
		while ( idx < oriText.length() && row < ROW_COUNT) {
			int matched_color = -1;
			for ( int i = 0; i < COLOR_COUNT; i ++) {
				if ( oriText.toUpperCase().charAt( idx) == colorText[ i].getText().charAt( 0)) {
					matched_color = i;
					break;
				}
			}
			if ( matched_color >= 0) {
				text[ row][ col] = colorText[ matched_color].getText().charAt( 0);
				if ( ++ col >= COL_COUNT) {
					col = 0;
					row ++;
				}
			}
			idx ++;
		}
		while ( row < ROW_COUNT) {
			text[ row][ col] = '*';
			if ( ++ col >= COL_COUNT) {
				col = 0;
				row ++;
			}
		}
		text[ change_row][ change_col] = colorText[ to_which].getText().charAt( 0);
		String newText = new String();
		for ( int i = 0; i < ROW_COUNT; i ++) {
			for ( int j = 0; j < COL_COUNT; j ++)
				newText += text[ i][ j];
			newText += '\n';
		}
		outputText.setText( newText);
	}
	
	private void onTextChanged() {
		setColors();
	}
	
	@Override
	public void keyPressed(KeyEvent e) {
		Component comp = e.getComponent();
		for ( int i = 0; i < COLOR_COUNT; i ++) {
			if ( colorText[ i].equals( comp)) {
				char ch = e.getKeyChar();
				switch ( ch) {
				case '~': case '!': case '@': case '#': case '$': case '%':
				case '^': case '&': case '*': case '(': case ')': case '-':
				case '=': case '+': case '|': case '\\': case '/': case '?':
				case '[': case ']': case '{': case '}': case '<': case '>':
				case ',': case '.':
					break;
				default:
					if ( ch >= '0' && ch <= '9')
						break;
					else if ( ch >= 'a' && ch <= 'z') {
						ch -= ' ';
						break;
					} else if ( ch >= 'A' && ch <= 'Z')
						break;
					else
						return;
				}
				for ( int j = 0; j < COLOR_COUNT; j ++) {
					if ( ch == colorText[ j].getText().charAt( 0))
						return;
				}
				char old = colorText[ i].getText().charAt( 0);
				if ( old != '*') {
					String str = outputText.getText();
					outputText.setText( str.toUpperCase().replace( old, ch));
				}
				colorText[ i].setText( String.valueOf( ch));
				if ( ch == '*') {
					colorText[ i].setForeground( Color.BLACK);
					colorText[ i].setBackground( Color.WHITE);
				}
				setColors();
				return;
			}
		} // for which text field
	}

	@Override
	public void keyTyped(KeyEvent e) {}
	
	@Override
	public void keyReleased(KeyEvent e) {}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object comp = e.getSource();
		for ( int i = 0; i < COLOR_COUNT; i ++)
			if ( colorRadio[ i].equals( comp)) {
				if ( currRadio >= 0 && currRadio < COLOR_COUNT)
					colorRadio[ currRadio].setSelected( false);
				colorRadio[ i].setSelected( true);
				currRadio = i;
				return;
			}
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		if ( e.getButton() == MouseEvent.BUTTON1 && e.getClickCount() == 2) {
			for ( int i = 0; i < COLOR_COUNT; i ++)
				if ( colorText[ i].equals( e.getComponent())) {
					if ( currRadio >= 0)
						colorRadio[ currRadio].setSelected( false);
					colorRadio[ i].setSelected( true);
					currRadio = i;
					colorText[ i].select( 0, 0);
					if ( colorText[ i].getText().equals( "*"))
						return;
					Color newColor = JColorChooser.showDialog( this, "Pick Color", colorText[ i].getBackground());
					if ( newColor == null)
						return;
					colorText[ i].setBackground( newColor);
					int brightness = (int) (newColor.getRed() * 0.3 + newColor.getGreen() * 0.59 + newColor.getBlue() * 0.11);
					if ( brightness > 120)
						colorText[ i].setForeground( Color.BLACK);
					else
						colorText[ i].setForeground( Color.WHITE);
					setColors();
					return;
				}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {}

	@Override
	public void mouseReleased(MouseEvent e) {
		if ( e.getButton() == MouseEvent.BUTTON1) {
			if ( e.getComponent().equals( boardPanel) && currRadio >= 0) {
				GameBoard.Position position = new GameBoard.Position();
				boardPanel.transferPosition( e.getX(), e.getY(), position);
				if ( position.row >= 0)
					updateTile( position.row, position.col, currRadio);
			}
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {}

	@Override
	public void mouseExited(MouseEvent e) {}
	
	@Override
	public void insertUpdate(DocumentEvent e) {
		onTextChanged();
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		onTextChanged();
	}

	@Override
	public void changedUpdate(DocumentEvent e) {
		onTextChanged();
	}
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainUi frame = new MainUi();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}


}
