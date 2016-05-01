#pragma once

#include <GLFW\glfw3.h>

namespace engine
{
	class Event
	{
	public:
		Event(int type) : type(type)
		{ }

		virtual ~Event()
		{ }

		static int nextEventType()
		{
			return ++lastEventType;
		}

	public:
		int type;

		static const int DEFAULT;
		static const int MOUSE_MOVE;
		static const int MOUSE_DOWN;
		static const int MOUSE_UP;
		static const int MOUSE_WHEEL;
		static const int KEY_DOWN;
		static const int KEY_UP;
		static const int WINDOW_RESIZE;
		static const int WINDOW_FOCUSED;
		static const int WINDOW_BLURED;

		static int lastEventType;
	};

	enum class MouseButton : unsigned char
	{
		None,
		Left,
		Right,
		Middle,
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent(int type)
			: Event(type)
			, altKey(false)
			, ctrlKey(false)
			, shiftKey(false)
			, button(MouseButton::None)
			, mouseX(0)
			, mouseY(0)
		{ }

	public:
		bool altKey;
		bool ctrlKey;
		bool shiftKey;

		MouseButton button;

		int mouseX;
		int mouseY;
	};

	class WheelEvent : public Event
	{
	public:
		WheelEvent(int type)
			: Event(type)
			, deltaX(0)
			, deltaY(0)
			, deltaZ(0)
		{ }

	public:
		float deltaX;
		float deltaY;
		float deltaZ;
	};

	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(int type)
			: Event(type)
			, altKey(false)
			, ctrlKey(false)
			, shiftKey(false)
			, key(GLFW_KEY_UNKNOWN)
		{ }

	public:
		bool altKey;
		bool ctrlKey;
		bool shiftKey;
		int key;
	};
}
