/*
*	Author:Esperanza Barcia Ortiz
*	APR 2021
*/

#include "Sorter.hpp"

#include <vector>
#include <iterator>
#include <iostream>

int Count_Sort::Sorter::FindMaxValue(int* arrayToSort, int* arrayEnd)
{

	/**Saves the maximun value found
	*/
	for (int* i = arrayToSort; i != arrayEnd; i++)
	{
		if (*i > maxValue)
		{
			maxValue = *i;
		}
	}

	return maxValue;
}

void Count_Sort::Sorter::Sort(int* arrayToSort, int* arrayEnd)
{
	std::cout << std::endl << " Ordenando array..." << std::endl << std::endl;

	FindMaxValue(arrayToSort, arrayEnd);

	//if the max value is 100, the list size will be 101
	maxValue += 1;

	//Creates a list with the max value size
	//The positions will save the number of times that number appears
	//For example: position 5 will save the number of times 5 appears
	std::vector<int> countList(maxValue);

	//Initialise the list to 0
	InitialiseList(countList);

	// Each time a number appears, +1 to that position on the count list.
	for (int* i = arrayToSort; i != arrayEnd; i++)
	{
		//Example: 9 appears 1 time on the array, on position 9 in the count list there will be a 1
		int pos = (*i);
		countList[pos]++;
	}

	//Fills the list, now sorted
	for (int i = 0; i < countList.size(); i++)
	{
		//Following the count list, we add a value to the list the number of times it appears
		for (int j = 0; j < countList[i]; j++)
		{
			sortedList.push_back(i);
		}
	}
}

void Count_Sort::Sorter::InitialiseList(std::vector<int> list)
{
	for (size_t i = 0; i < list.size(); i++)
	{
		list[i] = 0;
	}
}

void Count_Sort::Sorter::print(int* arrayToPrint, int* arrayEnd)
{
	std::cout << std::endl;
	std::cout << "[ ";

	for (int* i = arrayToPrint; i != arrayEnd; i++)
	{
		std::cout << " " << *i << " ";
	}
	std::cout << " ]";
	std::cout << std::endl;

}

void Count_Sort::Sorter::print(std::vector<int> list)
{
	std::cout << std::endl;
	std::cout << "[ ";

	for (size_t i = 0; i < list.size(); i++)
	{
		std::cout << " " << list[i] << " ";
	}
	std::cout << " ]";
	std::cout << std::endl;
}