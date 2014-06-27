#include "IntoXWindow.h"

int main(int argv, char** argc)
{
	IntoXWindow *window = new IntoXWindow("Hello World", 1280, 1024);
	window->Init();
	window->Show();
	
	if (window != NULL)
		delete window;
	//delete window;

	system("pause");
	return 0;

}