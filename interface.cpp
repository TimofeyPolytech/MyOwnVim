#include "main.h"
#define BACKSPACE 8
#define ENTER     10
#define ESC       27
std::vector <MyString> names_mode
{
	"EDITING",
	"COMMAND",
	"INPUT",
	"SEARCH",
	"HELPER"
};

User_Interface::User_Interface(Model* new_model)
{
	init();
	model = new_model;
	rows = 29;
	columns = 120;
	window_pos_col = 0;
	window_pos_row = 0;
	for_page_shift = 0;
	busy_rows = 0;
	first_row = 0;
	info_size = 0;
	page_shift = 10;
	mode = 0;
	direction = 0;
	text_input = false;
	is_change = false;
	working = true;
}

User_Interface::~User_Interface()
{
	clear_window();
	refresh_window();
}

void User_Interface::switch_mode()
{
	int symbol = getch();
	if (symbol == -1)
		return;
	switch (mode)
	{
	case 0:
		editor_mode(symbol);
		break;
	case 1:
		command_mode(symbol);
		break;
	case 2:
		input_mode(symbol);
		break;
	case 3:
		search_mode(symbol);
		break;
	case 4:
		helper_mode(symbol);
	default:
		return;
	}
}

void User_Interface::create_window()
{
	if (window_pos_col >= columns)
	{
		window_pos_col = columns - 1;
		window_pos_col = columns - 1;
	}
	create_text_vector();
}

void User_Interface::go()
{
	while (working == true)
	{
		switch_mode();
	}
}

int User_Interface::cur_index()
{
	int index = 0;
	int counter = 0;
	if (text_vector.size() != 0)
	{
		for (int i = 0; i < for_page_shift; i++)
			counter += (text_vector[i].size() + 1);
		index = counter + window_pos_col;
	}
	return index;
}

void User_Interface::start_display()
{
	MyString hello("Hello, world!");
	set_string(rows / 2, columns / 2 - hello.size() / 2, hello);
	move_cursor(0, 0);
}

void User_Interface::regular_display(MyString* text)
{
	MyString substring;
	int i = 0;
	int counter = 0;
	if (first_row != 0)
	{
		int count = 0;
		while (count != first_row)
		{
			counter += (text_vector[count].size() + 1);
			count++;
		}
	}
	for (unsigned int j = first_row; i < rows && j < busy_rows; i++, j++)
	{
		int len = text_vector[j].size();
		substring = text->substr(counter, len);
		counter += (len + 1);
		set_string(i, 0, substring);
	}
}

void User_Interface::display()
{
	clear_window();
	MyString* text = model->get_text();
	if (text->size() != 0)
		regular_display(text);
	else
		start_display();
	info_size = 0;
	display_mode_file();
	display_rows();
	move_cursor(window_pos_row, window_pos_col);
	refresh_window();
}

void User_Interface::display_rows()
{
	MyString cursor;
	if (busy_rows != 0)
		cursor.append(std::to_string(for_page_shift + 1));
	else
		cursor.append(std::to_string(for_page_shift));
	cursor.append("/");
	cursor.append(std::to_string(busy_rows));
	set_string(rows, columns - cursor.size() - 1, cursor);
}

void User_Interface::display_mode_file()
{
	info_size = names_mode[mode].size();
	set_string(rows, 0, names_mode[mode]);
	info_size++;
	if (mode == 4)
	{
		MyString helper("help.txt");
		info_size += helper.size();
		set_string(rows, info_size - helper.size(), helper);
	}
	else
	{
		info_size += save_filename.size();
		set_string(rows, info_size - save_filename.size(), save_filename);
	}
}

void User_Interface::right_cursor()
{
	if (text_vector[for_page_shift].size() > window_pos_col)
		window_pos_col++;
}

void User_Interface::left_cursor()
{
	if (window_pos_col > 0)
		window_pos_col--;
}

void User_Interface::up_cursor()
{
	if (window_pos_row != 0)
	{
		if (window_pos_row < page_shift && first_row != 0)
		{
			first_row--;
			for_page_shift--;
		}
		else
		{
			window_pos_row--;
			for_page_shift--;
		}
		if (text_vector.size() < window_pos_row)
			window_pos_col = 0;
		else if (text_vector[for_page_shift].size() < window_pos_col)
			window_pos_col = text_vector[window_pos_row].size();
	}
}

