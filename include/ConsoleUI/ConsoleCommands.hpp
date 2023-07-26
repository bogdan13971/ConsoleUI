#pragma once

#include <conio.h>

namespace ui
{
	static const char* SET_FORMAT		= "\033[30;47m";
	static const char* CLEAR_FORMAT		= "\033[0m";
	static const char* CLEAR_SCREEN		= "\033[2J";
	static const char* CLEAR_LINE		= "\033[0K";
	static const char* ALTERNATE_BUFFER	= "\033[?1049h";
	static const char* MAIN_BUFFER		= "\033[?1049l";
	static const char* HIDE_CURSOR		= "\033[?25l";
	static const char* SHOW_CURSOR		= "\033[?25h";
	static const char* RESET_CURSOR		= "\033[0;0H";
	static const char* CLEAR_TO_END		= "\033[0J";
	static const char* CURSOR_POSITION  = "\033[6n";
	static const char* BOLD_FORMAT      = "\033[1m";

	inline std::string moveCursor(unsigned char rows, unsigned char cols = 0)
	{
		return "\033[" + std::to_string(rows) + ";" + std::to_string(cols) + "H";
	}

	inline std::pair<unsigned char, unsigned char> getViewportSize()
	{
		std::pair<unsigned char, unsigned char> viewportSize;

		std::cout << moveCursor(999, 999);
		std::cout << CURSOR_POSITION;

		char buffer[10] = { 0 };
		int pos = 0;

		char c = _getch();
		while (c != 'R')
		{
			if (c == EOF)
			{
				break;
			}

			if (isprint(c))
			{
				buffer[pos++] = c;
			}

			c = _getch();
		}

		int width = 0;
		int height = 0;

		std::cout << ui::RESET_CURSOR;
		if (sscanf_s(buffer, "[%d;%d", &width, &height) == 2)
		{
			viewportSize.first = width;
			viewportSize.second = height;
		}

		return viewportSize;
	}
}