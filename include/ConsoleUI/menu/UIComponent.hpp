#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

#include "CVTHelper.hpp"

namespace ui
{

class UIComponent
{
protected:
	VTSizeType row = 0;
	VTSizeType col = 0;

public:
	~UIComponent() = default;
	/**
	 * @brief Set position for the virtual terminal
	*/
	void setPosition(VTSizeType row, VTSizeType col);
	/**
	 * @brief Print component at set position on the virtual terminal
	*/
	virtual void print() const;
};

class Title : public UIComponent
{
private:
	std::string label;

public:
	Title(std::string&& label);

	void print() const override;

	void alignToCenter(VTSizeType viewportWidth);
};

class Helper : public UIComponent
{
private:
	std::unordered_map<std::string, std::string> helpers;
	VTSizeType padding;
	VTSizeType maxTab;
	bool isActive;

public:
	Helper();

	void addHelper(const std::string& key, const std::string& command);

	void setMaxTab(VTSizeType maxTab);

	void setPadding(VTSizeType padding);

	void toggle();

	void print() const override;
};

class ConsoleLog : public UIComponent
{
private:
	std::list<std::string> lines;
	VTSizeType maxLines;

public:
	ConsoleLog();

	ConsoleLog(VTSizeType maxLines);

	void setMaxLines(VTSizeType maxLines);

	/**
	 * @brief Add or sink line
	*/
	void addLine(std::string line);

	void clear();

	void print() const override;
};

}// ui