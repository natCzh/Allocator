#include <map>
#include <iostream>
#include "src/AllocatorFixed.h"
#include "src/factorial.h"


int main()
{
	try
	{
		/////
		/*std::map<int, int> newMap;
		for (int it = 0; it < 10; it++)
			newMap.insert(std::make_pair(it, factorial(it)));*/

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
	}
	catch (...)
	{
		std::cerr << "Exception" << std::endl;
	}

	return 0;
}
