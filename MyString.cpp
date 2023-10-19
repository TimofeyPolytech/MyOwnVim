#include "MyString.h"
#pragma warning(disable:4018)
#pragma warning(disable:6385)
#pragma warning(disable:6386)

MyString::MyString()
{
	str = new char[1]();
	str[0] = 0;
	len = 0;
	capacity_len = 1;
}

void MyString::constructor_work(const char* s)
{
	capacity_len = len + 1;
	str = new char[capacity_len]();
	for (int i = 0; i < len; i++)
		str[i] = s[i];
	str[len] = '\0';
}

MyString::MyString(const MyString& s)
{
	len = s.size();
	constructor_work(s.str);
}

MyString::MyString(const char* s)
{
	len = strlen(s);
	constructor_work(s);
}

MyString::MyString(const std::string& s)
{
	len = s.size();
	constructor_work(s.c_str());
}

MyString::MyString(const std::initializer_list<char>& list)
{
	len = list.size();
	capacity_len = len + 1;
	str = new char[capacity_len]();
	int i = 0;
	for (char element : list)
	{
		str[i] = element;
		i++;
	}
	str[i] = '\0';
}

MyString::MyString(const char* s, int count)
{
	len = count;
	capacity_len = count + 1;
	str = new char[capacity_len]();
	for (int i = 0; i < count; i++)
		str[i] = s[i];
	str[count] = '\0';
}

MyString::MyString(int count, char letter)
{
	len = count;
	capacity_len = count + 1;
	str = new char[capacity_len]();
	for (int i = 0; i < count; i++)
		str[i] = letter;
	str[count] = '\0';
}

MyString::~MyString()
{
	delete[] str;
	len = 0;
	capacity_len = 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& s)
{
	return os << s.str;
}

std::istream& operator>>(std::istream& is, MyString& s)
{
	while (!is.eof())
	{
		char symbol = 0;
		char str[2] = { symbol, 0 };
		is >> std::noskipws >> symbol;
		str[0] = symbol;
		s.append(str);
	}
	return is;
}

MyString MyString::concatenate_strings(const char* s)const
{
	MyString for_ret(str);
	for_ret.append(s);
	return for_ret;
}

MyString MyString::operator+(const char* s)const
{
	return concatenate_strings(s);
}

MyString MyString::operator+(const std::string& s)const
{
	return concatenate_strings(s.c_str());
}

MyString MyString::operator+(const MyString& s)const
{
	return concatenate_strings(s.c_str());
}

MyString MyString::plus_equally(const char* s)
{
	this->append(s);
	return *this;
}

MyString MyString::operator+=(const MyString& s)
{
	return plus_equally(s.str);
}

MyString MyString::operator+=(const char* s)
{
	return plus_equally(s);
}

MyString MyString::operator+=(const std::string& s)
{
	return plus_equally(s.c_str());
}

void MyString::equally(const char* s)
{
	if (str != s)
	{
		int new_len = strlen(s);
		if (capacity_len < new_len + 1)
		{
			delete[] str;
			len = new_len;
			capacity_len = len + 1;
			str = new char[capacity_len]();
			for (int i = 0; i < len; i++)
				str[i] = s[i];
			str[len] = '\0';
		}
		else
		{
			clear();
			for (len = 0; len < new_len; len++)
				str[len] = s[len];
			str[len] = '\0';
		}
	}
}

const MyString& MyString::operator=(const MyString& s)
{
	equally(s.str);
	return *this;
}

const MyString& MyString::operator=(const char* s)
{
	equally(s);
	return *this;
}

const MyString& MyString::operator=(std::string& s)
{
	equally(s.c_str());
	return *this;
}

const MyString& MyString::operator=(char c)
{
	delete[] str;
	str = new char[2]();
	str[0] = c;
	str[1] = '\0';
	len = 1;
	capacity_len = 2;
	return *this;
}

