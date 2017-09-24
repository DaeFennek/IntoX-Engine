#pragma once

#include <list>
#include <functional>
#include <memory>

template <typename ... Args> 
struct Event : public std::shared_ptr <std::list<std::function<void(Args...)>>> 
{
	using handler = std::function <void(Args...)>;
	using listener_list = std::list<handler>;

	struct Listener
	{
		std::weak_ptr<listener_list> the_event;
		typename listener_list::iterator it;

		Listener(){ }

		Listener(Event& s, handler f)
		{
			Observe(s, f);
		}

		Listener(Listener &&other)
		{
			the_event = other.the_event;
			it = other.it;
			other.the_event.reset();
		}

		Listener(const Listener &other) = delete;

		Listener & operator=(const Listener &other) = delete;

		Listener & operator=(Listener &&other)
		{
			Reset();
			the_event = other.the_event;
			it = other.it;			
			other.the_event.reset();
			return *this;
		}

		void Observe(Event& s, handler f)
		{
			Reset();
			the_event = s;
			it = s->insert(s->end(), f);
		}

		void Reset()
		{
			if (!the_event.expired()) the_event.lock()->erase(it);
			the_event.reset();
		}

		~Listener(){ Reset(); }
	};

	Event() : std::shared_ptr<listener_list>(std::make_shared<listener_list>()){ }
	Event(const Event &) = delete;
	Event & operator=(const Event &) = delete;

	void Notify(Args... args)
	{
		for (auto &f : **this)
		{
			f(args...);
		}
	}

	Listener Connect(handler h)
	{
		return Listener(*this, h);
	}
};

using WindowClosedEvent = Event<int>;

class EventManger
{
public:
	EventManger() {};
	~EventManger() {};

	static EventManger& Get()
	{
		static EventManger s_instance;
		return s_instance;
	}

	WindowClosedEvent m_WindowClosedEvent;
};