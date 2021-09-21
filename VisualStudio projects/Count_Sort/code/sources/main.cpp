/*
*	Author:Esperanza Barcia Ortiz
*	APR 2021
*/
/*
	Count Sort algorithm implementation
*/

#include <Sorter.hpp>

#include <iostream>

using namespace Count_Sort;

int main()
{
	const int arraySize = 14;

	int myArray[arraySize]{ 0,25,3,7,72,8,7,54,11,8,7,89,73,2 };

	Sorter sorter;

	std::cout << " Array inicial" << std::endl;
	sorter.print(myArray, myArray + arraySize);

	sorter.Sort(myArray, myArray + arraySize);

	std::cout << " Array ordenado: " << std::endl;
	sorter.print(sorter.sortedList);

}