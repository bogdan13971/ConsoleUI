#pragma once

#include <stack>
#include <memory>
#include "types.hpp"

namespace ui
{

class Menu;

/**
 * @brief Simple class to build a menu hierarchy
*/
class MenuBuilder
{
private:
	std::unique_ptr<Menu> menu;

public:
	MenuBuilder();
	std::unique_ptr<Menu> build();

	MenuBuilder& addItem(std::string&& label, const ExecCallback& execCB = NO_OP_CB);
	MenuBuilder& addItem(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB);

	MenuBuilder& addSubmenu(std::string&& label, const ExecCallback& execCB = NO_OP_CB);
	MenuBuilder& addSubmenu(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB, const BackCallback& backCB = NO_OP_CB);
	
	MenuBuilder& endSubmenu();
};

}// ui