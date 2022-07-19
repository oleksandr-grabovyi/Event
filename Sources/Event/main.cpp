#include <iostream>
#include <vector>

# include "events_holder.hpp"


namespace
{
	void onEventsHolderInstanceCalled(int count)
	{
		std::cout << "Global func CB. EventsHolder::instance called: "<< count << " times.\n";
	}

	class SomeListener
	{
	public:
		SomeListener()
		{
			auto& eventsHolder = EventsHolder::instance();
			m_listenerID = eventsHolder.onInstanceCalled.subscribe(
				this, &SomeListener::onEventsHolderInstanceCalled);
			std::cout << "\n========= Class method subscribed ========\n";
		}

		~SomeListener()
		{
			EventsHolder::instance().onInstanceCalled.unsubscribe(m_listenerID);
			std::cout << "\n========= Class method unsubscribed ========\n";
		}

	private:
		EventListenerID m_listenerID;

		void onEventsHolderInstanceCalled(int count)
		{
			std::cout << "Class method CB. EventsHolder::instance called: " << count << " times.\n";
		}
	};
}

int main()
{
	auto& eventsHolder = EventsHolder::instance();
	auto listenerID = eventsHolder.onInstanceCalled.subscribe(&onEventsHolderInstanceCalled);
	std::cout << "\n========= Global function subscribed ========\n";

	auto someListener = SomeListener();
	EventsHolder::instance();

	eventsHolder.onInstanceCalled.unsubscribe(listenerID);
	std::cout << "\n========= Global function unsubscribe ========\n";

	return 0;
}