void User_Interface::down_cursor()
{
	if (busy_rows != 0 && window_pos_row < rows - 1 && for_page_shift < busy_rows - 1)
	{
		if (window_pos_row + page_shift >= rows && first_row + rows < busy_rows)
		{
			first_row++;
			for_page_shift++;
			display();
			return;
		}
		else
		{
			window_pos_row++;
			for_page_shift++;
		}
		if (text_vector.size() <= for_page_shift)
			window_pos_col = 0;
		else if (text_vector[for_page_shift].size() < window_pos_col)
			window_pos_col = text_vector[for_page_shift].size();
	}
}

void User_Interface::set_cursor(int index)
{
	int count = 0;
	int counter = text_vector[count].size();
	int saver = counter;
	for (count; index > counter; count++)
	{
		saver = counter;
		counter += (text_vector[count + 1].size() + 1);
	}
	if (index != saver && index >= saver)
		window_pos_col = index - (saver + 1);
	else
		window_pos_col = index;
	window_pos_row = count;
	for_page_shift = count;
	if (count > rows / 2)
	{
		first_row = count - rows / 2;
		window_pos_row = rows / 2;
	}
}

void User_Interface::begin_str()
{
	window_pos_col = 0;
}

void User_Interface::end_str()
{
	window_pos_col = text_vector[for_page_shift].size();
}

void User_Interface::end_word()
{
	int j = window_pos_col;
	if (text_vector[for_page_shift][j + 1] == ' ')
		j += 2;
	int count = text_vector[for_page_shift].find(" ", j);
	if (count == -1)
		count = text_vector[for_page_shift].size();
	count--;
	window_pos_col = count;
}

void User_Interface::begin_word()
{
	int count = window_pos_col;
	if (text_vector[for_page_shift][count - 1] == ' ')
		count -= 2;
	while (count > 0 && text_vector[for_page_shift][count] != ' ')
		count--;
	if (text_vector[for_page_shift][count] == ' ')
		count++;
	window_pos_col = count;
}

void User_Interface::begin_file()
{
	first_row = 0;
	window_pos_col = 0;
	window_pos_row = 0;
	for_page_shift = 0;
}

void User_Interface::end_file()
{
	window_pos_col = text_vector[busy_rows - 1].size();
	if (busy_rows - 1 >= rows)
	{
		window_pos_row = rows - 1;
		first_row = busy_rows - 1 - window_pos_row;
	}
	else
		window_pos_row = busy_rows - 1;
	for_page_shift = busy_rows - 1;
}

void User_Interface::page_up()
{
	if (busy_rows < rows)
		return;
	window_pos_row = 0;
	if (for_page_shift < rows)
		first_row = 0;
	else
		first_row = for_page_shift - rows;
	for_page_shift = first_row;
}

void User_Interface::page_down()
{
	if (busy_rows <= rows)
		return;
	window_pos_row = 0;
	if (for_page_shift + rows > busy_rows - rows)
		first_row = busy_rows - rows;
	else
		first_row = for_page_shift + rows;
	for_page_shift = first_row;
}

void User_Interface::NG_button(int index)
{
	if (index >= busy_rows)
		return;
	int pos_x = window_pos_col;
	if (index > window_pos_row)
	{
		for (int i = window_pos_row; i < index; i++)
			down_cursor();
	}
	else
	{
		for (int i = window_pos_row; i > index; i--)
			up_cursor();
	}
}

void User_Interface::search()
{
	int index = model->search_str(input_buffer, cur_index(), direction);
	if (index != -1)
		set_cursor(index);
	else
		begin_file();
}

void User_Interface::create_text_vector()
{
	MyString* text = model->get_text();
	int cur_pos = 0;
	text_vector.clear();
	busy_rows = 0;
	int size = text->size();
	if (size != 0)
	{
		while (size > cur_pos)
		{
			int end_str = text->find("\n", cur_pos);
			if (end_str == -1)
				end_str = size;
			if (end_str - cur_pos >= columns)
				end_str = cur_pos + 119;
			MyString new_str = text->substr(cur_pos, end_str - cur_pos);
			text_vector.push_back(new_str);
			busy_rows++;
			cur_pos += (new_str.size() + 1);
			if (size == cur_pos && text->operator[](cur_pos - 1) == '\n')
			{
				MyString new_str("\0");
				text_vector.push_back(new_str);
				busy_rows++;
			}
		}
	}
	display();
}

void User_Interface::read_text(const MyString& filename)
{
	if (filename != "help.txt")
		save_filename = filename;
	std::ifstream text_file(filename.c_str());
	if (!text_file.is_open())
		return;
	MyString new_text;
	text_file >> new_text;
	text_file.close();
	model->set_text(new_text);
}

void User_Interface::set_working()
{
	working = false;
}

