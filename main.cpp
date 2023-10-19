#include "main.h"

int main()
{
	Model editor;
	User_Interface start(&editor);
	editor.add_observer(&start);
	MyString default_file = "test.txt";
	start.read_text(default_file);
	start.create_window();
	start.go();
	return 0;
}