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
		//������ ���Ǹ�ֵ����������ֱ����ָ�����
		//�½�һ�������ѽڵ����ݸ��ƹ�ȥ
		BinaryTreeNode *newRoot = new BinaryTreeNode(root->data);
		newRoot->leftChild = copy(root->leftChild);
		newRoot->rightChild = copy(root->rightChild);
		return newRoot;
	}
	return nullptr;
}

bool BinaryTree::compare(BinaryTreeNode * tree1, BinaryTreeNode * tree2)
{
	//��Ϊ�ջ򲿷ֿյ����
	if (tree1 == nullptr && tree2 == nullptr)
		return true;
	if ((tree1 == nullptr && tree2 != nullptr) ||
		(tree1 != nullptr && tree2 == nullptr))
		return false;

	//���ڵ�
	if (tree1->data != tree2->data)
		return false;

	//���Һ��Ӷ����
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

	//�������
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