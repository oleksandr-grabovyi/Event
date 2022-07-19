#pragma once

#include <functional>
#include <map>

using EventListenerID = int;

template<class ... P>
class Event
{
	using ListenerType = std::function<void(P ...)>;
public:

	EventListenerID subscribe(ListenerType listener)
	{
		EventListenerID listenerID = generateListenerID();
		m_listeners[listenerID] = listener;
		return listenerID;
	};

	template<class T, class ClassListenerType>
	EventListenerID subscribe(T obj, ClassListenerType listener)
	{
		return subscribe([obj, listener](P ... params)
			{
				(*obj.*listener)(std::forward<P>(params)...);
			});
	}

	void unsubscribe(EventListenerID listenerID)
	{
		m_listeners.erase(listenerID);
	}

	void invoke(P ... params)
	{
		for (auto& listener : m_listeners)
		{
			listener.second(std::forward<P>(params)...);
		}
	}

	void operator()(P ... params)
	{
		invoke(std::forward<P>(params)...);
	}

private:
	EventListenerID m_listenerID = 0;

	EventListenerID generateListenerID()
	{
		return m_listenerID++;
	}

	std::map<EventListenerID, ListenerType> m_listeners;
};