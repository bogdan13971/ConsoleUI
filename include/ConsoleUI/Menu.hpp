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

	non_owning_ptr<Item> createItem(std::string&&, const ExecCallback& = NO_OP_CB);
	non_owning_ptr<Item> createItem(std::string&&, const ExecCallback&, const UpdateCallback&);
	non_owning_ptr<SubMenu> createSubmenu(std::string&&, const ExecCallback& = NO_OP_CB);
	non_owning_ptr<SubMenu> createSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback& = NO_OP_CB);

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