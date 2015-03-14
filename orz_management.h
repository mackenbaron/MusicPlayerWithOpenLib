#ifndef ORZ_MANAGEMENT_H_INCLUDED
#define ORZ_MANAGEMENT_H_INCLUDED


#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"
#include "orz_complex_control.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	class ElementRoot: public BaseElement
	{
	public:
		ElementRoot();
		bool CreatElementRoot(const char *ControlName, const Rect &ElementRect);

	private:
		void DoContact();
		void DoContactReset();
		void DoDraw(const Rect& DrawRect);
	};

	class _Manager
	{
	public:
		_Manager();

		// ��ʼ���г���
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

		// �˳�����
		void QuitScene();

		// ��ȡ
		BaseElement& GerRoot();
		BaseElement& SearchRoot(const char *ControlName);

	private:
		// ��ͼ
		void PresentScene();
		void UpdateDebugScene();

		// ���ڱ�ʶѭ��
		bool is_loop;

		// �����
		RBTree rb_tree;
		
		// Ԫ�ظ��ڵ�
		ElementRoot element_root;

		// ��������
	};
}

#endif