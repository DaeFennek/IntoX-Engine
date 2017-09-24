#include "IntoXWindow.h"

int main(int argv, char** argc)
{
	IntoXWindow window("IntoX Engine", 1024, 768);
	window.Init();
	window.Show();		
	return 0;
}