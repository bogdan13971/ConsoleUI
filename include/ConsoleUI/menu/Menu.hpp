#pragma once

#include <stack>
#include "UIComponent.hpp"
#include <utils/types.hpp>
#include <utils/non_owning_ptr.hpp>
#include "SubMenuHandle.hpp"

namespace ui
{

class Item;
class SubMenu;

/**
 * @brief A menu is a hierarchy of submenus containing a history of previous parents
 * Each menu operation is executed on the current submenu.
*/
class Menu : public UIComponent
{
private:
	std::shared_ptr<SubMenu> root;
	std::stack<SubMenu*> history;

public:
	Menu();
	~Menu();

	ItemHandle createItem(std::string&& label, const ExecCallback& execCB = NO_OP_CB);
	ItemHandle createItem(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB);
	SubMenuHandle createSubmenu(std::string&& label, const ExecCallback& execCB = NO_OP_CB);
	SubMenuHandle createSubmenu(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB, const BackCallback& backCB = NO_OP_CB);

	/**
	 * @brief Print the current submenu on stdout at the current cursor position
	*/
	void print() const override;

	/**
	 * @brief Change the active submenu
	*/
	void addToHistory(SubMenu& submenu);

	/**
	 * @brief Change the active submenu to the previous one
	*/
	void removeFromHistory();

	/**
	 * @brief Executes the callback of the selected item in the current submenu
	*/
	void execute() const;

	/**
	 * @brief Selects the item above in the current submenu
	*/
	void moveUp() const;

	/**
	 * @brief Selects the item below in the current submenu
	*/
	void moveDown() const;

	/**
	 * @brief Return to the previous submenu
	*/
	void back() const;

	size_t numberOfItems() const;
	Item& getSelectedItem();
	SubMenu& getParentSubMenu();
	std::vector<std::reference_wrapper<SubMenu>> getParents();
};

std::unique_ptr<Menu> createMenu();

}//ui