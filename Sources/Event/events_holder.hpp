#pragma once
#include "event.hpp"

class EventsHolder
{
    EventsHolder() = default;

public:
	Event<int> onInstanceCalled;

	static EventsHolder& instance();
};