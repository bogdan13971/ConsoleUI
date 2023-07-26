#pragma once

#include <string>
#include <list>

#include "Component.hpp"

namespace ui
{

class ConsoleLog : public Component
{
private:
	std::list<std::string> lines;
	unsigned char maxLines;

public:
	ConsoleLog()
		: ConsoleLog{ 10 }
	{}
	ConsoleLog(unsigned char maxLines)
		:maxLines{ maxLines }
	{}

	inline void setMaxLines(unsigned char maxLines)
	{
		this->maxLines = maxLines;
	}

	inline void addLine(std::string&& line)
	{
		lines.push_back(std::move(line));

		if (lines.size() > maxLines)
		{
			lines.pop_front();
		}
	}

	inline void clear()
	{
		lines.clear();
	}

	inline void print() override
	{
		std::cout << CLEAR_TO_END;
		std::cout << moveCursor(row - lines.size());

		for (const auto& line : lines)
		{
			std::cout << line << "\n";
		}
	}
};

}//ui