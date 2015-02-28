#ifndef ORZ_BASE_RBTREE_H_INCLUDED
#define ORZ_BASE_RBTREE_H_INCLUDED

#include "orz_animate.h"
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
        inline RBTreeNode* Maxmum(RBTreeNode *x);
        inline RBTreeNode* Minmum(RBTreeNode *x);

		// 打印操作
		void Print(void);
		void Print(RBTreeNode*, int);

        // 后继
        RBTreeNode* Successor(RBTreeNode* x);

        // 旋转操作
        inline void LeftRotate(RBTreeNode* x);
        inline void RightRotate(RBTreeNode* x);

        // 插入
        void Insert(RBTreeNode* z);

        // 删除
        void Transplant(RBTreeNode* y, RBTreeNode* x);
        void Delete(RBTreeNode* z);

	private:
		void InsertFixUp(RBTreeNode* z);
		void DeleteFixUp(RBTreeNode* x);

        RBTreeNode* const null;
        RBTreeNode soild_null;
        RBTreeNode* root;
    };
}
#endif // ORZ_BASE_RBTREE_H_INCLUDED
