#pragma once

#include <functional>
#include <iostream>
#include <string>

#include "../utils/types.hpp"

namespace ui
{

class Item
{
private:
	std::string label;
	ExecCallback execCallback;
	UpdateCallback updateCallback;

public:
	Item(std::string&& label,
		const ExecCallback& execCB = NO_OP_CB)
		: Item{ std::move(label), execCB, [&]() {return this->label; } }
	{}

	Item(std::string&& label,
		const ExecCallback& execCB,
		const UpdateCallback& updateCB)
		: label{ std::move(label) },
		execCallback{ execCB },
		updateCallback{updateCB}
	{};

	Item(const Item&) = delete;
	Item& operator=(const Item&) = delete;

	virtual ~Item() 
	{}

public:
	virtual void print() const
	{
		std::cout << label << "\n";
	}

	virtual void execute()
	{
		execCallback();
	}

	virtual void update()
	{
		label = updateCallback();
	}

	void setExecCallback(const ExecCallback& cb)
	{
		execCallback = cb;
	}

	void setUpdateCallback(const UpdateCallback& cb)
	{
		updateCallback = cb;
	}

	const ExecCallback& getExecCallback() const
	{
		return execCallback;
	}

public:
	friend class SubMenu;
};

}//uit