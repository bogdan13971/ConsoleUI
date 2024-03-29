#include <conio.h>
#include "ConsoleUI.hpp"
#include "CVTHelper.hpp"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

using namespace ui;

ConsoleUI::ConsoleUI()
	: updateCallback{ []() {} },
	isAlive{ true }
{}

ConsoleUI::~ConsoleUI()
{}

void ConsoleUI::setContainer(std::unique_ptr<UIContainer>&& container_)
{
	this->container = std::move(container_);
}

void ConsoleUI::setEventListener(std::unique_ptr<EventHandler>&& eventListener_)
{
	this->eventListener = std::move(eventListener_);
}

void ConsoleUI::init()
{
	executeCommand(CVTCommand::ALTERNATE_BUFFER);
	executeCommand(CVTCommand::HIDE_CURSOR);
	executeCommand(CVTCommand::RESET_CURSOR);

	eventListener->handleEvent(EVENT_TYPE::START);
}

void ConsoleUI::exit()
{
	eventListener->handleEvent(EVENT_TYPE::EXIT);
	
	executeCommand(CVTCommand::SHOW_CURSOR);
	executeCommand(CVTCommand::MAIN_BUFFER);
}

void ConsoleUI::render()
{
	//reset cursor instead of full clear to fix blinking
	executeCommand(CVTCommand::RESET_CURSOR);

	if (container)
	{
		container.get()->print();
	}

	executeCommand(CVTCommand::HIDE_CURSOR);
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
		getMenu().execute();
		return true;
	case 'x':
		eventListener->handleEvent(EVENT_TYPE::BACK);
		getMenu().back();
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
		getMenu().moveUp();
		break;
	case KEY_DOWN:
		eventListener->handleEvent(EVENT_TYPE::DOWN);
		getMenu().moveDown();
		break;
	case '\n':
	case KEY_RIGHT:
		eventListener->handleEvent(EVENT_TYPE::ENTER);
		getMenu().execute();
		break;
	case KEY_LEFT:
		eventListener->handleEvent(EVENT_TYPE::BACK);
		getMenu().back();
		break;
	default:
		break;
	}
}

void ConsoleUI::handleInput()
{
	//single char handling
	char key = static_cast<char>(_getch());
	if (handleKeyInput(key))
	{
		return;
	}

	//special keys have another char
	key = static_cast<char>(_getch());
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

void ConsoleUI::log(std::string line)
{
	getContainer().getLog().addLine(std::move(line));
}

void ConsoleUI::clearLog()
{
	getContainer().getLog().clear();
}

UIContainer& ConsoleUI::getContainer()
{
	return *(container.get());
}

Menu& ConsoleUI::getMenu()
{
	return getContainer().getMenu();
}

EventHandler& ConsoleUI::getListener()
{
	return *(eventListener.get());
}