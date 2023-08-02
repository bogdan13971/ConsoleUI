#pragma once

#include <conio.h>
#include <array>

namespace ui
{
	//Console Virtual Terminal size type
	using VTSizeType = unsigned short;

	constexpr auto SET_FORMAT		= "\033[30;47m";
	constexpr auto CLEAR_FORMAT		= "\033[0m";
	constexpr auto CLEAR_SCREEN		= "\033[2J";
	constexpr auto CLEAR_LINE		= "\033[0K";
	constexpr auto ALTERNATE_BUFFER	= "\033[?1049h";
	constexpr auto MAIN_BUFFER		= "\033[?1049l";
	constexpr auto HIDE_CURSOR		= "\033[?25l";
	constexpr auto SHOW_CURSOR		= "\033[?25h";
	constexpr auto RESET_CURSOR		= "\033[0;0H";
	constexpr auto CLEAR_TO_END		= "\033[0J";
	constexpr auto CURSOR_POSITION  = "\033[6n";
	constexpr auto BOLD_FORMAT      = "\033[1m";

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

	inline std::pair<VTSizeType, VTSizeType> getViewportSize()
	{
		std::pair<VTSizeType, VTSizeType> viewportSize;

		moveCursor(999, 999);
		std::cout << CURSOR_POSITION;

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

		std::cout << ui::RESET_CURSOR;
		if (sscanf_s(buffer, "[%d;%d", &width, &height) == 2)
		{
			viewportSize.first = static_cast<VTSizeType>(width);
			viewportSize.second = static_cast<VTSizeType>(height);
		}

		return viewportSize;
	}
}