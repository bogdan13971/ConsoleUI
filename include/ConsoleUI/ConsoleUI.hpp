#pragma once

#include <memory>

#include "Menu.hpp"
#include "EventListener.hpp"

namespace ui
{

class ConsoleLog;

class ConsoleUI
{
public:
	Title* title;
	Helper* helper;
	std::unique_ptr<ConsoleLog> consoleLog;

private:
	std::unique_ptr<Menu> menu;
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

	void setMenu(std::unique_ptr<Menu>&&);
	void setEventListener(std::unique_ptr<EventListener>&&);

	void start();
	void setUpdateCallback(std::function<void()> callback);
	void log(std::string&&);
	void clearLog();

	Menu& getMenu();
	EventListener& getEventListener();
};

}//ui