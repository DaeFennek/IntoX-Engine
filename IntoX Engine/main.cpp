#include "Engine.h"
#include "IntoXWindow.h"

int main(int argv, char** argc)
{
	ENGINE.Init();
	IntoXWindow window("IntoX Engine", 1024, 768);	
	window.Show();
	ENGINE.Run();
	ENGINE.Destroy();
	return 0;
}