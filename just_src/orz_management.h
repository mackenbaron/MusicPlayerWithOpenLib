#ifndef ORZ_MANAGEMENT_H_INCLUDED
#define ORZ_MANAGEMENT_H_INCLUDED

#include "orz_root.h"

namespace Orz
{
	class Management: public Root
	{
	private:


	public:

		// ��ʼ���г���
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

	private:

		// 
	};
}

#endif