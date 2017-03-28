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
template<int N, int NN, typename __List>
void Generic::Fill<N, NN, __List>::fill()
{
	Generic::_if<NN, GenericTypeArray>::Array()[N] = malloc(sizeof(typename Generic::TypeAt<N, __List>::result));
	*(typename Generic::TypeAt<N, __List>::result*)Generic::_if<NN, Generic::GenericTypeArray>::Array()[N] = 255;
	Generic::Fill<N + 1, NN, __List>::fill();
}
template<int NN, typename __List>
void Generic::Fill < NN, NN, __List >::fill()
{
	Generic::_if<NN, Generic::GenericTypeArray>::Array()[NN] = malloc(sizeof(typename Generic::TypeAt<NN, __List>::result));
	*(typename Generic::TypeAt<NN, __List>::result*)Generic::_if<NN, Generic::GenericTypeArray>::Array()[NN] = 255;
}
template<int N, int NN, typename __List>
void Generic::Free<N, NN, __List>::freeIt()
{
	free(Generic::_if<NN, Generic::GenericTypeArray>::Array()[N]);
	Generic::Free<N + 1, NN, __List>::freeIt();
}
template<int NN, typename __List>
void Generic::Free < NN, NN, __List >::freeIt()
{
	free(Generic::_if<NN, Generic::GenericTypeArray>::Array()[NN]);
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