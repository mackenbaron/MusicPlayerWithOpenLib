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

    // �����
    class RBTree
    {
    public:
        RBTree();
        ~RBTree();

        // �ͷ���
        void Free();
        RBTreeNode* Free(RBTreeNode *x);

        // ��Ѱ
        RBTreeNode* Search(const KeyType &key);

        // �������/��С
        inline RBTreeNode* Maxmum(RBTreeNode *x);
        inline RBTreeNode* Minmum(RBTreeNode *x);

		// ��ӡ����
		void Print(void);
		void Print(RBTreeNode*, int);

        // ���
        RBTreeNode* Successor(RBTreeNode* x);

        // ��ת����
        inline void LeftRotate(RBTreeNode* x);
        inline void RightRotate(RBTreeNode* x);

        // ����
        void Insert(RBTreeNode* z);

        // ɾ��
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
