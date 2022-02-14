#pragma once
#include <iostream>
#include <list>

//=====================================================
// # Event listener base
//=====================================================
template<typename T>
class EventListenerBase
{
public:
	EventListenerBase() = default;
	virtual ~EventListenerBase() = default;

	virtual bool isSameBindFunction(EventListenerBase<T>* elb) = 0;

	bool isSameType(EventListenerBase<T>* elb)
	{
		return !(!elb || typeid(*this) != typeid(*elb));
	}
};

//=====================================================
// # One argument event listener
//=====================================================
template<typename T>
class EventListener : public EventListenerBase<T>
{
public:
	virtual void invoke(T& value) = 0;
};

//=====================================================
// # One argument event function
//=====================================================
template<typename T>
class EventListenerFunction : public EventListener<T>
{
public:
	EventListenerFunction(void(*fn)(T& value)) : m_function(fn) {}

	void invoke(T& value) override { m_function(value); }
	bool isSameBindFunction(EventListenerBase<T>* el) override
	{
		if (!EventListenerBase<T>::isSameType(el)) return false;

		const auto elb = dynamic_cast<EventListenerFunction<T>*>(el);
		if (!elb) return false;

		return this->m_function == elb->m_function;
	}

private:
	void(*m_function)(T& value);
};

//=====================================================
// # One argument event for member function
//=====================================================
template<typename T, typename U>
class EventListenerMemberFunction : public EventListener<T>
{
public:
	EventListenerMemberFunction(void(U::* fn)(T& value), U* instance) : m_instance(instance), m_function(fn) {}

	void invoke(T& value) override { if (m_instance) (m_instance->*m_function)(value); }
	bool isSameBindFunction(EventListenerBase<T>* el) override
	{
		if (!EventListenerBase<T>::isSameType(el)) return false;

		const auto elb = dynamic_cast<EventListenerMemberFunction<T, U>*>(el);
		if (!elb) return false;

		return this->m_instance == elb->m_instance && this->m_function == elb->m_function;
	}

private:
	U* m_instance;
	void(U::* m_function)(T& value);
};

//=====================================================
// # zero argument event listener
//=====================================================
template<>
class EventListener<void> : public EventListenerBase<void>
{
public:
	virtual void invoke() = 0;
};

//=====================================================
// # zero argument event function
//=====================================================
template<>
class EventListenerFunction<void> : public EventListener<void>
{
public:
	EventListenerFunction(void(*fn)()) : m_function(fn) {}

	void invoke() override { m_function(); }
	bool isSameBindFunction(EventListenerBase<void>* el) override
	{
		if (!isSameType(el)) return false;

		const auto elb = dynamic_cast<EventListenerFunction<void>*>(el);
		if (!elb) return false;

		return this->m_function == elb->m_function;
	}

private:
	void(*m_function)();
};

//=====================================================
// # zero argument for member function
//=====================================================
template<typename U>
class EventListenerMemberFunction<void, U> : public EventListener<void>
{
public:
	EventListenerMemberFunction(void(U::* fn)(), U* instance) : m_instance(instance), m_function(fn) {}

	void invoke() override { if (m_instance) (m_instance->*m_function)(); }
	bool isSameBindFunction(EventListenerBase<void>* el) override
	{
		if (!isSameType(el)) return false;

		const auto elb = dynamic_cast<EventListenerMemberFunction<void, U>*>(el);
		if (!elb) return false;

		return this->m_instance == elb->m_instance && this->m_function == elb->m_function;
	}

private:
	U* m_instance;
	void(U::* m_function)();
};

//=====================================================
// # Event handler
//=====================================================
class EventHandler
{
public:
	template<typename T>
	static EventListener<T>* bind(void(*fn)(T& value))
	{
		return new EventListenerFunction<T>(fn);
	}

	template<typename T, typename U>
	static EventListener<T>* bind(void(U::* fn)(T& value), U* instance)
	{
		return new EventListenerMemberFunction<T, U>(fn, instance);
	}

	static EventListener<void>* bind(void(*fn)())
	{
		return new EventListenerFunction<void>(fn);
	}

	template<typename U>
	static EventListener<void>* bind(void(U::* fn)(), U* instance)
	{
		return new EventListenerMemberFunction<void, U>(fn, instance);
	}

	EventHandler() = delete;
};


//=====================================================
// # Event base
//=====================================================
template<typename T>
class EventBase
{
public:
	EventBase() = default;
	virtual ~EventBase() { clearListeners(); }

	void hook(EventListener<T>* el) { this += el; }
	void unhook(EventListener<T>* el) { this -= el; }
	void clearListeners()
	{
		for (auto listener : m_listeners)
		{
			delete listener;
			listener = 0;
		}
		m_listeners.clear();
	}

	EventBase& operator+=(EventListener<T>* el)
	{
		m_listeners.push_back(el);

		return *this;
	}
	EventBase& operator-=(EventListener<T>* el)
	{
		for (auto i = m_listeners.begin(); i != m_listeners.end(); ++i)
		{
			EventListener<T>* listener = *i;
			if (el->isSameBindFunction(listener))
			{
				delete listener;
				listener = 0;

				m_listeners.erase(i);
				break;
			}
		}

		return *this;
	}

	// Disable assignment operator
	EventBase& operator=(const EventBase&) = delete;

protected:
	std::list<EventListener<T>*> m_listeners;
};

//=====================================================
// # One argument event
//=====================================================
template<typename T>
class Event : public EventBase<T>
{
public:
	void operator()(T& value)
	{
		for (const auto listener : this->m_listeners)
			if (listener != nullptr) listener->invoke(value);
	}
};

//=====================================================
// # Zero argument event
//=====================================================
template<>
class Event<void> : public EventBase<void>
{
public:
	void operator()()
	{
		for (const auto listener : m_listeners)
			if (listener != nullptr) listener->invoke();
	}
};