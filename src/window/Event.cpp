#include "window/Event.h"

namespace engine
{
	const int Event::DEFAULT		= 0;
	const int Event::MOUSE_MOVE		= 1;
	const int Event::MOUSE_DOWN		= 2;
	const int Event::MOUSE_UP		= 3;
	const int Event::MOUSE_WHEEL	= 4;
	const int Event::KEY_DOWN		= 5;
	const int Event::KEY_UP			= 6;
	const int Event::WINDOW_RESIZE	= 7;
	const int Event::WINDOW_FOCUSED	= 8;
	const int Event::WINDOW_BLURED	= 9;

	int Event::lastEventType		= 9;
}