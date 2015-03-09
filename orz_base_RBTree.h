#ifndef ORZ_BASE_RBTREE_H_INCLUDED
#define ORZ_BASE_RBTREE_H_INCLUDED

#include <string>

namespace Orz
{
    typedef std::string KeyType;
    enum RBTreeColor{RED, BLACK};

    struct RBTreeNode
    {
		~RBTreeNode()
		{
			delete p;
		}

        KeyType key;
        void *p;
        RBTreeColor color;
        RBTreeNode *left, *right, *parent;

        bool operator<(const RBTreeNode &node){ return key<node.key? true : false;}
        bool operator>(const RBTreeNode &node){ return key>node.key? true : false;}
    };

    // 红黑树
    class RBTree
    {
    public:
        RBTree();
        ~RBTree();

        // 释放树
        void Free();
        RBTreeNode* Free(RBTreeNode *x);

        // 搜寻
        RBTreeNode* Search(const KeyType &key);

        // 返回最大/最小
        RBTreeNode* Maxmum(RBTreeNode *x);
        RBTreeNode* Minmum(RBTreeNode *x);

		// 打印操作,调试用
		void _Print(void);
		void _Print(RBTreeNode*, int);

        // 后继
        RBTreeNode* Successor(RBTreeNode* x);

        // 插入
        void Insert(RBTreeNode* z);

        // 删除
        void Delete(RBTreeNode* z);

		// 查询大小
		bool Empty();
		int Size();

	private:
		// 更替操作
		void Transplant(RBTreeNode* y, RBTreeNode* x);

        // 旋转操作
        void LeftRotate(RBTreeNode* x);
        void RightRotate(RBTreeNode* x);

		// 修复操作
		void InsertFixUp(RBTreeNode* z);
		void DeleteFixUp(RBTreeNode* x);

        RBTreeNode* const null;
		RBTreeNode* root;
		RBTreeNode soild_null;

		int size;
    };
}
#endif // ORZ_BASE_RBTREE_H_INCLUDED
