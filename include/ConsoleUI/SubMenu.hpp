#pragma once

#include "Item.hpp"
#include <vector>
#include <stack>

namespace ui
{

class Menu;

class SubMenu : public Item
{
public:
	using BackCallback = std::function<void()>;

private:
	Menu& menu;
	BackCallback backCallback;
	mutable unsigned short selected;
	std::vector<std::unique_ptr<Item>> items;

public:
	SubMenu(Menu&, std::string&&, const ExecCallback& = NO_OP_CB);

	SubMenu(Menu&, std::string&&,
		const ExecCallback&,
		const UpdateCallback&,
		const BackCallback& = NO_OP_CB);
	
	SubMenu(const SubMenu&) = delete;
	SubMenu& operator=(const SubMenu&) = delete;
	~SubMenu() = default;

	void setBackCallback(const BackCallback&);
	const BackCallback& getBackCallback() const;

	void execute() override;
	void update() override;

	void printItems() const;
	void executeSelected() const;
	void moveUp() const;
	void moveDown() const;
	void back() const;

	ItemHandle createItem(std::string&&, const ExecCallback& = NO_OP_CB);
	ItemHandle createItem(std::string&&, const ExecCallback&, const UpdateCallback&);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback& = NO_OP_CB);
	SubMenuHandle createSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback& = NO_OP_CB);
	
	SubMenu& addItem(std::string&&, const ExecCallback & = NO_OP_CB);

	Item& getSelected();
	std::vector<std::reference_wrapper<Item>> getItems();
	size_t numberOfItems() const;

public:
	friend class Menu;
};

}//uit