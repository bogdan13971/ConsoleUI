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
	UIContainer(std::unique_ptr<Title>&& title,
		std::unique_ptr<Menu>&& menu,
		std::unique_ptr<ConsoleLog>&& log,
		std::unique_ptr<Helper>&& helper);

	Title& getTitle();

	Menu& getMenu();

	ConsoleLog& getLog();

	Helper& getHelper();

	static std::unique_ptr<UIContainer> createSimple(std::string&& title, std::unique_ptr<Menu>&&);

	void print();
};


}// ui