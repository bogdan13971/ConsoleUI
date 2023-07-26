#include "Menu.hpp"

using namespace ui;

Menu::Menu()
	: root{ "root", &history}
{
	history.push(&root);
}

Item* Menu::addItem(const std::string& name)
{
	return root.addItem(name);
}

SubMenu* Menu::addSubmenu(const std::string& name)
{
	return root.addSubMenu(name);
}

void Menu::print()
{
	Component::print();
	
	if (root.items.size() == 0)
	{
		return;
	}

	history.top()->printItems();
}

void Menu::execute()
{
	history.top()->executeSelected();
}

void Menu::moveUp()
{
	history.top()->moveUp();
}

void Menu::moveDown()
{
	history.top()->moveDown();
}

void Menu::back()
{
	if (history.size() == 1)
	{
		return;
	}

	history.top()->back();
}

size_t Menu::numberOfItems()
{
	return history.top()->items.size();
}

Item* Menu::getSelectedItem()
{
	return history.top()->getSelected();
}

SubMenu* Menu::getParentSubMenu()
{
	return history.top();
}

std::vector<SubMenu*> Menu::getParents()
{
	std::vector<SubMenu*> parents;
	std::copy(history._Get_container().begin(),
		history._Get_container().end(),
		std::back_inserter(parents));

	return parents;
}