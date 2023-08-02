#include "SubMenu.hpp"
#include "ConsoleCommands.hpp"
#include "Menu.hpp"

using namespace ui;
using utils::non_owning_ptr;

SubMenu::SubMenu(Menu& menu,std::string&& label, 
	const ExecCallback& execCB,
	const BackCallback& backCB)
	: SubMenu{ menu,std::move(label), execCB, [&]() {return label;}, backCB }
{}

SubMenu::SubMenu(Menu& menu,std::string&& label,
	const ExecCallback& execCB,
	const UpdateCallback& updateCB,
	const BackCallback& backCB)
	: Item{ std::move(label), execCB, updateCB },
	backCallback{ backCB },
	selected{ 0 },
	menu{menu}
{};

void SubMenu::setBackCallback(const BackCallback& backCB)
{
	backCallback = backCB;
}

const SubMenu::BackCallback& SubMenu::getBackCallback() const
{
	return backCallback;
}

void SubMenu::execute()
{
	Item::execute();

	menu.addToHistory(*this);

	executeCommand(CVTCommand::CLEAR_SCREEN);
}

void SubMenu::update()
{
	Item::update();

	for (const auto& item : items)
	{
		item->update();
	}
}

void SubMenu::printItems() const
{
	for (size_t i = 0; i < items.size(); i++)
	{
		executeCommand(CVTCommand::CLEAR_LINE);

		if (i == selected)
		{
			executeCommand(CVTCommand::SET_FORMAT);
		}

		items[i]->print();

		if (i == selected)
		{
			executeCommand(CVTCommand::CLEAR_FORMAT);
		}
	}

	std::cout << "\n";
}

void SubMenu::executeSelected() const
{
	if (items.empty())
	{
		return;
	}

	items[selected]->execute();
}

void SubMenu::moveUp() const
{
	if (selected == 0)
	{
		return;
	}

	selected--;
}

void SubMenu::moveDown() const
{
	if (selected == items.size() - 1)
	{
		return;
	}

	selected++;
}

void SubMenu::back() const
{
	backCallback();

	selected = 0;
	executeCommand(CVTCommand::CLEAR_SCREEN);

	menu.removeFromHistory();
}

non_owning_ptr<Item> SubMenu::createItem(std::string&& label_, const ExecCallback& execCB)
{
	auto item = new Item(std::move(label_), execCB);
	items.push_back(std::unique_ptr<Item>(item));
	return items.back().get();
}

non_owning_ptr<Item> SubMenu::createItem(std::string&& label_, const ExecCallback& execCB, const UpdateCallback& updateCB)
{
	auto item = createItem(std::move(label_), execCB);
	item->setUpdateCallback(updateCB);
	return item;
}

non_owning_ptr<SubMenu> SubMenu::createSubmenu(std::string&& label_, const ExecCallback& execCB, const BackCallback& backCB)
{
	auto submenu = new SubMenu(menu, std::move(label_), execCB, backCB);
	items.push_back(std::unique_ptr<SubMenu>(submenu));
	return dynamic_cast<SubMenu*>(items.back().get());
}

non_owning_ptr<SubMenu> SubMenu::createSubmenu(std::string&& label_, const ExecCallback& execCB, const UpdateCallback& updateCB, const SubMenu::BackCallback& backCB)
{
	auto submenu = createSubmenu(std::move(label_), execCB);
	submenu->setUpdateCallback(updateCB);
	submenu->setBackCallback(backCB);
	return submenu;
}

Item& SubMenu::getSelected()
{
	return *(items[selected]);
}

std::vector<std::reference_wrapper<Item>> SubMenu::getItems()
{
	decltype(getItems()) result;
	for (const auto& item : items)
	{
		result.push_back(*item);
	}

	return result;
}

size_t SubMenu::numberOfItems() const
{
	return items.size();
}