#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

#include "ConsoleCommands.hpp"

namespace ui
{

class UIComponent
{
protected:
	unsigned char row = 0;
	unsigned char col = 0;

public:
	void setPosition(unsigned char row, unsigned char col);
	virtual void print() const;
};

class Title : public UIComponent
{
private:
	std::string label;

public:
	Title(std::string&& label);

	void print() const override;

	void alignToCenter(unsigned char width);
};

class Helper : public UIComponent
{
private:
	std::unordered_map<std::string, std::string> helpers;
	unsigned char padding;
	unsigned char maxTab;
	bool isActive;

public:
	Helper();

	void addHelper(const std::string& key, const std::string& command);

	void setMaxTab(unsigned char maxTab);

	void setPadding(unsigned char padding);

	void toggle();

	void print() const override;
};

class ConsoleLog : public UIComponent
{
private:
	std::list<std::string> lines;
	unsigned char maxLines;

public:
	ConsoleLog();

	ConsoleLog(unsigned char maxLines);

	void setMaxLines(unsigned char maxLines);

	void addLine(std::string&& line);

	void clear();

	void print() const override;
};

}// ui