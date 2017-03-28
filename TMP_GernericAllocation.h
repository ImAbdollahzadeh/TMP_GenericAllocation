#pragma once
#ifndef _TMPGENERICALLOCATION_H_
#define _TMPGENERICALLOCATION_H_
namespace Generic
{
	struct Empty {};
	typedef void* GenericTypeArray;
	GenericTypeArray Arr[0x10]       = { nullptr };
	GenericTypeArray BigArr[0x20]    = { nullptr };
	GenericTypeArray TooBigArr[0x30] = { nullptr };
	template<int N, typename T> struct _if
	{
		static GenericTypeArray* Array();
	};

	template<typename T, typename...U> struct List
	{
		constexpr static int size = 1 + List<U...>::size;
		typedef T head;
		typedef List<U...> tail;
	};
	template<typename T> struct List <T>
	{
		constexpr static int size = 0;
		typedef T head;
		typedef Empty tail;
	};

	template<int M, typename __List> struct TypeAt
	{
		typedef typename __List::head head;
		typedef typename __List::tail tail;
		typedef typename TypeAt<M - 1, tail>::result result;
	};
	template<typename __List> struct TypeAt <0, __List>
	{
		typedef typename __List::head result;
	};

	template<int N, int UpperLimit, typename __List> struct Fill
	{
		static void fill();
	};
	template<int UpperLimit, typename __List> struct Fill <UpperLimit, UpperLimit, __List>
	{
		static void fill();
	};

	template<int N, int UpperLimit, typename __List> struct Free
	{
		static void freeIt();
	};
	template<int UpperLimit, typename __List> struct Free <UpperLimit, UpperLimit, __List>
	{
		static void freeIt();
	};
	template<typename T, typename...U> class ListOfTypes
	{
		private:
			typedef List<T, U...> InternalList;
			constexpr static int InternalListSize = InternalList::size;
		public:
			static void FillUp();
			static void FreeAll();
	};
}
#endif
