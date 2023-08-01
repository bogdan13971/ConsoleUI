#include "UIComponent.hpp"

using namespace ui;

void UIComponent::setPosition(unsigned char row, unsigned char col)
{
	this->row = row;
	this->col = col;
}

void UIComponent::print() const
{
	std::cout << moveCursor(row, col);
}

Title::Title(std::string&& label)
	: label{ std::move(label) }
{}

void Title::print() const
{
	UIComponent::print();
	std::cout << BOLD_FORMAT;
	std::cout << label;
	std::cout << CLEAR_FORMAT;
}

void Title::alignToCenter(unsigned char width)
{
	setPosition(0, (width - label.size()) / 2);
}

Helper::Helper()
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

void Helper::addHelper(const std::string& key, const std::string& command)
{
	helpers.insert(std::make_pair(key, command));
}

void Helper::setMaxTab(unsigned char maxTab)
{
	this->maxTab = maxTab;
}

void Helper::setPadding(unsigned char padding)
{
	this->padding = padding;
}

void Helper::toggle()
{
	isActive = !isActive;
}

void Helper::print() const
{
	if (!isActive)
	{
		return;
	}

	UIComponent::print();
		
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
