#pragma once

#include <vector>
#include <utils/types.hpp>
#include <utils/non_owning_ptr.hpp>
#include "ItemHandle.hpp"

namespace ui
{

class SubMenu;

/**
 * @brief Submenu handle created only by a menu
*/
class SubMenuHandle
{
private:
	utils::non_owning_ptr<SubMenu> impl;

private:
	SubMenuHandle() = delete;

public:
	SubMenuHandle(const utils::non_owning_ptr<SubMenu>& impl);

	/**
	* @brief Prints the label on stdout at the current cursor position
	*/
	void print() const;

	/**
	* @brief Execute the registered callback
	*/
	void execute();

	/**
	* @brief Replace the current label with the label returned by the update callback
	*/
	void update();

	void setExecCallback(const ExecCallback& cb);

	void setUpdateCallback(const UpdateCallback& cb);

	const ExecCallback& getExecCallback() const;

	void setBackCallback(const BackCallback&);
	const BackCallback& getBackCallback() const;

	/**
	 * @brief Print all the contained elements on stdout at the current cursor position
	*/
	void printItems() const;

	/**
	 * @brief Execute the registered callback of the selected element
	*/
	void executeSelected() const;

	/**
	 * @brief Select the element above the current one
	*/
	void moveUp() const;

	/**
	 * @brief Select the element below the current one
	*/
	void moveDown() const;

	/**
	 * @brief Return to the previous submenu
	*/
	void back() const;

	ItemHandle createItem(std::string&&, const ExecCallback & = NO_OP_CB);
	ItemHandle createItem(std::string&&, const ExecCallback&, const UpdateCallback&);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback & = NO_OP_CB, const BackCallback & = NO_OP_CB);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback & = NO_OP_CB);

	Item& getSelected();
	std::vector<std::reference_wrapper<Item>> getItems();
	size_t numberOfItems() const;
};

}//uit