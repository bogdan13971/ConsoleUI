#pragma once

#include <memory>

#include "menu/Menu.hpp"
#include "EventListener.hpp"
#include "menu/UIContainer.hpp"

namespace ui
{
/**
 * @brief Console Menu with key listeners
 * The visual components are rendered only at menu movements or key presses.
 * Rendering is done by moving the terminal cursor and overwritting.
 * This is done to remove terminal flickering and to simplify the rendering loop.
 * The rendering is NOT frame-based.
 * 
 * Preffer using the log function instead of printing to stdout because the cursor will not be on the last line.  
*/
class ConsoleUI
{
private:
	std::unique_ptr<UIContainer> container;
	std::unique_ptr<EventHandler> eventListener;

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

	void setContainer(std::unique_ptr<UIContainer>&& container);
	void setEventListener(std::unique_ptr<EventHandler>&& eventListener);

	/**
	 * @brief Starts the UI rendering
	 * This blocks until the menu is quit
	*/
	void start();

	/**
	 * @brief Sets callback that is called at every menu rendering.
	 * Menu rendering happens only after a menu movement: up, down, enter, back or a key event.
	*/
	void setUpdateCallback(std::function<void()> callback);

	/**
	 * @brief Copy or sink line
	*/
	void log(std::string line);
	void clearLog();

	UIContainer& getContainer();
	Menu& getMenu();
	EventHandler& getListener();
};

}//ui