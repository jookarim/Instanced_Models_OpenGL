#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cstdint>

using byte = uint8_t;

enum class ClearCommand : byte
{
	None = 1 << 0, //0001
	Color = 1 << 1, //0010
	Depth = 1 << 2, //0100
};

inline ClearCommand operator|(ClearCommand a, ClearCommand b)
{
	return static_cast<ClearCommand>(
		static_cast<byte>(a) | static_cast<byte>(b)
		);
}

inline bool operator&(ClearCommand a, ClearCommand b)
{
	return (static_cast<byte>(a) & static_cast<byte>(b)) != 0;
}

class Window
{
private:
	GLFWwindow* m_handle = nullptr;
	int m_width = 800, m_height = 600;
	std::string m_title = "";
private:
	void createWindow(int width = 800, int height = 600, std::string_view title = "Window");
	void destroyWindow() noexcept;
public:
	Window();
	Window(int width = 800, int height = 600, std::string_view title = "Window");

	~Window() noexcept;
	
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string_view getTitle() const { return m_title; }

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) noexcept = delete; 
	Window& operator=(Window&&) noexcept = delete;

	bool shouldClose() const;

	void swapBuffers() const;

	void pollEvents() const;

	void clear(ClearCommand clearCommand);
	void clearColor(float r, float g, float b, float a) const;
};