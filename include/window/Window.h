#pragma once

#include <Windows.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "EventTarget.h"

namespace engine
{
	class Window : public EventTarget
	{
	public:
		Window(const char* title = "OpenGL App", int width = 800, int height = 500);

		virtual ~Window()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		bool Window::active() const
		{
			return !glfwWindowShouldClose(window);
		}

		void Window::refresh()
		{
			Sleep(33);
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		bool Window::isAltKeyDown() const
		{
			return glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS
				|| glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;
		}

		bool Window::isCtrlKeyDown() const
		{
			return glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS
				|| glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
		}

		bool Window::isShiftKeyDown() const
		{
			return glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
				|| glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
		}

	public:
		int width;
		int height;

	private:
		GLFWwindow* window;
		static Window* instance;

		static void onWindowResize(GLFWwindow* window, int width, int height)
		{
			instance->width = width;
			instance->height = height;
			instance->dispatchEvent(Event(Event::WINDOW_RESIZE));
		}

		static void onWindowFocus(GLFWwindow* window, int focus)
		{
			if (focus) instance->dispatchEvent(Event(Event::WINDOW_FOCUSED));
			else instance->dispatchEvent(Event(Event::WINDOW_BLURED));
		}

		static void onWindowMouseWheel(GLFWwindow* window, double offsetX, double offsetY)
		{
			WheelEvent event(Event::MOUSE_WHEEL);
			event.deltaX = (float)offsetX;
			event.deltaY = (float)offsetY;
			instance->dispatchEvent(event);
		}

		static void onWindowMouseMove(GLFWwindow* window, double mouseX, double mouseY);
		static void onWindowMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void onWindowKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}