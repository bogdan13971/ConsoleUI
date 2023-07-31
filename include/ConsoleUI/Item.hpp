#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace ui
{

class Item
{
public:
	using ExecCallback = std::function<void()>;
	using UpdateCallback = std::function<std::string()>;

	static const ExecCallback NO_OP_CB;

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

public:
	Item(const Item&) = delete;
	Item& operator=(const Item&) = delete;

	virtual ~Item() 
	{}

public:
	inline virtual void print() const
	{
		std::cout << label << "\n";
	}

	inline virtual void execute() const
	{
		execCallback();
	}

	inline virtual void update()
	{
		label = updateCallback();
	}

	inline void setExecCallback(const ExecCallback& cb)
	{
		execCallback = cb;
	}

	inline void setUpdateCallback(const UpdateCallback& cb)
	{
		updateCallback = cb;
	}

	inline const ExecCallback& getExecCallback() const
	{
		return execCallback;
	}

public:
	friend class SubMenu;
};

}//uit