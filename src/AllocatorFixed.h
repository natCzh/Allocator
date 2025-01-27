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
		std::cout << "allocate" << std::endl;
		std::cout << "n = " << n << ",";
		if (n <= 0)
			return nullptr;
		else if (offsetThis + n > Size)
		{
			std::cout << "offsetThis + n = " << offsetThis + n << ",";
			std::cout << "Size = " << Size << std::endl;
			throw std::bad_alloc();
		}

		std::cout << "offsetThis = " << offsetThis << std::endl;

		T *p = nullptr;
		if (offsetThis == 0) // Выделение новой памяти
		{
			ptr = static_cast<T*>(std::malloc(sizeof(T) * Size));
			if (!ptr)
				throw std::bad_alloc();
			
			for (; offsetThis < n; offsetThis++)
			{
				std::cout << "offsetThis in round = " << offsetThis << std::endl;
				ptrAlloc[offsetThis] = ptr + offsetThis;
			}
			offsetThis--;
			p = ptr;
			std::cout << "offsetThis = " << offsetThis << std::endl;
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

			std::cout << "allocate2" << std::endl;
			std::cout << "index " << index << std::endl;

			for (decltype(n) i = 0; i < n; ++i)
			{
				ptrAlloc[index + i] = ptr + index + i;
				++offsetThis;
			}

			std::cout << "ptr" << ptr << std::endl;
			std::cout << "p" << p << std::endl;
			std::cout << "offsetThis" << offsetThis << std::endl;
			

			std::cout << "allocate3" << std::endl;
		}
		return p;
	}

		/// Освобождение памяти
	/// @param[in] p указатель на память
	/// @param[in] n кол-во элементов
	void deallocate(T *p, std::size_t n)
	{
		std::cout << "deallocate" << std::endl;
		std::cout << "p " << p << std::endl;
		std::cout << "n " << n << std::endl;

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
			std::cout << "deallocate 1" << std::endl;
			std::cout << "ptr " << ptr << std::endl;
			std::free(ptr);
			ptr = nullptr;
		}
	}

	template<typename U, typename ...Args>
	void construct(U* p, Args &&...args)
	{
		std::cout << "construct" << std::endl;
		new(p) U(std::forward<Args>(args)...);
		std::cout << "construct1" << std::endl;
	}

	void destroy(T* p)
	{
		std::cout << "destroy" << std::endl;
		p->~T();
	}





	const T* data() const
    {
		std::cout << "data" << std::endl;
        return ptr;
    }

	std::size_t size() const
	{
		std::cout << "size" << std::endl;
		return offsetThis;
	}

protected:
	T* ptr = nullptr;
	std::array<T*, Size> ptrAlloc = {}; // используемые адреса
	std::size_t offsetThis = 0;
};

#endif /* _ALLOCATOR_FIXED_H_ */
