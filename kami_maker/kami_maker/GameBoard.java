package kami_maker;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

import javax.swing.JPanel;

public class GameBoard extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4595789757308543556L;

	public static class Position {
		public int row;
		public int col;
	};
	
	public Color colors[][] = new Color[ MainUi.ROW_COUNT][ MainUi.COL_COUNT];
	
	private int pointX[][][] = new int[ MainUi.ROW_COUNT][ MainUi.COL_COUNT][ 3];
	private int pointY[][][] = new int[ MainUi.ROW_COUNT][ MainUi.COL_COUNT][ 3];
	
	/**
	 * Create the panel.
	 */
	public GameBoard() {
		for ( int row = 0; row < MainUi.ROW_COUNT; row ++)
			for ( int col = 0; col < MainUi.COL_COUNT; col ++)
				colors[ row][ col] = Color.WHITE;
		
		for ( int i = 0; i < MainUi.ROW_COUNT; i ++)
			for ( int j = 0; j < MainUi.COL_COUNT; j ++)
				if ( ( i + j) % 2 == 0) { // point right
					pointX[ i][ j][ 0] = pointX[ i][ j][ 2] = j * MainUi.TILE_WIDTH;
					pointX[ i][ j][ 1] = pointX[ i][ j][ 0] + MainUi.TILE_WIDTH;
					pointY[ i][ j][ 1] = i * MainUi.TILE_HEIGHT / 2;
					pointY[ i][ j][ 0] = pointY[ i][ j][ 1] - MainUi.TILE_HEIGHT / 2;
					pointY[ i][ j][ 2] = pointY[ i][ j][ 1] + MainUi.TILE_HEIGHT / 2;
				} else { // point left
					pointX[ i][ j][ 2] = j * MainUi.TILE_WIDTH;
					pointX[ i][ j][ 0] = pointX[ i][ j][ 1] = pointX[ i][ j][ 2] + MainUi.TILE_WIDTH;
					pointY[ i][ j][ 2] = i * MainUi.TILE_HEIGHT / 2;
					pointY[ i][ j][ 0] = pointY[ i][ j][ 2] - MainUi.TILE_HEIGHT / 2;
					pointY[ i][ j][ 1] = pointY[ i][ j][ 2] + MainUi.TILE_HEIGHT / 2;
				}
	}
	
	public void transferPosition( int x, int y, Position pos) {
		for ( int i = 0; i < MainUi.ROW_COUNT; i ++)
			for ( int j = 0; j < MainUi.COL_COUNT; j ++)
				if ( ( i + j) % 2 == 0) { // point right
					if ( x > pointX[ i][ j][ 0] && x < pointX[ i][ j][ 1]) {
						int dx = x - pointX[ i][ j][ 0];
						float dy = MainUi.TILE_HEIGHT / 2 * dx / (float)( MainUi.TILE_WIDTH);
						float upperY = pointY[ i][ j][ 0] + dy;
						float lowerY = pointY[ i][ j][ 2] - dy;
						if ( y > upperY && y < lowerY) {
							pos.row = i;
							pos.col = j;
							return;
						}
					}
				} else { // point left
					if ( x > pointX[ i][ j][ 2] && x < pointX[ i][ j][ 0]) {
						int dx = x - pointX[ i][ j][ 2];
						float dy = MainUi.TILE_HEIGHT / 2 * dx / (float)( MainUi.TILE_WIDTH);
						float upperY = pointY[ i][ j][ 2] - dy;
						float lowerY = pointY[ i][ j][ 2] + dy;
						if ( y > upperY && y < lowerY) {
							pos.row = i;
							pos.col = j;
							return;
						}
					}
				}
	}
	
	@Override
	public void paintComponent( final Graphics g) {
		super.paintComponent(g);
		
		if ( g != null) {
			Graphics2D g2d = (Graphics2D)g;
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			// draw tiles:
			for ( int i = 0; i < MainUi.ROW_COUNT; i ++)
				for ( int j = 0; j < MainUi.COL_COUNT; j ++) {
					g2d.setColor( colors[ i][ j]);
					g2d.fillPolygon( pointX[ i][ j], pointY[ i][ j], 3);
				}
			// draw lines:
			g2d.setColor( Color.BLACK);
			for ( int i = 0; i <= MainUi.COL_COUNT; i ++) {
				int x = MainUi.TILE_WIDTH * i;
				g2d.drawLine( x, 0, x, this.getHeight());
			}
			int slash_count = MainUi.ROW_COUNT / 2 + MainUi.COL_COUNT / 2;
			int width = MainUi.COL_COUNT * MainUi.TILE_WIDTH;
			for ( int i = 0; i < slash_count; i ++) {
				int x = MainUi.TILE_WIDTH * ( 1 + i * 2);
				int y = MainUi.TILE_HEIGHT * ( 1 + i * 2) / 2;
				g2d.drawLine( x, 0,	0, y);
				x = width - x;
				g2d.drawLine( x, 0, width, y);
			}
		}
	}

}
