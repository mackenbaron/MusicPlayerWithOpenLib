#ifndef ORZ_BASE_LIST_H_INCLUDED
#define ORZ_BASE_LIST_H_INCLUDED

namespace Orz
{
	class ArrayListNode
	{
		void *p;
	};

	class BaseArrayList
	{
		ArrayListNode *head, *tril;
		bool Insert();
		bool Delete();
		ArrayListNode& operator[](int Index);
		int size;
	};
}

#endif