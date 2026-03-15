#include <iostream>
#include "Window.h"

int main()
{
	Window window(1270, 800, "Window");

	while (!window.shouldClose())
	{
		window.pollEvents();

		window.clear(ClearCommand::Color | ClearCommand::Depth);
		window.clearColor(1.f, 0.f, 1.f, 1.f);

		window.swapBuffers();
	}
}