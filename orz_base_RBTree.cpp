
#include "orz_base_RBTree.h"
#include <iostream>

namespace Orz
{
	RBTree::RBTree():null(&soild_null), root(null), size(0)
	{
		null->color = BLACK;
	}
	
	RBTree::~RBTree()
	{
		Free();
	}

	// 打印操作
	void RBTree::_Print()
	{
		_Print(root, 0);
	}

	void RBTree::_Print(RBTreeNode* node, int lay)
	{
		using std::cout;
		if(node!=null)
		{
			cout<<"层数为"<<lay<<"的 "<<node<<" 节点的值为: "<<node->key<<"\n";

			cout<<"层数为"<<lay<<"的 "<<node<<" 的左节点:\n";
			_Print(node->left, lay+1);
			cout<<"层数为"<<lay<<"的 "<<node<<" 的右节点:\n";
			_Print(node->right, lay+1);
		}
		else
			cout<<"层数为"<<lay<<"的 "<<node<<" 节点无数据\n"<<std::endl;
	}

    // 搜寻
    // 成功 返回相应节点
    // 失败 返回NULL
    RBTreeNode* RBTree::Search(const KeyType &key)
    {
        RBTreeNode *x = root;
        while(x != null && x->key != key)
        {
            if(key < x->key)
                x = x->left;
            else x = x->right;
        }

        if(x != null)
			return x;
		else
			return NULL;
    }


    // 释放空间
    RBTreeNode* RBTree::Free(RBTreeNode *x)
    {
        if(x != null)
        {
            if(x->left != null) delete Free(x->left);
            if(x->right != null) delete Free(x->right);
            return x;
        }

        return NULL;
    }

    void RBTree::Free()
    {
		delete Free(root);
		size = 0;
    }

    // 寻找后继
    RBTreeNode* RBTree::Successor(RBTreeNode* x)
    {
        if(x->right != null)
            return Minmum(x->right);

        RBTreeNode* y = x->parent;

        while(y != null && x == y->right)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // 旋转操作
    void RBTree::LeftRotate(RBTreeNode* x)
    {
        // 处理孩子节点
        RBTreeNode* y = x->right;
        x->right = y->left;

        // 处理双亲节点
        if(y->left != null)
            y->left->parent = x;
        y->parent = x->parent;

        // 处理根节点
        if(x->parent == null)
            root = y;
        else if(x == x->parent->left)
            x->parent->left = y;
        else x->parent->right = y;

        // 处理其他节点
        y->left = x;
        x->parent = y;
    }
    
	void RBTree::RightRotate(RBTreeNode* y)
    {
        // 处理孩子节点
        RBTreeNode* x = y->left;
        y->left = x->right;

        // 处理双亲节点
        if(x->right != null)
            x->right->parent = y;
        x->parent = y->parent;

        // 处理根节点
        if(y->parent == null)
            root = x;
        else if(y == y->parent->left)
            y->parent->left = x;
        else y->parent->right = x;

        // 处理其他节点
        x->right = y;
        y->parent = x;
    }

    // 插入操作
    void RBTree::Insert(RBTreeNode* z)
    {
        RBTreeNode  *x = root, *y= null;
        while(x != null)
        {
            y = x;
            if(z->key < x->key)
                x = x->left;
            else x = x->right;
        }

        z->parent = y;

        if(y == null)
            root = z;
        else if(z->key < y->key)
            y->left = z;
        else y->right = z;

        z->left = z->right = null;
        z->color = RED;

        InsertFixUp(z);

		size++;
    }

    void RBTree::InsertFixUp(RBTreeNode* z)
    {
        while(z->parent->color == RED)
        {
            if(z->parent == z->parent->parent->left)
            {
                RBTreeNode* y = z->parent->parent->right;

                if(y->color == RED)
                {
                    z->parent->color = y->color = BLACK;
                    y->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->right)
                    {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
					RightRotate(z->parent->parent);
                }
            }
            else
            {
                RBTreeNode* y = z->parent->parent->left;

                if(y->color == RED)
                {
                    z->parent->color = y->color = BLACK;
                    y->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // 删除
    void RBTree::Transplant(RBTreeNode* y, RBTreeNode* x)
    {
        if(y->parent == null)
            root = y;
        else if(y == y->parent->left)
            y->parent->left = x;
        else y->parent->right = x;

        x->parent = y->parent;
    }

    void RBTree::Delete(RBTreeNode* z)
    {
        RBTreeNode *y = z, *x;
        RBTreeColor y_original_color = y->color;

        if(z->left == null)
        {
            x = z->right;
            Transplant(z, z->right);
        }
        else if(z->right == null)
        {
            x = z->left;
            Transplant(z, z->left);
        }
        else
        {
            y = Minmum(y->right);
            y_original_color = y->color;
            x = y->right;

            if(y->parent == z)
            {
                x->parent = y;  // 确保了 T.null.parent == y !
            }
            else
            {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            Transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;

            if(y_original_color == BLACK)
                DeleteFixUp(x);
        }

		size--;
    }
    
	void RBTree::DeleteFixUp(RBTreeNode* x)
    {
        while(x != root && x->color == BLACK)
        {
            if(x==x->parent->left)
            {
                RBTreeNode* w = x->parent->right;

                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }

                if(w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = BLACK;
                    x = x->parent;
                }
                else
                {
                    if(w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                RBTreeNode* w = x->parent->left;

                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }

                if(w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = BLACK;
                    x = x->parent;
                }
                else
                {
                    if(w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = w->left->color = BLACK;
                    RightRotate(x->parent);
                    x = root;
                }
            }

        }
        x->color = BLACK;
    }

	RBTreeNode* RBTree::Maxmum(RBTreeNode *x)
	{
		while(x->left != null)
			x = x->left;
		return x;
	}

	RBTreeNode* RBTree::Minmum(RBTreeNode *x)
	{
		while(x->right != null)
			x = x->right;
		return x;
	}

	bool RBTree::Empty()
	{
		if (size >= 0)
			return false;

		return true;
	}

	int RBTree::Size()
	{
		return size;
	}

}










