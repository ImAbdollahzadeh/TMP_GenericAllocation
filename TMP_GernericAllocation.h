#include <iostream>
namespace Generic
{
	struct Empty {};
	typedef void* GenericTypeArray;
	GenericTypeArray Arr[0x10]       = { nullptr };
	GenericTypeArray BigArr[0x20]    = { nullptr };
	GenericTypeArray TooBigArr[0x30] = { nullptr };
	template<int N, typename T> struct _if
	{
		static GenericTypeArray* Array()
		{
			return
				(N <= 0x10)             ? Arr :
				(N > 0x10 && N <= 0x20) ? BigArr :
				TooBigArr;
		}
	};

	template<typename T, typename...U> struct List {
		constexpr static int size = 1 + List<U...>::size;
		typedef T head;
		typedef List<U...> tail;
	};
	template<typename T> struct List < T > {
		constexpr static int size = 0;
		typedef T head;
		typedef Empty tail;
	};

	template<int M, typename __List> struct TypeAt {
		typedef typename __List::head head;
		typedef typename __List::tail tail;
		typedef typename TypeAt<M - 1, tail>::result result;
	};
	template<typename __List> struct TypeAt < 0, __List > {
		typedef typename __List::head result;
	};

	template<int N, int NN, typename __List> struct Fill {
		static void fill()
		{
			_if<NN, GenericTypeArray>::Array()[N] = malloc(sizeof(typename TypeAt<N, __List>::result));
			*(typename TypeAt<N, __List>::result*)_if<NN, GenericTypeArray>::Array()[N] = 255;
			Fill<N + 1, NN, __List>::fill();
		}
	};
	template<int NN, typename __List> struct Fill < NN, NN, __List > {
		static void fill()
		{
			_if<NN, GenericTypeArray>::Array()[NN] = malloc(sizeof(typename TypeAt<NN, __List>::result));
			*(typename TypeAt<NN, __List>::result*)_if<NN, GenericTypeArray>::Array()[NN] = 255;
		}
	};

	template<int N, int NN, typename __List> struct Free {
		static void freeIt()
		{
			free(_if<NN, GenericTypeArray>::Array()[N]);
			Free<N + 1, NN, __List>::freeIt();
		}
	};
	template<int NN, typename __List> struct Free < NN, NN, __List > {
		static void freeIt()
		{
			free(_if<NN, GenericTypeArray>::Array()[NN]);
		}
	};
	template<typename T, typename...U> class ListOfTypes {
	private:
		typedef List<T, U...> InternalList;
		constexpr static int InternalListSize = InternalList::size;
	public:
		static void FillUp()
		{
			Fill<0, InternalListSize, InternalList>::fill();
		}
		static void FreeAll()
		{
			Free<0, InternalListSize, InternalList>::freeIt();
		}
	};
}