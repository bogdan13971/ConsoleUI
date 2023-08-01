#include <conio.h>
#include "ConsoleUI.hpp"
#include "ConsoleLog.hpp"
#include "ConsoleCommands.hpp"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

using namespace ui;

ConsoleUI::ConsoleUI()
	: updateCallback{ []() {} },
	isAlive{ true },
	consoleLog{std::make_unique<ConsoleLog>()},
	title{nullptr},
	helper{nullptr}
{
	int height, width;
	std::tie(height, width) = getViewportSize();
	consoleLog->setPosition(height - 4, 0);
}

ConsoleUI::~ConsoleUI()
{}

void ConsoleUI::setMenu(std::unique_ptr<Menu>&& menu)
{
	this->menu = std::move(menu);
}

void ConsoleUI::setEventListener(std::unique_ptr<EventListener>&& eventListener)
{
	this->eventListener = std::move(eventListener);
}

void ConsoleUI::init()
{
	std::cout << ALTERNATE_BUFFER;
	std::cout << HIDE_CURSOR;
	std::cout << RESET_CURSOR;

	eventListener->handleEvent(EVENT_TYPE::START);
}

void ConsoleUI::exit()
{
	eventListener->handleEvent(EVENT_TYPE::EXIT);
	
	std::cout << SHOW_CURSOR;
	std::cout << MAIN_BUFFER;
}

void ConsoleUI::render()
{
	//reset cursor instead of full clear to fix blinking
	std::cout << RESET_CURSOR;

	if (title)
	{
		title->moveToCoords();
	}

	menu->moveToCoords();

	if (consoleLog)
	{
		consoleLog->moveToCoords();
	}

	if (helper)
	{
		helper->moveToCoords();
	}

	std::cout << HIDE_CURSOR;
}

void ConsoleUI::update()
{
	updateCallback();
}

void ConsoleUI::setUpdateCallback(std::function<void()> callback)
{
	updateCallback = callback;
}

bool ConsoleUI::handleKeyInput(char key)
{
	switch (key)
	{
	case '\r':
		eventListener->handleEvent(EVENT_TYPE::ENTER);
		menu->execute();
		return true;
	case 'x':
		eventListener->handleEvent(EVENT_TYPE::BACK);
		menu->back();
		return true;
	case 'q':
		isAlive = false;
		return true;
	default:
		if (eventListener->keyHandlerExists(key))
		{
			eventListener->handleKeyEvent(key);
			return true;
		}
		return false;
	}
}

void ConsoleUI::handleArrowInput(char arrow)
{
	switch (arrow)
	{
	case KEY_UP:
		eventListener->handleEvent(EVENT_TYPE::UP);
		menu->moveUp();
		break;
	case KEY_DOWN:
		eventListener->handleEvent(EVENT_TYPE::DOWN);
		menu->moveDown();
		break;
	case '\n':
	case KEY_RIGHT:
		eventListener->handleEvent(EVENT_TYPE::ENTER);
		menu->execute();
		break;
	case KEY_LEFT:
		eventListener->handleEvent(EVENT_TYPE::BACK);
		menu->back();
		break;
	default:
		break;
	}
}

void ConsoleUI::handleInput()
{
	//single char handling
	char key = _getch();
	if (handleKeyInput(key))
	{
		return;
	}

	//special keys have another char
	key = _getch();
	handleArrowInput(key);
}

void ConsoleUI::start()
{
	init();

	while (isAlive)
	{
		render();
		handleInput();
		update();
	}

	exit();
}

void ConsoleUI::log(std::string&& line)
{
	consoleLog->addLine(std::move(line));
}

void ConsoleUI::clearLog()
{
	consoleLog->clear();
}

Menu& ConsoleUI::getMenu()
{
	return *menu;
}

EventListener& ConsoleUI::getEventListener()
{
	return *eventListener;
}