void User_Interface::editor_mode(int symbol)
{
	switch (symbol)
	{
	case KEY_RIGHT:
	{
		right_cursor();
		display();
		break;
	}
	case KEY_LEFT:
	{
		left_cursor();
		display();
		break;
	}
	case KEY_UP:
	{
		up_cursor();
		display();
		break;
	}
	case KEY_DOWN:
	{
		down_cursor();
		display();
		break;
	}
	case '0':
	{
		begin_str();
		display();
		break;
	}
	case '^':
	{
		begin_str();
		display();
		break;
	}
	case '$':
	{
		end_str();
		display();
		break;
	}
	case 'w':
	{
		if (input_buffer[input_buffer.size() - 2] == 'd' && input_buffer[input_buffer.size() - 1] == 'i')
		{
			input_buffer.clear();
			is_change = true;
			model->delete_word(cur_index());
		}
		else if (input_buffer[input_buffer.size() - 1] == 'y')
		{
			input_buffer.clear();
			model->copy_word(cur_index());
		}
		else
		{
			end_word();
			display();
		}
		break;
	}
	case 'b':
	{
		begin_word();
		display();
		break;
	}
	case 'g':
	{
		if (input_buffer[input_buffer.size() - 1] == 'g')
		{
			input_buffer.clear();
			begin_file();
			display();
		}
		else
			input_buffer.append("g");
		break;
	}
	case 'G':
	{
		if (input_buffer.size() > 0)
		{
			int numeral = atoi(input_buffer.c_str());
			input_buffer.clear();
			NG_button(numeral - 1);
			display();
		}
		else
		{
			end_file();
			display();
		}
		break;
	}
	case KEY_PPAGE:
	{
		page_up();
		display();
		break;
	}
	case KEY_NPAGE:
	{
		page_down();
		display();
		break;
	}
	case 'x':
	{
		model->delete_char(cur_index());
		is_change = true;
		break;
	}
	case 'd':
	{
		if (input_buffer[input_buffer.size() - 1] == 'd')
		{
			input_buffer.clear();
			int counter = 0;
			for (int i = 0; i < for_page_shift; i++)
				counter += (text_vector[i].size() + 1);
			int len = text_vector[for_page_shift].size();
			begin_str();
			display();
			model->cut_string(counter, len);
			is_change = true;
		}
		else
			input_buffer.append("d");
		break;
	}
	case 'y':
	{
		int counter = 0;
		for (int i = 0; i < for_page_shift; i++)
			counter += (text_vector[i].size() + 1);
		int len = text_vector[for_page_shift].size();
		model->copy_string(counter, len);
		input_buffer.append("y");
		break;
	}
	case 'p':
	{
		int res = model->paste(cur_index());
		set_cursor(res + cur_index());
		display();
		is_change = true;
		break;
	}
	case '/':
	{
		search_mode('/');
		break;
	}
	case '?':
	{
		search_mode('?');
		break;
	}
	case 'i':
	{
		if (input_buffer[input_buffer.size() - 1] == 'd')
			input_buffer.append("i");
		else
		{
			mode = 2;
			display();
		}
		break;
	}
	case 'I':
	{
		mode = 2;
		begin_str();
		display();
		break;
	}
	case 'A':
	{
		mode = 2;
		end_str();
		display();
		break;
	}
	case 'S':
	{
		mode = 2;
		int counter = 0;
		for (int i = 0; i < for_page_shift; i++)
			counter += (text_vector[i].size() + 1);
		int len = text_vector[for_page_shift].size();
		begin_str();
		display();
		model->cut_string(counter, len);
		is_change = true;
		break;
	}
	case 'r':
	{
		input_buffer.append("r");
		mode = 2;
		model->delete_char(cur_index());
		display();
		is_change = true;
		break;
	}
	case ':':
	{
		mode = 1;
		display();
		text_input = false;
		break;
	}
	default:
	{
		if (symbol >= '0' && symbol <= '9')
		{
			char numeral[2] = { symbol,0 };
			input_buffer.append(numeral);
		}
	}
	}
}

void User_Interface::input_mode(int symbol)
{
	switch (symbol)
	{
	case BACKSPACE:
	{
		model->delete_char(cur_index());
		left_cursor();
		is_change = true;
		break;
	}
	case ENTER:
	{
		model->set_buffer('\n');
		int res = model->paste(cur_index());
		set_cursor(res + cur_index());
		begin_str();
		display();
		is_change = true;
		break;
	}
	case ESC:
	{
		mode = 0;
		input_buffer.clear();
		display();
		break;
	}
	default:
	{
		model->set_buffer(symbol);
		int res = model->paste(cur_index());
		set_cursor(res + cur_index());
		display();
		is_change = true;
		if (input_buffer == "r")
		{
			mode = 0;
			display();
			input_buffer.clear();
		}
	}
	}
}

