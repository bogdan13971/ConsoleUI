#include "menu/SubMenuHandle.hpp"
#include "SubMenu.hpp"

using namespace ui;

SubMenuHandle::SubMenuHandle(const utils::non_owning_ptr<SubMenu>& impl)
	:impl{ impl }
{}

void SubMenuHandle::print() const
{
	impl->print();
}

void SubMenuHandle::execute()
{
	impl->execute();
}

void SubMenuHandle::update()
{
	impl->update();
}

void SubMenuHandle::setExecCallback(const ExecCallback& cb)
{
	impl->setExecCallback(cb);
}

void SubMenuHandle::setUpdateCallback(const UpdateCallback& cb)
{
	impl->setUpdateCallback(cb);
}

const ExecCallback& SubMenuHandle::getExecCallback() const
{
	return impl->getExecCallback();
}

void SubMenuHandle::setBackCallback(const BackCallback& backCB)
{
	impl->setBackCallback(backCB);
}

const BackCallback& SubMenuHandle::getBackCallback() const
{
	return impl->getBackCallback();
}

void SubMenuHandle::printItems() const
{
	impl->printItems();
}

void SubMenuHandle::executeSelected() const
{
	impl->executeSelected();
}

void SubMenuHandle::moveUp() const
{
	impl->moveUp();
}

void SubMenuHandle::moveDown() const
{
	impl->moveDown();
}

void SubMenuHandle::back() const
{
	impl->back();
}

ItemHandle SubMenuHandle::createItem(std::string&& label, const ExecCallback& execCB)
{
	return impl->createItem(std::move(label), execCB);
}

ItemHandle SubMenuHandle::createItem(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB)
{
	return impl->createItem(std::move(label), execCB, updateCB);
}

SubMenuHandle SubMenuHandle::createSubmenu(std::string&& label, const ExecCallback& execCB, const BackCallback& backCB)
{
	return impl->createSubmenu(std::move(label), execCB, backCB);
}

SubMenuHandle SubMenuHandle::createSubmenu(std::string&& label, const ExecCallback& execCB, const UpdateCallback& updateCB, const SubMenu::BackCallback& backCB)
{
	return impl->createSubmenu(std::move(label), execCB, updateCB, backCB);
}

Item& SubMenuHandle::getSelected()
{
	return impl->getSelected();
}
std::vector<std::reference_wrapper<Item>> SubMenuHandle::getItems()
{
	return impl->getItems();
}

size_t SubMenuHandle::numberOfItems() const
{
	return impl->numberOfItems();
}