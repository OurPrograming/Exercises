#include "BinaryTree.h"

BinaryTree::BinaryTree(BinaryTreeNode *root)
{
	pRoot = root;
}

BinaryTree::BinaryTree(const BinaryTree & tree)
{
	pRoot = copy(tree.pRoot);
}

BinaryTree::~BinaryTree()
{
	destroy(pRoot);
}

void BinaryTree::destroy(BinaryTreeNode * &root)
{
	if (root != nullptr)
	{
		destroy(root->leftChild);
		destroy(root->rightChild);

		delete root;
		root = nullptr;
	}
}

BinaryTreeNode * BinaryTree::copy(BinaryTreeNode * root)
{
	if (root != nullptr)
	{
		//复制树 不是赋值给树，不能直接让指针相等
		//新建一棵树并把节点内容复制过去
		BinaryTreeNode *newRoot = new BinaryTreeNode(root->data);
		newRoot->leftChild = copy(root->leftChild);
		newRoot->rightChild = copy(root->rightChild);
		return newRoot;
	}
	return nullptr;
}

bool BinaryTree::compare(BinaryTreeNode * tree1, BinaryTreeNode * tree2)
{
	//树为空或部分空的情况
	if (tree1 == nullptr && tree2 == nullptr)
		return true;
	if ((tree1 == nullptr && tree2 != nullptr) ||
		(tree1 != nullptr && tree2 == nullptr))
		return false;

	//根节点
	if (tree1->data != tree2->data)
		return false;

	//左右孩子都相等
	if (compare(tree1->leftChild, tree2->leftChild) == true)
	{
		if (compare(tree1->rightChild, tree2->rightChild) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//交换相等
	if (compare(tree1->leftChild, tree2->rightChild) == true)
	{
		if (compare(tree1->rightChild, tree2->leftChild) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}