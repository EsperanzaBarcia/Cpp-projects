/*
*Author: Esperanza Barcia Ortiz
*Nov 2020
*/
#pragma once

namespace Utils
{
	class Sorter
	{
		//without pointer
	public:
		void BubbleSort(int arr[], int size);

		void Print(const int arr[], int size);

		//with pointers
	public:
		void BubbleSortPointer(int* begin, int* size);

		void PrintPointers(int* begin, int* end);

	};
}

