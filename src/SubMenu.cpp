#include "SubMenu.hpp"
#include "ConsoleCommands.hpp"

using namespace ui;

SubMenu::SubMenu(const std::string& name, HISTORY* history)
	: Item{ name },
	selected{ 0 },
	history{ history }
{}

SubMenu::~SubMenu()
{
	for (Item* item : items)
	{
		delete item;
	}
}

void SubMenu::execute()
{
	Item::execute();

	std::cout << CLEAR_SCREEN;

	history->push(this);
}

void SubMenu::printItems()
{
	for (size_t i = 0; i < items.size(); i++)
	{
		std::cout << CLEAR_LINE;

		if (i == selected)
		{
			std::cout << SET_FORMAT;
		}

		items[i]->print();

		if (i == selected)
		{
			std::cout << CLEAR_FORMAT;
		}

		std::cout << "\n";
	}
}

void SubMenu::executeSelected()
{
	if (items.empty())
	{
		return;
	}

	items[selected]->execute();
}

void SubMenu::moveUp()
{
	if (selected == 0)
	{
		return;
	}

	selected--;
}

void SubMenu::moveDown()
{
	if (selected == items.size() - 1)
	{
		return;
	}

	selected++;
}

void SubMenu::back()
{
	selected = 0;
	history->pop();

	std::cout << CLEAR_SCREEN;
}

Item* SubMenu::addItem(const std::string& name)
{
	items.push_back(new Item(name));
	return items.back();
}

SubMenu* SubMenu::addSubMenu(const std::string& name)
{
	items.push_back(new SubMenu(name, history));
	return static_cast<SubMenu*>(items.back());
}

Item* SubMenu::getSelected()
{
	return items[selected];
}

const std::vector<Item*>& SubMenu::getItems()
{
	return items;
}

void SubMenu::setDirty()
{
	setBaseDirty();

	for (auto item : items)
	{
		item->setDirty();
	}
}

void SubMenu::setBaseDirty()
{
	Item::setDirty();
}