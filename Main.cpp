#include <iostream>
#include "TMP_GenericAllocation.h"
int main()
{
	typedef Generic::ListOfTypes<int, double, char> list;
	list::FillUp();
	std::cout << *(int*)   Generic::Arr[0] << std::endl;
	std::cout << *(double*)Generic::Arr[1] << std::endl;
	std::cout << *(char*)  Generic::Arr[2] << std::endl;
	list::FreeAll();
}
