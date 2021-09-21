/*
*Author: Esperanza Barcia Ortiz
*Nov 2020
*/

/*
This project implements the Bubble Sort algorithm to sort a number array.
*/
/*
Implementar una funci�n que permita ordenar un array de n�meros de menor a mayor
* usando cualquier algoritmo de ordenaci�n(burbuja, inserci�n, etc., lo cual requiere documentarse).
* Dicha funci�n se implementar� en un archivo llamado sort.cpp.En otro archivo llamado main.cpp se implementar� la funci�n main()
* y se llamar� a la funci�n de ordenaci�n para probar que funciona correctamente(creando un array, llamando a la funci�n de ordenaci�n y
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