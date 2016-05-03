#include <exception>
#include "window\Window.h"

namespace engine
{
	Window* Window::instance = nullptr;

	Window::Window(const char* title, int width, int height) : width(width), height(height)
	{
		if (!glfwInit()) throw std::exception();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!window)
		{
			glfwTerminate();
			throw std::exception();
		}

		glfwMakeContextCurrent(window);

		glfwSetWindowSizeCallback(window, onWindowResize);
		glfwSetScrollCallback(window, onWindowMouseWheel);
		glfwSetMouseButtonCallback(window, onWindowMouseButton);
		glfwSetCursorPosCallback(window, onWindowMouseMove);
		glfwSetKeyCallback(window, onWindowKeyboard);
		glfwSetWindowFocusCallback(window, onWindowFocus);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::exception();

		instance = this;
	}

	void Window::onWindowMouseMove(GLFWwindow* window, double mouseX, double mouseY)
	{
		MouseEvent event(Event::MOUSE_MOVE);
		event.mouseX = (int)mouseX;
		event.mouseY = (int)mouseY;
		event.altKey = instance->isAltKeyDown();
		event.ctrlKey = instance->isCtrlKeyDown();
		event.shiftKey = instance->isShiftKeyDown();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			event.button = MouseButton::Left;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			event.button = MouseButton::Right;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			event.button = MouseButton::Middle;
		}
		else
		{
			event.button = MouseButton::None;
		}

		instance->dispatchEvent(event);
	}

	void Window::onWindowMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		MouseEvent event(Event::MOUSE_DOWN);
		event.mouseX = (int)mouseX;
		event.mouseY = (int)mouseY;
		event.altKey = instance->isAltKeyDown();
		event.ctrlKey = instance->isCtrlKeyDown();
		event.shiftKey = instance->isShiftKeyDown();

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			event.button = MouseButton::Left;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			event.button = MouseButton::Right;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			event.button = MouseButton::Middle;
		}
		else
		{
			event.button = MouseButton::None;
		}

		if (action == GLFW_PRESS)
		{
			instance->dispatchEvent(event);
		}
		else
		{
			event.type = Event::MOUSE_UP;
			instance->dispatchEvent(event);
		}
	}

	void Window::onWindowKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyboardEvent event(Event::KEY_DOWN);
		event.key = key;
		event.altKey = instance->isAltKeyDown();
		event.ctrlKey = instance->isCtrlKeyDown();
		event.shiftKey = instance->isShiftKeyDown();
		if (action != GLFW_PRESS) event.type = Event::KEY_UP;
		instance->dispatchEvent(event);
	}
}