char MyString::operator[](int index)const
{
	if (index < len)
		return str[index];
	else
		return 0;
}

int MyString::compare(const char* s)const
{
	int position = 0;
	int for_return = 0;
	for (position = 0; str[position] == s[position] && s[position] != 0 && str[position] != 0; position++);
	if (str[position] < s[position])
		for_return = 1;
	if (str[position] == s[position])
		for_return = 0;
	if (str[position] > s[position])
		for_return = -1;
	return for_return;
}

bool MyString::operator<(const char* s)const
{
	if (compare(s) == 1)
		return true;
	else
		return false;
}

bool MyString::operator<(const std::string& s)const
{
	return operator<(s.c_str());
}

bool MyString::operator<(MyString& s)const
{
	return operator<(s.str);
}

bool MyString::operator<=(const char* s)const
{
	if (compare(s) >= 0)
		return true;
	else
		return false;
}

bool MyString::operator<=(const std::string& s)const
{
	return operator<=(s.c_str());
}

bool MyString::operator<=(MyString& s)const
{
	return operator<=(s.str);
}

bool MyString::operator>(const char* s)const
{
	if (compare(s) == -1)
		return true;
	else
		return false;
}

bool MyString::operator>(const std::string& s)const
{
	return operator>(s.c_str());
}

bool MyString::operator>(MyString& s)const
{
	return operator>(s.str);
}

bool MyString::operator>=(const char* s)const
{
	if (compare(s) <= 0)
		return true;
	else
		return false;
}

bool MyString::operator>=(const std::string& s)const
{
	return operator>=(s.c_str());
}

bool MyString::operator>=(MyString& s)const
{
	return operator>=(s.str);
}

bool MyString::operator==(const char* s)const
{
	if (compare(s) == 0)
		return true;
	else
		return false;
}

bool MyString::operator==(const std::string& s)const
{
	return operator==(s.c_str());
}

bool MyString::operator==(MyString& s)const
{
	return operator==(s.str);
}

bool MyString::operator!=(const char* s)const
{
	if (compare(s) != 0)
		return true;
	else
		return false;
}

bool MyString::operator!=(const std::string& s)const
{
	return operator!=(s.c_str());
}

bool MyString::operator!=(MyString& s)const
{
	return operator!=(s.str);
}

char* MyString::c_str()const
{
	return str;
}

char* MyString::data()const
{
	return str;
}

unsigned int MyString::length()const
{
	return len;
}

unsigned int MyString::size()const
{
	return len;
}

bool MyString::empty()const
{
	if (len)
		return false;
	else
		return true;
}

unsigned int MyString::capacity()const
{
	return capacity_len;
}

void MyString::shrink_to_fit()
{
	if (capacity_len <= len + 1)
		return;
	capacity_len = len + 1;
	char* buf = new char[capacity_len]();
	for (int i = 0; i < len; i++)
		buf[i] = str[i];
	buf[len] = '\0';
	str = buf;
}

void MyString::erase(int a, int b)
{
	if ((a < 0) || (b < 0) || (a > len))
		return;
	int i = a + b;
	for (i; i < len; i++)
	{
		str[a] = str[a + b];
		a++;
	}
	len -= b;
	str[len] = '\0';
}

void MyString::clear()
{
	for (int i = 0; i < capacity_len; i++)
		str[i] = '\0';
	len = 0;
}

void MyString::insert_big_cap(int count, int a, int b)
{
	len = count;
	int end = count - 1;
	int contin = a + b;
	int memory = a;
	MyString str_copy(str);
	for (contin; contin <= end; contin++)
	{
		str[contin] = str_copy[a];
		a++;
	}
}

