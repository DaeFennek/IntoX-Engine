#include "IntoXWindow.h"

int main(int argv, char** argc)
{
	IntoXWindow *window = new IntoXWindow("IntoX Engine", 1024, 768);
	window->Init();
	window->Show();
	
	if (window != NULL)
		delete window;

	system("pause");
	return 0;

}