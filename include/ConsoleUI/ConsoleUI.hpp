#pragma once

#include <memory>

#include "menu/Menu.hpp"
#include "EventListener.hpp"
#include "menu/UIContainer.hpp"

namespace ui
{

class ConsoleUI
{
private:
	std::unique_ptr<UIContainer> container;
	std::unique_ptr<EventListener> eventListener;

	std::function<void()> updateCallback;
	bool isAlive;

	void init();
	void exit();
	void render();
	void update();
	void handleInput();
	bool handleKeyInput(char);
	void handleArrowInput(char);

public:
	ConsoleUI();
	~ConsoleUI();

	void setContainer(std::unique_ptr<UIContainer>&&);
	void setEventListener(std::unique_ptr<EventListener>&&);

	void start();
	void setUpdateCallback(std::function<void()> callback);
	/**
	 * @brief Log or sink line
	*/
	void log(std::string line);
	void clearLog();

	UIContainer& getContainer();
	Menu& getMenu();
	EventListener& getListener();
};

}//ui