#pragma once

#include <stack>
#include <memory>
#include "types.hpp"

namespace ui
{

class Menu;

class MenuBuilder
{
private:
	std::unique_ptr<Menu> menu;

public:
	MenuBuilder();
	std::unique_ptr<Menu> build();

	MenuBuilder& addItem(std::string&&, const ExecCallback& = NO_OP_CB);
	MenuBuilder& addItem(std::string&&, const ExecCallback&, const UpdateCallback&);

	MenuBuilder& addSubmenu(std::string&&, const ExecCallback& = NO_OP_CB);
	MenuBuilder& addSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback & = NO_OP_CB);
	
	MenuBuilder& endSubmenu();
};

}// ui