/*
*Author: Esperanza Barcia Ortiz
*Nov 2020
*/

/*
This project implements the Bubble Sort algorithm to sort a number array.
*/
/*
Implementar una función que permita ordenar un array de números de menor a mayor
* usando cualquier algoritmo de ordenación(burbuja, inserción, etc., lo cual requiere documentarse).
* Dicha función se implementará en un archivo llamado sort.cpp.En otro archivo llamado main.cpp se implementará la función main()
* y se llamará a la función de ordenación para probar que funciona correctamente(creando un array, llamando a la función de ordenación y
	* escribiendo en la consola el resultado).
*
*/

#include "Sorter.hpp"
#include <iostream>
using namespace Utils;
using namespace std;

int main()
{
	int arr[] = { 45,75,3,9,2,44,10,8,98,2 };

	int size = sizeof(arr) / sizeof(int);

	Sorter sorter;
	cout << endl << "Input array:  " << endl;

	//prints the input array
	sorter.PrintPointers(arr, arr + size);

	sorter.BubbleSortPointer(arr, arr + size);

	cout << endl << "Sorted array:  " << endl;
	sorter.PrintPointers(arr, arr + size);

	return 0;
}