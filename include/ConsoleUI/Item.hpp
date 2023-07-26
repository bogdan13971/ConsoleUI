#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace ui
{

class SubMenu;

class Item
{
private:
	using ExecCallback = std::function<void()>;
	using UpdateCallback = std::function<std::string()>;

private:
	std::string label;
	ExecCallback execCallback;

	bool isDirty;
	UpdateCallback updateCallback;

private:
	Item(const std::string& label)
		: label{ label },
		execCallback{[]() {}},
		updateCallback{ []() {return "";}},
		isDirty{false}
	{};

	~Item()
	{}

public:
	inline virtual void print()
	{
		if (isDirty)
		{
			label = updateCallback();
			isDirty = false;
		}

		std::cout << label;
	}

	inline virtual void execute()
	{
		execCallback();
	}

	inline void setExecCallback(const ExecCallback& cb)
	{
		execCallback = cb;
	}

	inline void setUpdateCallback(const UpdateCallback& cb)
	{
		updateCallback = cb;
	}

	inline virtual void setDirty()
	{
		isDirty = true;
	}

public:
	friend class SubMenu;
};

}//uit