#include <iostream>
#include "TMP_GenericAllocation.h"
template<int N, typename T>
Generic::GenericTypeArray* Generic::_if<N, T>::Array()
{
	return
		(N <= 0x10)             ? Generic::Arr    :
		(N > 0x10 && N <= 0x20) ? Generic::BigArr :
		Generic::TooBigArr;
}
template<int N, int UpperLimit, typename __List>
void Generic::Fill<N, UpperLimit, __List>::fill()
{
	Generic::_if<UpperLimit, GenericTypeArray>::Array()[N] = malloc(sizeof(typename Generic::TypeAt<N, __List>::result));
	*(typename Generic::TypeAt<N, __List>::result*)Generic::_if<UpperLimit, Generic::GenericTypeArray>::Array()[N] = 255;
	Generic::Fill<N + 1, UpperLimit, __List>::fill();
}
template<int UpperLimit, typename __List>
void Generic::Fill <UpperLimit, UpperLimit, __List>::fill()
{
	Generic::_if<UpperLimit, Generic::GenericTypeArray>::Array()[UpperLimit] = malloc(sizeof(typename Generic::TypeAt<UpperLimit, __List>::result));
	*(typename Generic::TypeAt<UpperLimit, __List>::result*)Generic::_if<UpperLimit, Generic::GenericTypeArray>::Array()[UpperLimit] = 255;
}
template<int N, int UpperLimit, typename __List>
void Generic::Free<N, UpperLimit, __List>::freeIt()
{
	free(Generic::_if<UpperLimit, Generic::GenericTypeArray>::Array()[N]);
	Generic::Free<N + 1, UpperLimit, __List>::freeIt();
}
template<int UpperLimit, typename __List>
void Generic::Free <UpperLimit, UpperLimit, __List>::freeIt()
{
	free(Generic::_if<UpperLimit, Generic::GenericTypeArray>::Array()[UpperLimit]);
}
template<typename T, typename...U>
void Generic::ListOfTypes<T, U...>::FillUp()
{
	Generic::Fill<0, InternalListSize, InternalList>::fill();
}
template<typename T, typename...U>
void Generic::ListOfTypes<T, U...>::FreeAll()
{
	Generic::Free<0, InternalListSize, InternalList>::freeIt();
}
