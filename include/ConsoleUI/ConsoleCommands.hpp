#pragma once

#include <conio.h>

namespace ui
{
	//Virtual Terminal size type
	using VTSizeType = unsigned char;

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

	constexpr const char* moveCursor(VTSizeType rows, VTSizeType cols)
	{
		constexpr char* format = "\033[000;000H";

		format[3] = rows / 100;
		format[4] = (rows / 10) % 10;
		format[5] = rows % 10;

		format[7] = cols / 100;
		format[8] = (cols / 10) % 10;
		format[9] = cols % 10;

		return format;
	}

	inline std::pair<VTSizeType, VTSizeType> getViewportSize()
	{
		std::pair<VTSizeType, VTSizeType> viewportSize;
		constexpr VTSizeType maxWidth = static_cast<VTSizeType>(999);
		constexpr VTSizeType maxHeight = maxWidth;

		std::cout << moveCursor(maxWidth, maxHeight);
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