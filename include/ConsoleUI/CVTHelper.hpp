#pragma once

#include <conio.h>
#include <array>
#include <iostream>
#include <unordered_map>

namespace ui
{
	//Console Virtual Terminal size type
	using VTSizeType = unsigned short;

	enum class CVTCommand
	{
		SET_FORMAT,
		CLEAR_FORMAT,
		CLEAR_SCREEN,
		CLEAR_LINE,
		ALTERNATE_BUFFER,
		MAIN_BUFFER,
		HIDE_CURSOR,
		SHOW_CURSOR,
		RESET_CURSOR,
		CLEAR_TO_END,
		CURSOR_POSITION,
		BOLD_FORMAT
	};

	static const std::unordered_map<CVTCommand, std::string> CommandOPCode =
	{
		{CVTCommand::SET_FORMAT,		"\033[30;47m"},
		{CVTCommand::CLEAR_FORMAT,		"\033[0m"},
		{CVTCommand::CLEAR_SCREEN,		"\033[2J"},
		{CVTCommand::CLEAR_LINE,		"\033[0K"},
		{CVTCommand::ALTERNATE_BUFFER,	"\033[?1049h"},
		{CVTCommand::MAIN_BUFFER,		"\033[?1049l"},
		{CVTCommand::HIDE_CURSOR,		"\033[?25l"},
		{CVTCommand::SHOW_CURSOR,		"\033[?25h"},
		{CVTCommand::RESET_CURSOR,		"\033[0;0H"},
		{CVTCommand::CLEAR_TO_END,		"\033[0J"},
		{CVTCommand::CURSOR_POSITION,	"\033[6n"},
		{CVTCommand::BOLD_FORMAT,		"\033[1m"}
	};

	//Executes the command by printing it to the current terminal
	inline void executeCommand(CVTCommand command)
	{
		std::cout << CommandOPCode.at(command);
	}

	//Compile-time generation of the Virtual Terminal Command to move cursor at (row, col)
	constexpr std::array<char, 11> generateMoveCursorCommand(VTSizeType row, VTSizeType col)
	{
		std::array<char, 11> format = { 
			'\033',
			'[', 
			'0' + static_cast<char>(row / 100), 
			'0' + static_cast<char>((row / 10) % 10), 
			'0' + static_cast<char>(row % 10), 
			';', 
			'0' + static_cast<char>(col / 100), 
			'0' + static_cast<char>((col / 10) % 10),
			'0' + static_cast<char>(col % 10), 
			'H' };
		
		return format;
	}

	//Move cursor to (row, col)
	inline void moveCursor(VTSizeType rows, VTSizeType cols)
	{
		std::cout << generateMoveCursorCommand(rows, cols).data();
	}

	/**
	 * @brief Compute the console virtual terminal viewport size
	 * @return pair of width - height
	*/
	inline std::pair<VTSizeType, VTSizeType> getViewportSize()
	{
		std::pair<VTSizeType, VTSizeType> viewportSize = { 0, 0 };

		moveCursor(999, 999);
		executeCommand(CVTCommand::CURSOR_POSITION);

		char buffer[10] = { 0 };
		int pos = 0;

		int c = _getch();
		while (c != 'R')
		{
			if (c == EOF)
			{
				break;
			}

			if (isprint(c))
			{
				buffer[pos++] = static_cast<char>(c);
			}

			c = _getch();
		}

		int width = 0;
		int height = 0;

		executeCommand(CVTCommand::RESET_CURSOR);
		if (sscanf_s(buffer, "[%d;%d", &width, &height) == 2)
		{
			viewportSize.first = static_cast<VTSizeType>(width);
			viewportSize.second = static_cast<VTSizeType>(height);
		}

		return viewportSize;
	}
}