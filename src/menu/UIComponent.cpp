#include "menu/UIComponent.hpp"

using namespace ui;

void UIComponent::setPosition(VTSizeType row_, VTSizeType col_)
{
	row = row_;
	col = col_;
}

void UIComponent::print() const
{
	moveCursor(row, col);
}

Title::Title(std::string&& label)
	: label{ std::move(label) }
{}

void Title::print() const
{
	UIComponent::print();
	executeCommand(CVTCommand::BOLD_FORMAT);
	std::cout << label;
	executeCommand(CVTCommand::CLEAR_FORMAT);
}

void Title::alignToCenter(VTSizeType width)
{
	setPosition(0, (width - static_cast<VTSizeType>(label.size())) / 2);
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

void Helper::setMaxTab(VTSizeType maxTab_)
{
	maxTab = maxTab_;
}

void Helper::setPadding(VTSizeType padding_)
{
	padding = padding_;
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
		
	VTSizeType tab = 0;
	VTSizeType index = 0;
	VTSizeType lineRow = 0;

	for (auto& pair : helpers)
	{
		if (index == 0)
		{
			moveCursor(row + lineRow, 
									padding / 2 - static_cast<VTSizeType>(pair.first.size()));
		}
		else
		{
			moveCursor(row + lineRow, 
									padding / 2 + padding * index - static_cast<VTSizeType>(pair.first.size()));
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


ConsoleLog::ConsoleLog()
	: ConsoleLog{ 10 }
{}

ConsoleLog::ConsoleLog(VTSizeType maxLines_)
	:maxLines{ maxLines_ }
{}

void ConsoleLog::setMaxLines(VTSizeType maxLines_)
{
	maxLines = maxLines_;
}

void ConsoleLog::addLine(std::string line)
{
	lines.push_back(std::move(line));

	if (lines.size() > maxLines)
	{
		lines.pop_front();
	}
}

void ConsoleLog::clear()
{
	lines.clear();
}

void ConsoleLog::print() const
{
	executeCommand(CVTCommand::CLEAR_TO_END);
	moveCursor(row - static_cast<VTSizeType>(lines.size()), 0);

	for (const auto& line : lines)
	{
		std::cout << line << "\n";
	}
}