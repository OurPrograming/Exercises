#pragma once

#include <stack>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

struct BinaryTreeNode
{
	string data;
	BinaryTreeNode * leftChild;
	BinaryTreeNode * rightChild;

	//��ʼ��
	BinaryTreeNode() : leftChild(nullptr), rightChild(nullptr)	{}
	BinaryTreeNode(string d, BinaryTreeNode* l = nullptr, BinaryTreeNode* r = nullptr)
		: data(d), leftChild(l), rightChild(r) {}
};

/*
**	���ʽ��
*/
class BinaryTree
{
public:
	BinaryTreeNode * pRoot;
	
public:
	BinaryTree(BinaryTreeNode *root);
	BinaryTree(const BinaryTree &tree);				//�������캯��
	~BinaryTree();

public:
	void destroy(BinaryTreeNode * &root);				//������
	BinaryTreeNode * copy(BinaryTreeNode *root);	//������

	static bool compare(BinaryTreeNode *tree1, BinaryTreeNode *tree2);	//�Ƚ�������

};
