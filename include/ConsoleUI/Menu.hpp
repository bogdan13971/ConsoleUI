#pragma once

#include <stack>
#include "UIComponent.hpp"
#include "../utils/types.hpp"
#include "../utils/non_owning_ptr.hpp"
#include "SubMenuHandle.hpp"

namespace ui
{

class Item;
class SubMenu;

class Menu : public UIComponent
{
private:
	std::shared_ptr<SubMenu> root;
	std::stack<SubMenu*> history;

public:
	Menu();
	~Menu();

	ItemHandle createItem(std::string&&, const ExecCallback& = NO_OP_CB);
	ItemHandle createItem(std::string&&, const ExecCallback&, const UpdateCallback&);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback& = NO_OP_CB);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback& = NO_OP_CB);

	void print() const override;

	void addToHistory(SubMenu&);
	void removeFromHistory();

	void execute() const;
	void moveUp() const;
	void moveDown() const;
	void back() const;

	size_t numberOfItems() const;
	Item& getSelectedItem();
	SubMenu& getParentSubMenu();
	std::vector<SubMenu*> getParents();
};

}//ui