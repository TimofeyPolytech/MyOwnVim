#include "main.h"

void AdapterPDCurses::init()
{
	initscr();
	PDC_set_title("VIM");
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
}

void AdapterPDCurses::set_string(int x, int y, const MyString& text)
{
	mvaddstr(x, y, text.c_str());
}

void AdapterPDCurses::clear_window()
{
	clear();
}

void AdapterPDCurses::refresh_window()
{
	refresh();
}

void AdapterPDCurses::move_cursor(int x, int y)
{
	move(x, y);
}