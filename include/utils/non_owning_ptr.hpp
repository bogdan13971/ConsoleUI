#pragma once

#include <memory>
#include <cassert>

template<class T>
class non_owning_ptr
{
private:
	T* ptr;

public:
	non_owning_ptr() = delete;

private:
	non_owning_ptr(T* ptr)
		: ptr{ ptr }
	{
		assert(ptr != nullptr);
	}

public:
	template<class U>
	static non_owning_ptr<T> create(const std::unique_ptr<U>& ptr)
	{
		return non_owning_ptr<T>(dynamic_cast<T*>(ptr.get()));
	}

	template<class U>
	static non_owning_ptr<T> create(const std::shared_ptr<U>& ptr)
	{
		return non_owning_ptr<T>(dynamic_cast<T*>(ptr.get()));
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

public:
	template<class U>
	friend non_owning_ptr<T> make_non_owning(const std::unique_ptr<U>&);

	template<class U>
	friend non_owning_ptr<T> make_non_owning(const std::shared_ptr<U>&);
};

template<class T, class U>
non_owning_ptr<T> make_non_owning(const std::unique_ptr<U>& ptr)
{
	return non_owning_ptr<T>::create(ptr);
}

template<class T, class U>
non_owning_ptr<T> make_non_owning(const std::shared_ptr<U>& ptr)
{
	return non_owning_ptr<T>::create(ptr);
}