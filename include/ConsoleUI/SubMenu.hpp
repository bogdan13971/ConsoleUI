#pragma once

#include "Item.hpp"
#include <vector>
#include <stack>

namespace ui
{

class SubMenu : public Item
{
public:
	using BackCallback = std::function<void()>;

private:
	BackCallback backCallback;
	unsigned short selected;
	std::vector<std::unique_ptr<Item>> items;

public:
	SubMenu(std::string&&, const ExecCallback& = NO_OP_CB);

	SubMenu(std::string&&,
		const ExecCallback&,
		const UpdateCallback&,
		const BackCallback& = NO_OP_CB);
	
	SubMenu(const SubMenu&) = delete;
	SubMenu& operator=(const SubMenu&) = delete;
	~SubMenu() = default;

	void setBackCallback(const BackCallback&);
	const BackCallback& getBackCallback() const;

	void execute() const override;
	void update() override;

	void printItems() const;
	void executeSelected() const;
	void moveUp();
	void moveDown();
	void back();

	Item& addItem(std::string&&, const ExecCallback& = NO_OP_CB);
	Item& addItem(std::string&&, const ExecCallback&, const UpdateCallback&);
	SubMenu& addSubmenu(std::string&&, const ExecCallback& = NO_OP_CB);
	SubMenu& addSubmenu(std::string&&, const ExecCallback&, const UpdateCallback&, const BackCallback& = NO_OP_CB);
	
	Item& getSelected();
	std::vector<std::reference_wrapper<Item>> getItems();
	size_t numberOfItems() const;

public:
	friend class Menu;
};

}//uit