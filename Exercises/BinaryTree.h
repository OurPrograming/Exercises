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

	//初始化
	BinaryTreeNode() : leftChild(nullptr), rightChild(nullptr)	{}
	BinaryTreeNode(string d, BinaryTreeNode* l = nullptr, BinaryTreeNode* r = nullptr)
		: data(d), leftChild(l), rightChild(r) {}
};

/*
**	表达式树
*/
class BinaryTree
{
public:
	BinaryTreeNode * pRoot;
	
public:
	BinaryTree(BinaryTreeNode *root);
	BinaryTree(const BinaryTree &tree);				//拷贝构造函数
	~BinaryTree();

public:
	void destroy(BinaryTreeNode * &root);				//销毁树
	BinaryTreeNode * copy(BinaryTreeNode *root);	//复制树

	static bool compare(BinaryTreeNode *tree1, BinaryTreeNode *tree2);	//比较两棵树

};