void User_Interface::search_mode(int symbol)
{
	char new_str[] = { symbol, 0 };
	switch (symbol)
	{
	case '/':
	{
		mode = 3;
		direction = 1;
		text_input = true;
		display();
		break;
	}
	case '?':
	{
		mode = 3;
		direction = 2;
		text_input = true;
		display();
		break;
	}
	case ENTER:
	{
		text_input = false;
		search();
		display();
		break;
	}
	case BACKSPACE:
	{
		if (input_buffer.size())
			input_buffer.erase(input_buffer.size() - 1, 1);
		text_input = true;
		display();
		break;
	}
	case ESC:
	{
		mode = 0;
		input_buffer.clear();
		display();
		break;
	}
	case 'n':
	{
		if (text_input == false)
		{
			search();
			display();
		}
		else
			input_buffer.append(new_str);
		break;
	}
	case 'N':
	{
		if (text_input == false)
		{
			if (direction == 1)
				direction = 2;
			else
				direction = 1;
			search();
			display();
		}
		else
			input_buffer.append(new_str);
		break;
	}
	default:
	{
		if (text_input == true)
			input_buffer.append(new_str);
	}
	}
}

void User_Interface::helper_mode(int symbol)
{
	switch (symbol)
	{
	case ESC:
	{
		mode = 0;
		first_row = 0;
		model->return_default_text();
		begin_file();
		display();
		create_text_vector();
		break;
	}
	case KEY_RIGHT:
	{
		right_cursor();
		display();
		break;
	}
	case KEY_LEFT:
	{
		left_cursor();
		display();
		break;
	}
	case KEY_UP:
	{
		up_cursor();
		display();
		break;
	}
	case KEY_DOWN:
	{
		down_cursor();
		display();
		break;
	}
	case '0':
	{
		begin_str();
		display();
		break;
	}
	case '^':
	{
		begin_str();
		display();
		break;
	}
	case '$':
	{
		end_str();
		display();
		break;
	}
	case 'w':
	{
		end_word();
		display();
		break;
	}
	case 'b':
	{
		begin_word();
		display();
		break;
	}
	case 'g':
	{
		if (input_buffer[input_buffer.size() - 1] == 'g')
		{
			input_buffer.clear();
			begin_file();
			display();
		}
		else
			input_buffer.append("g");
		break;
	}
	case 'G':
	{
		if (input_buffer.size() > 0)
		{
			int numeral = atoi(input_buffer.c_str());
			input_buffer.clear();
			NG_button(numeral - 1);
			display();
		}
		else
		{
			end_file();
			display();
		}
		break;
	}
	case KEY_PPAGE:
	{
		page_up();
		display();
		break;
	}
	case KEY_NPAGE:
	{
		page_down();
		display();
		break;
	}
	default:
	{
		if (symbol >= '0' && symbol <= '9')
		{
			char numeral[2] = { symbol,0 };
			input_buffer.append(numeral);
		}
	}
	}
}

void User_Interface::command_mode(int symbol)
{
	switch (symbol)
	{
	case 'h':
	{
		input_buffer.append("h");
		break;
	}
	case BACKSPACE:
	{
		if (input_buffer.size())
			input_buffer.erase(input_buffer.size() - 1, 1);
		break;
	}
	case ESC:
	{
		mode = 0;
		input_buffer.clear();
		display();
		break;
	}
	case ENTER:
	{
		text_input = false;
		if (input_buffer == "h")
		{
			mode = 4;
			display();
			model->save_text_return();
			MyString helper_file = "help.txt";
			read_text(helper_file);
			break;
		}
		int index = input_buffer.find(" ");
		if (index == -1)
			command = input_buffer;
		else
		{
			command = input_buffer.substr(0, index);
			command_filename = input_buffer.substr(index + 1, input_buffer.size() - index - 1);
		}
		if (command == "o")
			read_text(command_filename);
		else if (command == "x" || command == "wq!")
		{
			model->save_in_file(save_filename);
			set_working();
		}
		else if (command == "w")
			model->save_in_file(command_filename);
		else if (command == "q")
		{
			if (is_change == true)
				return;
			else
				set_working();
		}
		else if (command == "q!")
			set_working();
		else if (command[command.size() - 1] >= '0' && command[command.size() - 1] <= '9')
		{
			int numeral = atoi(command.c_str());
			NG_button(numeral - 1);
			display();
		}
		break;
	}
	default:
	{
		if (text_input == false)
		{
			text_input = true;
			display();
		}
		char new_str[] = { symbol, 0 };
		input_buffer.append(new_str);
	}
	}
	display();
}