void MyString::insert(int a, int b, char c)
{
	if ((a > len) || (a < 0))
		return;
	int count = len + b;
	if (capacity_len > count + 1)
	{
		insert_big_cap(count, a, b);
		for (int i = 0; i < b; i++)
		{
			str[a] = c;
			a++;
		}
		return;
	}
	capacity_len = len + b + 1;
	char* buf = new char[capacity_len]();
	for (int i = 0; i < a; i++)
		buf[i] = str[i];
	int counter = a + b;
	for (int i = a; i < counter; i++)
		buf[i] = c;
	for (int i = a + b; i < count; i++)
		buf[i] = str[i - b];
	buf[count] = '\0';
	delete[] str;
	len = count;
	str = buf;
}

void MyString::insert_with_str(int count, int a, int size, const char* s)
{
	capacity_len = count + 1;
	char* buf = new char[capacity_len]();
	for (int i = 0; i < a; i++)
		buf[i] = str[i];
	int counter = a + size;
	for (int j = a, i = 0; j < counter; j++, i++)
		buf[j] = s[i];
	for (int i = counter; i < count; i++)
		buf[i] = str[i - size];
	buf[count] = '\0';
	delete[] str;
	len = count;
	str = buf;
}

void MyString::insert(int a, const char* s)
{
	if ((a > len) || (a < 0))
		return;
	int size = strlen(s);
	int count = len + size;
	if (capacity_len > count + 1)
	{
		insert_big_cap(count, a, size);
		for (int i = 0; i < size; i++)
		{
			str[a] = s[i];
			a++;
		}
		return;
	}
	insert_with_str(count, a, size, s);
}

void MyString::insert(int a, const char* s, int b)
{
	if ((a > len) || (a < 0))
		return;
	int count = len + b;
	if (capacity_len > count + 1)
	{
		insert_big_cap(count, a, b);
		for (int i = 0; i < b; i++)
		{
			str[a] = s[i];
			a++;
		}
		return;
	}
	insert_with_str(count, a, b, s);
}

void MyString::insert(int a, const std::string s)
{
	insert(a, s.c_str());
}

void MyString::insert(int a, const std::string s, int b)
{
	insert(a, s.c_str(), b);
}

void MyString::append(int count, char c)
{
	this->insert(len, count, c);
}

void MyString::append(const char* s)
{
	this->insert(len, s);
}

void MyString::append(std::string s)
{
	this->insert(len, s);
}

void MyString::append(const char* s, int a, int b)
{
	if (a >= strlen(s) || a + b > strlen(s))
		return;
	this->insert(len, s + a, b);
}

void MyString::append(std::string s, int a, int b)
{
	this->append(s.c_str(), a, b);
}

void MyString::replace(int a, int b, const char* s)
{
	this->erase(a, b);
	this->insert(a, s);
}

void MyString::replace(int a, int b, std::string s)
{
	this->replace(a, b, s.c_str());
}

MyString MyString::substr(int index)const
{
	if ((index > len) || (index < 0))
		return NULL;
	int count = len - index;
	return substr(index, count);
}

MyString MyString::substr(int index, int count)const
{
	if ((count < 0) || (index > len) || (count > len + 1 - index) || (index < 0))
		return NULL;
	char* buf = new char[count + 1];
	for (int i = 0; i < count; i++)
		buf[i] = str[index + i];
	buf[count] = '\0';
	MyString for_ret(buf);
	delete[] buf;
	return for_ret;
}

int MyString::find(const char* s)const
{
	return find(s, 0);
}

int MyString::find(const char* s, int index)const
{
	if (index < 0)
		return -1;
	unsigned int i = 0;
	for (i = index; i < len; i++)
	{
		if (str[i] == s[0])
		{
			int i_gen = i, i_sub = 0;
			for (i_gen, i_sub; s[i_sub] && str[i_gen] && str[i_gen] == s[i_sub]; i_gen++, i_sub++);
			if (!s[i_sub])
				return i;
		}
	}
	return -1;
}

int MyString::find(const std::string s)const
{
	return find(s.c_str());
}

int MyString::find(const std::string s, int index)const
{
	return find(s.c_str(), index);
}