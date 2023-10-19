#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <initializer_list>
#include "MyString.h"

class MyString
{
private:
	char* str = NULL;
	unsigned int len = 0;
	unsigned int capacity_len = 0;
public:
	MyString();
	MyString(const MyString& s);
	MyString(const char* input_string);
	MyString(const std::string& input_string);
	MyString(const std::initializer_list<char>& list);
	MyString(int count, char letter);
	MyString(const char* input_string, int count);
	~MyString();
	void constructor_work(const char* s);
	friend std::ostream& operator<<(std::ostream& os, const MyString& c);
	friend std::istream& operator>>(std::istream& is, MyString& c);
	MyString concatenate_strings(const char* s)const;
	MyString operator+=(const MyString& s);
	MyString operator+=(const char* s);
	MyString operator+=(const std::string& s);
	MyString operator+(const char* s)const;
	MyString operator+(const std::string& s)const;
	MyString operator+(const MyString& s)const;
	void equally(const char* s);
	MyString plus_equally(const char* s);
	const MyString& operator=(const MyString&);
	const MyString& operator=(const char* s);
	const MyString& operator=(std::string& s);
	const MyString& operator=(char c);
	char operator [](int index)const;
	int compare(const char* s)const;
	bool operator<(const char* s)const;
	bool operator<(const std::string& s)const;
	bool operator<(MyString& s)const;
	bool operator<=(const char* s)const;
	bool operator<=(const std::string& s)const;
	bool operator<=(MyString& s)const;
	bool operator>(const char* s)const;
	bool operator>(const std::string& s)const;
	bool operator>(MyString& s)const;
	bool operator>=(const char* s)const;
	bool operator>=(const std::string& s)const;
	bool operator>=(MyString& s)const;
	bool operator==(const char* s)const;
	bool operator==(const std::string& s)const;
	bool operator==(MyString& s)const;
	bool operator!=(const char* s)const;
	bool operator!=(const std::string& s)const;
	bool operator!=(MyString& s)const;
	char* c_str()const;
	char* data()const;
	unsigned int length()const;
	unsigned int size()const;
	bool empty()const;
	unsigned int capacity()const;
	void shrink_to_fit();
	void insert(int a, int b, char c);
	void insert(int a, const char* s);
	void insert(int a, const char* s, int b);
	void insert(int a, const std::string s);
	void insert(int a, const std::string s, int b);
	void insert_big_cap(int count, int a, int b);
	void insert_with_str(int count, int a, int size, const char* s);
	void erase(int a, int b);
	void clear();
	void append(int count, char c);
	void append(const char* s);
	void append(const char* s, int a, int b);
	void append(const std::string s);
	void append(const std::string s, int a, int b);
	void replace(int a, int b, const char* s);
	void replace(int a, int b, const std::string s);
	MyString substr(int index)const;
	MyString substr(int index, int count)const;
	int find(const char* s)const;
	int find(const char* s, int index)const;
	int find(const std::string s)const;
	int find(const std::string s, int index)const;
};
