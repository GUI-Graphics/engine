#pragma once

#include "Event.h"

namespace engine
{
	class AbstractCallbck
	{
	public:
		virtual ~AbstractCallbck()
		{ }

		virtual void onEvent(Event& e) = 0;
	};

	template<class Handler, class Evt>
	class Callback : public AbstractCallbck
	{
	public:
		Callback(int type, void(Handler::*func)(Evt&), Handler* handler)
			: type(type)
			, func(func)
			, handler(handler)
		{ }

		void onEvent(Event& e) override
		{
			if (e.type == type) (handler->*func)(static_cast<Evt&>(e));
		}

	public:
		const int type;
		void(Handler::*func)(Evt&);
		Handler* handler;
	};
}
