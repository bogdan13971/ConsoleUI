#pragma once

#include <vector>
#include <utils/types.hpp>
#include <utils/non_owning_ptr.hpp>
#include "ItemHandle.hpp"

namespace ui
{

class SubMenu;

class SubMenuHandle
{
private:
	utils::non_owning_ptr<SubMenu> impl;

private:
	SubMenuHandle() = delete;

public:
	SubMenuHandle(const utils::non_owning_ptr<SubMenu>& impl);

	void print() const;

	void execute();

	void update();

	void setExecCallback(const ExecCallback& cb);

	void setUpdateCallback(const UpdateCallback& cb);

	const ExecCallback& getExecCallback() const;

	void setBackCallback(const BackCallback&);
	const BackCallback& getBackCallback() const;

	void printItems() const;
	void executeSelected() const;
	void moveUp() const;
	void moveDown() const;
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