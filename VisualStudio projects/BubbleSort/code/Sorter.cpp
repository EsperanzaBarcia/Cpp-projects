/*
*Author: Esperanza Barcia Ortiz
*Nov 2020
*/
#include "Sorter.hpp"
#include <iostream>

using namespace std;

namespace Utils
{
	void Sorter::BubbleSort(int arr[], int size)
	{
		cout << endl << "Sorting array from smallest to largest... " << endl;
		int aux;

		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 1; j < size; ++j)
			{
				if (arr[j] < arr[j - 1])
				{
					aux = arr[j];
					arr[j] = arr[j - 1];
					arr[j - 1] = aux;
				}

			}
		}
		cout << endl;
	}

	void Sorter::BubbleSortPointer(int* begin, int* size)
	{
		cout << endl << "Sorting array from smallest to largest... " << endl;
		int aux;

		for (int* i = begin; i < size; ++i)
		{
			for (int* j = begin; j < size; ++j)
			{
				if (*i < *j)
				{
					aux = *i;
					*i = *j;
					*j = aux;
				}
			}
		}

		cout << endl;
	}

	void Sorter::Print(const int arr[], int size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			cout << arr[i] << " ";
		}
	}

	void Sorter::PrintPointers(int* begin, int* end)
	{
		for (; begin < end; ++begin)
		{
			cout << *begin << " ";
		}
	}
}