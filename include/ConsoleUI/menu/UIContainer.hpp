#pragma once

#include "UIComponent.hpp"

namespace ui
{

class Menu;

class UIContainer
{
private:
	std::unique_ptr<Title> title;
	std::unique_ptr<Menu> menu;
	std::unique_ptr<ConsoleLog> log;
	std::unique_ptr<Helper> helper;

public:
	/**
	 * @brief Create container by sinking UI Components
	*/
	UIContainer(std::unique_ptr<Title>&& title,
		std::unique_ptr<Menu>&& menu,
		std::unique_ptr<ConsoleLog>&& log,
		std::unique_ptr<Helper>&& helper);

	Title& getTitle();

	Menu& getMenu();

	ConsoleLog& getLog();

	Helper& getHelper();

	/**
	 * @brief Create a container with a default log and helper
	 * @param titleLabel Label for the title UI component
	 * @param menu Menu UI component
	 * @return 
	*/
	static std::unique_ptr<UIContainer> createSimple(
		std::string&& titleLabel, 
		std::unique_ptr<Menu>&& menu);

	/**
	 * @brief Print all the elements of the container
	*/
	void print() const;
};


}// ui