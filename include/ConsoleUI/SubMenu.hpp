#pragma once

#include "Item.hpp"
#include <vector>
#include <stack>

namespace ui
{

class Menu;

class SubMenu : public Item
{
private:
	using HISTORY = std::stack<SubMenu*>;

private:
	unsigned short selected;
	std::vector<Item*> items;
	HISTORY* history;

private:
	SubMenu(const std::string&, HISTORY*);

	//rule of 5, non-copiable, non-movable
	SubMenu(const SubMenu&) = delete;
	SubMenu& operator=(const SubMenu&) = delete;
	SubMenu(SubMenu&&) = delete;
	SubMenu& operator=(SubMenu&&) = delete;
	~SubMenu();

	void printItems();
	void executeSelected();
	void moveUp();
	void moveDown();
	void back();

public:
	void execute() override;
	void setBaseDirty();
	void setDirty() override;

	Item* addItem(const std::string&);
	SubMenu* addSubMenu(const std::string&);
	Item* getSelected();
	const std::vector<Item*>& getItems();

public:
	friend class Menu;
};

}//uit