#include <map>
#include <iostream>
#include "src/AllocatorFixed.h"
#include "src/factorial.h"
#include "src/MyList.h"

int main()
{
	try
	{
		/////
		std::map<int, int> newMap;
		for (int it = 0; it < 10; it++)
			newMap.insert(std::make_pair(it, factorial(it)));

		////
		std::map<int, int, std::less<int>, AllocatorFixed<std::pair<int, int>, 10> > newMapMy;
		for (int it = 0; it < 10; ++it)
		{
			std::cout << "it " << it << std::endl;
			newMapMy.insert(std::make_pair(it, factorial(it)));
			std::cout << "1" << std::endl;
		}
		for (const auto& i : newMapMy)
			std::cout << i.first << " " << i.second << "/n";
		std::cout << "OK" << std::endl;

		////
		MyList<int> myList;
		auto it = myList.begin_();
		for (int iter = 0; iter < 10; iter++)
			it = myList.insert_after(it, iter);

		////
		MyList<int, AllocatorFixed<int, 10> > myListAlloc;
		auto it1 = myListAlloc.begin_();
		for (int iter = 0; iter < 10; iter++)
			it1 = myListAlloc.insert_after(it1, iter);
		for (const auto& iter : myListAlloc)
			std::cout << iter << "/n";
	}
	catch (...)
	{
		std::cerr << "Exception" << std::endl;
	}

	return 0;
}
