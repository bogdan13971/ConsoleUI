#include "ItemHandle.hpp"
#include "Item.hpp"

using namespace ui;

ItemHandle::ItemHandle(const utils::non_owning_ptr<Item>& impl)
	:impl{impl}
{}

void ItemHandle::print() const
{
	impl->print();
}

void ItemHandle::execute()
{
	impl->execute();
}

void ItemHandle::update()
{
	impl->update();
}

void ItemHandle::setExecCallback(const ExecCallback& cb)
{
	impl->setExecCallback(cb);
}

void ItemHandle::setUpdateCallback(const UpdateCallback& cb)
{
	impl->setUpdateCallback(cb);
}

const ExecCallback& ItemHandle::getExecCallback() const
{
	return impl->getExecCallback();
}