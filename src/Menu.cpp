#include "Menu.hpp"

using namespace ui;

Menu::Menu()
	: root{new SubMenu(*this, "root")}
{
	history.push(root.get());
}

Menu::~Menu()
{}

non_owning_ptr<Item> Menu::createItem(std::string&& label, const ExecCallback& execCB)
{
	return root->createItem(std::move(label), execCB);
}

non_owning_ptr<Item> Menu::createItem(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB)
{
	return root->createItem(std::move(label), execCB, updateCB);
}

non_owning_ptr<SubMenu> Menu::createSubmenu(std::string&& label, const ExecCallback& execCB)
{
	return root->createSubmenu(std::move(label), execCB);
}

non_owning_ptr<SubMenu> Menu::createSubmenu(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB, const BackCallback& backCB)
{
	return root->createSubmenu(std::move(label), execCB, updateCB, backCB);
}

void Menu::moveToCoords() const
{
	Component::moveToCoords();

	history.top()->printItems();
}

void Menu::addToHistory(SubMenu& submenu)
{
	history.push(&submenu);
}

void Menu::removeFromHistory()
{
	if (history.size() != 1)
	{
		history.pop();
	}
}

void Menu::execute() const
{
	history.top()->executeSelected();
}

void Menu::moveUp() const
{
	history.top()->moveUp();
}

void Menu::moveDown() const
{
	history.top()->moveDown();
}

void Menu::back() const
{
	if (history.size() == 1)
	{
		return;
	}

	history.top()->back();
}

size_t Menu::numberOfItems() const
{
	return history.top()->numberOfItems();
}

Item& Menu::getSelectedItem()
{
	return history.top()->getSelected();
}

SubMenu& Menu::getParentSubMenu()
{
	return *(history.top());
}

std::vector<SubMenu*> Menu::getParents()
{
	std::vector<SubMenu*> parents;
	std::copy(history._Get_container().begin(),
		history._Get_container().end(),
		std::back_inserter(parents));

	return parents;
}