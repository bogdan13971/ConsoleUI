#pragma once

#include "SubMenu.hpp"
#include "Component.hpp"

namespace ui
{

class Menu : public Component
{
private:
	SubMenu root;
	SubMenu::HISTORY history;

public:
	Menu();

	Item* addItem(const std::string&);
	SubMenu* addSubmenu(const std::string&);

	void print() override;

	void execute();
	void moveUp();
	void moveDown();
	void back();

	void log(std::string&&);

	size_t numberOfItems();
	Item* getSelectedItem();
	SubMenu* getParentSubMenu();
	std::vector<SubMenu*> getParents();
};

}//ui