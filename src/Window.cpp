#include "Window.h"

void Window::createWindow(int width, int height, std::string_view title)
{
	srand(time(nullptr));

	if (!glfwInit()) throw std::runtime_error("Failed to init glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	if (!m_handle)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window\n");
	}

	glfwMakeContextCurrent(m_handle);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to create opengl context");
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, m_width, m_height);
}

void Window::destroyWindow() noexcept
{
	if (m_handle)
	{
		glfwDestroyWindow(m_handle);
		m_handle = nullptr;
	}
}

Window::Window(int width, int height, std::string_view title)
{
	m_width = width;
	m_height = height;
	m_title = title;

	createWindow(m_width, m_height, m_title);
}

Window::Window()
{
	createWindow(m_width, m_height, m_title);
}

Window::~Window() noexcept
{
	destroyWindow();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_handle);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_handle);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

void Window::clearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::clear(ClearCommand command) 
{
	GLenum finalCommand;

	if (command & ClearCommand::Color)
	{
		finalCommand |= GL_COLOR_BUFFER_BIT;
	}

	if (command & ClearCommand::Depth)
	{
		finalCommand |= GL_DEPTH_BUFFER_BIT;
	}

	glClear(finalCommand);
}