#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

#include "ConsoleCommands.hpp"

namespace ui
{

class Component
{
protected:
	unsigned char row = 0;
	unsigned char col = 0;

public:
	inline void setPosition(unsigned char row, unsigned char col)
	{
		this->row = row;
		this->col = col;
	}

	inline virtual void print()
	{
		std::cout << moveCursor(row, col);
	}
};

class Title : public Component
{
private:
	std::string label;

public:
	Title(const std::string& label)
		: label{ label }
	{}

	inline void print() override
	{
		Component::print();
		std::cout << BOLD_FORMAT;
		std::cout << label;
		std::cout << CLEAR_FORMAT;
	}
};

class Helper : public Component
{
private:
	std::unordered_map<std::string, std::string> helpers;
	unsigned char padding;
	unsigned char maxTab;
	bool isActive;

public:
	Helper()
		: helpers{
			{"Arrows", "Move"},
			{"ENTER" , "Execute"},
			{"q"     , "Quit"},
			{"x"     , "Back"},
			{"h"     , "Toggle Help"}
		},
		padding{20},
		maxTab{5},
		isActive{true}
	{}

	inline void addHelper(const std::string& key, const std::string& command)
	{
		helpers.insert(std::make_pair(key, command));
	}

	inline void setMaxTab(unsigned char maxTab)
	{
		this->maxTab = maxTab;
	}

	inline void setPadding(unsigned char padding)
	{
		this->padding = padding;
	}

	inline void toggle()
	{
		isActive = !isActive;
	}

	inline void print() override
	{
		if (!isActive)
		{
			return;
		}

		Component::print();
		
		unsigned char tab = 0;
		unsigned char index = 0;
		unsigned char lineRow = 0;

		for (auto& pair : helpers)
		{
			if (index == 0)
			{
				std::cout << moveCursor(row + lineRow, padding / 2 - pair.first.size());
			}
			else
			{
				std::cout << moveCursor(row + lineRow, padding / 2 + padding * index - pair.first.size());
			}

			std::cout << pair.first << ": " << pair.second;

			index++;
			tab++;

			if (tab == maxTab)
			{
				std::cout << "\n";
				index=0;
				tab = 0;
				lineRow++;
			}
		}
	}
};

}//uit