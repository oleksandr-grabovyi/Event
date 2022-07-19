#include "events_holder.hpp"

#include <iostream>

EventsHolder& EventsHolder::instance() 
{
    std::cout << "\nEventsHolder::instance() called\n";

    static EventsHolder instance;
    static int instanceCalls = 0;

    instance.onInstanceCalled(++instanceCalls);

    return instance;
}