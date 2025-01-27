#ifndef _ALLOCATOR_FIXED_H_
#define _ALLOCATOR_FIXED_H_

#include <cassert>
#include <array>
#include <algorithm>

template<typename T, int Size>
struct AllocatorFixed
{
	AllocatorFixed() = default;

	~AllocatorFixed() = default;

	using value_type = T;
	using pointer = T*;
    using const_pointer = const T*;
	using reference = T&;
    using const_reference = const T&;

	template<typename U>
    struct rebind
    {
        using other = AllocatorFixed<U, Size>;
    };

	/// Выделение памяти
	/// @param[in] n кол-во элементов
	/// @param[out] указатель на выделенную область
	T* allocate(std::size_t n)
	{
		if (n <= 0)
			return nullptr;
		else if (offsetThis + n > Size)
			throw std::bad_alloc();

		T *p = nullptr;
		if (offsetThis == 0) // Выделение новой памяти
		{
			ptr = static_cast<T*>(std::malloc(sizeof(T) * Size));
			if (!ptr)
				throw std::bad_alloc();
			
			for (; offsetThis < n; offsetThis++)
			{
				ptrAlloc[offsetThis] = ptr + offsetThis;
			}
			offsetThis--;
			p = ptr;
		}
		else // добавление элемента в уже выделенную память
		{
			auto it = std::find(ptrAlloc.begin(), ptrAlloc.end(), nullptr);
			assert(it != ptrAlloc.end());

			int index = 0;
			while (it != ptrAlloc.end())
			{
				index = std::distance(ptrAlloc.begin(), it);
				std::size_t numberFound = 1;
				for (; numberFound < n; ++numberFound)
				{
					if (ptrAlloc[index + numberFound] != nullptr)
					{
						it = std::find(it + 1, ptrAlloc.end(), nullptr);
						break;
					}
				}
				if (numberFound == n)
					break;
			}

			if (it == ptrAlloc.end()) // нет последовательных адресов
				throw std::bad_alloc();

			p = ptr + index;

			for (decltype(n) i = 0; i < n; ++i)
			{
				ptrAlloc[index + i] = ptr + index + i;
				++offsetThis;
			}
		}
		return p;
	}

		/// Освобождение памяти
	/// @param[in] p указатель на память
	/// @param[in] n кол-во элементов
	void deallocate(T *p, std::size_t n)
	{
		auto it = std::find(ptrAlloc.begin(), ptrAlloc.end(), p);
		assert(it != ptrAlloc.end());

		for (decltype(n) i = 0; i < n; ++i)
		{
			*it = nullptr;
			--offsetThis;
			++it;
			
		}
		if (offsetThis == 0)
		{
			std::free(ptr);
			ptr = nullptr;
		}
	}

	template<typename U, typename ...Args>
	void construct(U* p, Args &&...args)
	{
		new(p) U(std::forward<Args>(args)...);
	}

	void destroy(T* p)
	{
		p->~T();
	}

	const T* data() const
    {
        return ptr;
    }

	std::size_t size() const
	{
		return offsetThis;
	}

protected:
	T* ptr = nullptr;
	std::array<T*, Size> ptrAlloc = {}; // используемые адреса
	std::size_t offsetThis = 0;
};

#endif /* _ALLOCATOR_FIXED_H_ */
