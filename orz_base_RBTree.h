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
        RBTreeNode* Maxmum(RBTreeNode *x);
        RBTreeNode* Minmum(RBTreeNode *x);

		// ��ӡ����,������
		void _Print(void);
		void _Print(RBTreeNode*, int);

        // ���
        RBTreeNode* Successor(RBTreeNode* x);

        // ����
        void Insert(RBTreeNode* z);

        // ɾ��
        void Delete(RBTreeNode* z);

		// ��ѯ��С
		bool Empty();
		int Size();

	private:
		// �������
		void Transplant(RBTreeNode* y, RBTreeNode* x);

        // ��ת����
        void LeftRotate(RBTreeNode* x);
        void RightRotate(RBTreeNode* x);

		// �޸�����
		void InsertFixUp(RBTreeNode* z);
		void DeleteFixUp(RBTreeNode* x);

        RBTreeNode* const null;
		RBTreeNode* root;
		RBTreeNode soild_null;

		int size;
    };
}
#endif // ORZ_BASE_RBTREE_H_INCLUDED
