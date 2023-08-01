#pragma once

#include "SubMenu.hpp"
#include "Component.hpp"

namespace ui
{

class Menu : public Component
{
private:
	std::shared_ptr<SubMenu> root;
	std::stack<SubMenu*> history;

	void registerToMenu(SubMenu&);

public:
	Menu();
	~Menu();

	Item& addItem(std::string&&, const Item::ExecCallback & = Item::NO_OP_CB);
	Item& addItem(std::string&&, const Item::ExecCallback&, const Item::UpdateCallback&);
	SubMenu& addSubmenu(std::string&&, const Item::ExecCallback & = Item::NO_OP_CB);
	SubMenu& addSubmenu(std::string&&, const Item::ExecCallback&, const Item::UpdateCallback&, const SubMenu::BackCallback & = Item::NO_OP_CB);

	void moveToCoords() const override;

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