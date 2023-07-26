#pragma once

#include <functional>
#include <unordered_map>

enum class EVENT_TYPE
{
	UP, DOWN, ENTER, BACK
};

class EventListener
{
private:
	std::unordered_map<EVENT_TYPE, std::function<void()>> actionMap;
	std::unordered_map<char, std::function<void()>> keyPressMap;

public:
	EventListener()
	{
		const auto noOp = []() {};
		actionMap.insert({ EVENT_TYPE::UP, noOp });
		actionMap.insert({ EVENT_TYPE::DOWN, noOp });
		actionMap.insert({ EVENT_TYPE::ENTER, noOp });
		actionMap.insert({ EVENT_TYPE::BACK, noOp });
	}

	inline void registerEventHandler(EVENT_TYPE eventType, const std::function<void()>& handler)
	{
		actionMap.insert({ eventType, handler });
	}

	inline void registerKeyPressEventHandler(char key, const std::function<void()>& handler)
	{
		keyPressMap.insert({ key, handler });
	}

	inline void handleEvent(EVENT_TYPE eventType)
	{
		actionMap.at(eventType).operator()();
	}

	inline void handleKeyEvent(char key)
	{
		keyPressMap.at(key).operator()();
	}
};