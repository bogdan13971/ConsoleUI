#pragma once

#include <functional>
#include <unordered_map>
#include <memory>

namespace ui
{

enum class EVENT_TYPE
{
	START, UP, DOWN, ENTER, BACK, EXIT
};

/**
 * @brief Event handler for the menu movement events or key presses.
 * The menu movements have default empty handlers.
*/
class EventHandler
{
private:
	std::unordered_map<EVENT_TYPE, std::function<void()>> actionMap;
	std::unordered_map<char, std::function<void()>> keyPressMap;

public:
	EventHandler();

	void registerEventHandler(EVENT_TYPE eventType, const std::function<void()>& handler);

	void registerKeyPressEventHandler(char key, const std::function<void()>& handler);

	void handleEvent(EVENT_TYPE eventType);

	void handleKeyEvent(char key);

	bool keyHandlerExists(char key);
};

std::unique_ptr<EventHandler> createEventListener();

}//ui