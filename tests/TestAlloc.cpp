#include <list>

#include "gtest/gtest.h"
// #include "gmock/gmock.h"

#include "AllocatorFixed.h"

TEST (TestAlloc, testAllocate)
{
	constexpr int n = 10;
	AllocatorFixed<int, n> alloc;

	/*EXPECT_EQ(alloc.allocate(0), nullptr);
	EXPECT_THROW(alloc.allocate(n + 1), std::bad_alloc);

	for (int it = 0; it < n; it++)
		EXPECT_NO_THROW(alloc.allocate(1));
	EXPECT_THROW(alloc.allocate(1), std::bad_alloc);*/
}