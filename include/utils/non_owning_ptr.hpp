#pragma once

#include <memory>
#include <cassert>

namespace utils
{

/**
 * @brief Simple wrapper over a non null, non owning pointer
*/
template<class T>
class non_owning_ptr
{
private:
	T* ptr;

public:
	non_owning_ptr() = delete;

	non_owning_ptr(T* ptr)
		: ptr{ ptr }
	{
		assert(ptr != nullptr);
	}

	T* operator->()
	{
		return ptr;
	}

	const T* operator->() const
	{
		return ptr;
	}

	T& operator*()
	{
		return *ptr;
	}

	const T& operator*() const
	{
		return *ptr;
	}
};

}// utils