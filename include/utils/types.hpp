#pragma once

#include <string>
#include <functional>

namespace ui
{
	using ExecCallback = std::function<void()>;
	using UpdateCallback = std::function<std::string()>;
	using BackCallback = std::function<void()>;

	static const ExecCallback NO_OP_CB = []() {};
}