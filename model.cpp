#include "main.h"

void Model::add_observer(Notify* obs)
{
	observer = obs;
}

int Model::first_letter(int index)
{
	save_text.clear();
	MyString space(" ");
	MyString slash("\n");
	int first = find_reverse(space, index);
	int prob_first = find_reverse(slash, index);
	if (prob_first > first)
		first = prob_first;
	first++;
	return first;
}

void Model::delete_word(int index)
{
	int first = first_letter(index);
	copy_word(index);
	int space = text.find(" ", index);
	int slash = text.find("\n", index);
	if (slash > space && space != -1)
		text.erase(first, save_text.size() + 1);
	else
		text.erase(first, save_text.size());
	observer->create_text_vector();
	save_text.clear();
}

void Model::copy_word(int index)
{
	int first = first_letter(index);
	int end_ch1 = text.find(" ", index + 1);
	int end_ch2 = text.find("\n", index + 1);
	if (end_ch1 < end_ch2)
		save_text = text.substr(first, end_ch1 - first);
	else if (end_ch1 > end_ch2 && end_ch2 != -1)
		save_text = text.substr(first, end_ch2 - first);
	else if (end_ch2 == -1 && end_ch1 != -1)
		save_text = text.substr(first, end_ch1 - first);
	else
		save_text = text.substr(first, text.size() - first);
}

int Model::paste(int index)
{
	text.insert(index, save_text.c_str());
	int size = save_text.size();
	save_text.clear();
	observer->create_text_vector();
	save_text.clear();
	return size;
}

void Model::cut_string(int index, int size)
{
	copy_string(index, size);
	if (text[index + size] == '\n')
		size++;
	text.erase(index, size);
	observer->create_text_vector();
}

void Model::copy_string(int index, int size)
{
	save_text.clear();
	save_text = text.substr(index, size);
	observer->create_text_vector();
}

void Model::set_text(const MyString new_text)
{
	text = new_text;
	observer->create_text_vector();
}

void Model::delete_char(int index)
{
	text.erase(index, 1);
	observer->create_text_vector();
}

void Model::save_text_return()
{
	return_text = *get_text();
}

void Model::set_buffer(char symbol)
{
	save_text = symbol;
}

int Model::find_reverse(const MyString& substring, int pos) const
{
	int prev_idx = -1;
	int idx = text.find(substring.c_str());
	while (idx + substring.size() - 1 < pos && idx != -1)
	{
		prev_idx = idx;
		idx = text.find(substring.c_str(), prev_idx + 1);
	}
	return prev_idx;
}

int Model::search_str(const MyString& substr, int pos, int dir)
{
	if (dir == 2)
		return find_reverse(substr, pos);
	else
		return text.find(substr.c_str(), pos);
}

MyString* Model::get_text()
{
	return &text;
}

void Model::return_default_text()
{
	set_text(return_text);
	return_text.clear();
}

void Model::save_in_file(const MyString& filename)
{
	MyString* text = get_text();
	std::ofstream file_save(filename.c_str());
	if (file_save.is_open())
		file_save << text->c_str();
}