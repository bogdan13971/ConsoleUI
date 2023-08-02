#pragma once

#include <utils/types.hpp>
#include <utils/non_owning_ptr.hpp>

namespace ui
{

class Item;

class ItemHandle
{
private:
	utils::non_owning_ptr<Item> impl;

private:
	ItemHandle() = delete;

public:
	ItemHandle(const utils::non_owning_ptr<Item>& impl);

	void print() const;

	void execute();

	void update();

	void setExecCallback(const ExecCallback& cb);

	void setUpdateCallback(const UpdateCallback& cb);

	const ExecCallback& getExecCallback() const;
};

}//uit