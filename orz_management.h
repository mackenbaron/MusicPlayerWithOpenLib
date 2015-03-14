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

		// 开始运行程序
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

		// 退出场景
		void QuitScene();

		// 获取
		BaseElement& GerRoot();
		BaseElement& SearchRoot(const char *ControlName);

	private:
		// 绘图
		void PresentScene();
		void UpdateDebugScene();

		// 用于标识循环
		bool is_loop;

		// 红黑树
		RBTree rb_tree;
		
		// 元素根节点
		ElementRoot element_root;

		// 错误处理函数
	};
}

#endif