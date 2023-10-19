#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4005)
#pragma warning(disable:4018)
#pragma warning(disable:4838)
#include <fstream>
#include <iostream>
#include <vector>
#include <curses.h>
#include "MyString.h"

class AdapterPDCurses
{
public:
	void init();
	void set_string(int x, int y, const MyString& text);
	void clear_window();
	void refresh_window();
	void move_cursor(int x, int y);
};

class Notify
{
public:
	virtual void create_text_vector() = 0;
};

class Model
{
public:
	void add_observer(Notify* obs);
	void delete_word(int index);
	void copy_word(int index);
	void delete_char(int index);
	void cut_string(int index, int size);
	void copy_string(int index, int size);
	void set_text(const MyString new_text);
	void set_buffer(char symbol);
	void save_text_return();
	void return_default_text();
	void save_in_file(const MyString& filename);
	int first_letter(int index);
	int paste(int index);
	int find_reverse(const MyString& substring, int pos) const;
	int search_str(const MyString& substr, int pos, int dir);
	MyString* get_text();
protected:
	MyString text;
	MyString save_text;
	MyString return_text;
	Notify* observer;
};

class User_Interface : public AdapterPDCurses, public Notify
{
public:
	User_Interface(Model* new_model);
	~User_Interface();
	void create_text_vector();
	void switch_mode();
	void create_window();
	void go();
	void display();
	void start_display();
	void regular_display(MyString* data);
	void display_rows();
	void display_mode_file();
	void right_cursor();
	void left_cursor();
	void up_cursor();
	void down_cursor();
	void set_cursor(int index);
	void begin_str();
	void end_str();
	void end_word();
	void begin_word();
	void begin_file();
	void end_file();
	void page_up();
	void page_down();
	void NG_button(int index);
	void search();
	void read_text(const MyString& filename);
	void set_working();
	void editor_mode(int symbol);
	void search_mode(int symbol);
	void command_mode(int symbol);
	void helper_mode(int symbol);
	void input_mode(int symbol);
	int cur_index();
private:
	std::vector<MyString> text_vector;
	int rows;
	int columns;
	int window_pos_col;
	int window_pos_row;
	int for_page_shift;
	int busy_rows;
	int first_row;
	int info_size;
	int page_shift;
	int mode;
	int direction;
	bool text_input;
	bool is_change;
	bool working;
	Model* model;
	MyString command;
	MyString command_filename;
	MyString save_filename;
	MyString input_buffer;
};