#pragma once

#include <utils/types.hpp>
#include <utils/non_owning_ptr.hpp>

namespace ui
{

class Item;

/**
 * @brief Item handle created only by a menu
*/
class ItemHandle
{
private:
	utils::non_owning_ptr<Item> impl;

private:
	ItemHandle() = delete;

public:
	ItemHandle(const utils::non_owning_ptr<Item>& impl);

	/**
	 * @brief Prints the label on stdout at the current cursor position
	*/
	void print() const;

	/**
	 * @brief Execute the registered callback
	*/
	void execute();

	/**
	 * @brief Replace the current label with the label returned by the update callback
	*/
	void update();

	void setExecCallback(const ExecCallback& cb);

	void setUpdateCallback(const UpdateCallback& cb);

	const ExecCallback& getExecCallback() const;
};

}//uit