/*
*	Author:Esperanza Barcia Ortiz
*	APR 2021
*/

#include <vector>
using namespace std;

namespace Count_Sort
{
	class Sorter
	{

		/*
		* Max value of the array
		*/
		int maxValue = 0;

	public:

		/*
		* Final sorted list
		*/
		vector<int>sortedList;

		/*
		* Method to find the max value
		*/
		int FindMaxValue(int* arrayToSort, int* arrayEnd);

		/*
		* Algorithm
		*/
		void Sort(int* arrayToSort, int* arrayEnd);

		/*
		* List initialiser
		*/
		void InitialiseList(std::vector<int> list);

		/*
		* Prints array values
		*/
		void print(int* arrayToPrint, int* arrayEnd);

		/*
		* Prints list values
		*/
		void print(std::vector<int> list);

	};
}