#pragma once

#include <vector>
#include "Callback.h"

namespace engine
{
	class EventTarget;

	class EventHandler
	{
	public:
		EventHandler() : target(nullptr)
		{ }

		virtual ~EventHandler()
		{
			for (auto callback : callbacks)
			{
				delete callback;
			}
		}

		template<class Handler, class Evt>
		void addCallback(int type, void(Handler::*func)(Evt&))
		{
			callbacks.push_back(new Callback<Handler, Evt>(type, func, static_cast<Handler*>(this)));
		}

		template<class Handler, class Evt>
		void removeCallback(int type, void(Handler::*func)(Evt& e))
		{
			for (auto itr = callbacks.begin(), end = callbacks.end(); itr != end; ++itr)
			{
				Callback<Handler, Evt>* callback = dynamic_cast<Callback<Handler, Evt>*>(*itr);

				if (callback && callback->type == type && callback->func == func)
				{
					callbacks.erase(itr);
					delete callback;
				}
			}
		}

		void processEvent(Event& e)
		{
			for (auto callback : callbacks)
			{
				callback->onEvent(e);
			}
		}

	public:
		EventTarget* target;
		std::vector<AbstractCallbck*> callbacks;
	};
}
