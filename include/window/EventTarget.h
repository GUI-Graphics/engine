#pragma once

#include <vector>
#include "EventHandler.h"

namespace engine
{
	class EventTarget
	{
	public:
		EventTarget()
		{ }

		virtual ~EventTarget()
		{ }

		void addEventHandler(EventHandler& handler)
		{
			handlers.push_back(&handler);
		}

		void removeEventHandler(EventHandler& handler)
		{
			auto itr = std::find(handlers.begin(), handlers.end(), &handler);

			if (itr != handlers.end())
			{
				handlers.erase(itr);
			}
		}

		void dispatchEvent(Event& event)
		{
			for (auto handler : handlers)
			{
				handler->target = this;
				handler->processEvent(event);
			}
		}

	protected:
		std::vector<EventHandler*> handlers;
	};
}
