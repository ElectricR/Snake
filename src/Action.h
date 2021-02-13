#pragma once
#include <memory>
#include "ActionStatus.h"
#include "ActionList.h"
#include "Events.h"

class ActionBase{
public:
	ActionBase(ActionType prio):
		priority_(prio)
	{}
	
	virtual ~ActionBase() = default;

	virtual ActionStatus handle(std::unique_ptr<Event>& event) = 0;

	ActionType get_priority() {
		return priority_;
	}

private:
	ActionType priority_;
};

template<class T>
class Action:
	public ActionBase
{
public:
	Action(const std::weak_ptr<T>& obj_ptr, 
			ActionStatus(T::*m_ptr)(std::unique_ptr<Event>&), 
			ActionType prio):
		ActionBase(prio),
		obj_ptr_(obj_ptr),
		m_ptr_(m_ptr)
	{}

	ActionStatus handle(std::unique_ptr<Event>& event) override {
		std::shared_ptr<T> ptr = obj_ptr_.lock();
		return (ptr.get()->*m_ptr_)(event);
	}

	std::weak_ptr<T> get_object() const {
		return obj_ptr_;
	}
private:
	std::weak_ptr<T> obj_ptr_;
	ActionStatus(T::*m_ptr_)(std::unique_ptr<Event>&);
};

template<class T>
std::unique_ptr<ActionBase> make_action(const std::weak_ptr<T>& ptr, 
		ActionStatus(T::*m_ptr)(std::unique_ptr<Event>&), 
		ActionType priority)
{
	return std::unique_ptr<ActionBase>(new Action(ptr, m_ptr, priority));
}

class ActionComparator {
public:
	bool operator()(const std::unique_ptr<ActionBase>& a, const std::unique_ptr<ActionBase>& b) const {
		return a->get_priority() < b->get_priority();
	}
};
