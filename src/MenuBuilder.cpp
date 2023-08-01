#include "../utils/MenuBuilder.hpp"
#include "Menu.hpp"
#include "SubMenu.hpp"

using namespace ui;

MenuBuilder::MenuBuilder()
	: menu{ std::make_unique<Menu>() }
{}

std::unique_ptr<Menu> MenuBuilder::build()
{
	return std::move(menu);
}

MenuBuilder& MenuBuilder::addItem(std::string&& label, const ExecCallback& execCB)
{
	menu->getParentSubMenu().createItem(std::move(label), execCB);
	return *this;
}

MenuBuilder& MenuBuilder::addItem(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB)
{
	menu->getParentSubMenu().createItem(std::move(label), execCB, updateCB);
	return *this;
}

MenuBuilder& MenuBuilder::addSubmenu(std::string&& label, const ExecCallback& execCB)
{
	auto handle = menu->getParentSubMenu().createSubmenu(std::move(label), execCB);
	menu->addToHistory(*handle);
	return *this;
}

MenuBuilder& MenuBuilder::addSubmenu(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB, const SubMenu::BackCallback& backCB)
{
	menu->getParentSubMenu().createSubmenu(std::move(label), execCB, updateCB, backCB);
	return *this;
}

MenuBuilder& MenuBuilder::endSubmenu()
{
	menu->removeFromHistory();
	return *this;
}