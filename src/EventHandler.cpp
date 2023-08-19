#include "EventHandler.hpp"

using namespace ui;

EventHandler::EventHandler()
{
	const auto noOp = []() {};
	actionMap.insert({ EVENT_TYPE::UP, noOp });
	actionMap.insert({ EVENT_TYPE::DOWN, noOp });
	actionMap.insert({ EVENT_TYPE::ENTER, noOp });
	actionMap.insert({ EVENT_TYPE::BACK, noOp });
}

void EventHandler::registerEventHandler(EVENT_TYPE eventType, const std::function<void()>& handler)
{
	actionMap.insert({ eventType, handler });
}

void EventHandler::registerKeyPressEventHandler(char key, const std::function<void()>& handler)
{
	keyPressMap.insert({ key, handler });
}

void EventHandler::handleEvent(EVENT_TYPE eventType)
{
	actionMap.at(eventType).operator()();
}

void EventHandler::handleKeyEvent(char key)
{
	keyPressMap.at(key).operator()();
}

bool EventHandler::keyHandlerExists(char key)
{
	return keyPressMap.find(key) != keyPressMap.end();
}

std::unique_ptr<EventHandler> ui::createEventListener()
{
	return std::make_unique<EventHandler>();
}