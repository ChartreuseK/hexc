/*
 * 
 * 
 * 
 */
#include "hexc.hpp"

#include <curses.h>
#include <iostream>

#include <unistd.h>


int main(int argc, char **argv)
{
	initscr();
	cbreak();    // Character at a time input
	noecho();    // No automatic echo
	keypad(stdscr, TRUE);  // Capture special keys
	curs_set(0); // Hide cursor
	
	if (has_colors() == FALSE) {
		endwin();
		std::cerr << "Sorry this program currently requires color terminal support" << std::endl;
		return 2;
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLUE);
	init_pair(8, COLOR_WHITE, COLOR_GREEN);
	
	WINDOW *wInfo, *wStatus, *wLegend, *wAddr, *wHex, *wAscii;	
	
	wInfo    = newwin(1, getmaxx(stdscr), 0, 0);
	wStatus  = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
	wLegend  = newwin(1, getmaxx(stdscr), 1, 0);
	wAddr    = newwin(getmaxy(stdscr)-3, 8+1, 2, 0);
	wHex     = newwin(getmaxy(stdscr)-3, (16*3)+2, 2, 8+1);
	wAscii   = newwin(getmaxy(stdscr)-3, (16*1)+1, 2, 8+1+(16*3)+3);
	
	wbkgd(wInfo, COLOR_PAIR(1) | A_BOLD);
	wbkgd(wStatus, COLOR_PAIR(3) | A_BOLD);
	wbkgd(wLegend, COLOR_PAIR(2) | A_BOLD);
	wbkgd(wAddr, COLOR_PAIR(4) | A_BOLD);
	wbkgd(wHex, COLOR_PAIR(5) | A_BOLD);
	wbkgd(wAscii, COLOR_PAIR(6) | A_BOLD);
	
	
	mvwprintw(wInfo, 0,0, "Test File | ");
	mvwprintw(wStatus,0,0,"Cursor(%08X)", 5*16+9);
	mvwprintw(wLegend,0,0," Offset    0  1  2  3  4  5  6  7   8  9  a  b  c  d  e  f   ASCII");
	
	for(int i = 0; i < getmaxy(stdscr)-3; i++)
		mvwprintw(wAddr,i,0,"%08X:",i*16);
		
	for(int i = 0; i < getmaxy(stdscr)-3; i++)
		for(int j = 0; j < 16; j++)
		{
			if(i == 5 && j == 9)
			{
				wattron(wHex, COLOR_PAIR(7) | A_BOLD);
				wattron(wAscii, COLOR_PAIR(8) | A_BOLD);
			}
			else
			{
				wattron(wHex, COLOR_PAIR(5) | A_BOLD);
				wattron(wAscii, COLOR_PAIR(6) | A_BOLD);
			}
			mvwprintw(wHex,i, (j> 7)?(j*3 + 2):(j*3 + 1), "%02hhX", j+(16*i));
			mvwprintw(wAscii,i,j, "%c", isprint((j+(16*i))%256)  ? j+(16*i) : '.');
		}
	refresh();
	wrefresh(wInfo);
	wrefresh(wStatus);
	wrefresh(wLegend);
	wrefresh(wAddr);
	wrefresh(wHex);
	wrefresh(wAscii);
	
	getch();
	//sleep(10);
	
	endwin();    // Restore terminal
	return 0;
}
