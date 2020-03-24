#pragma once

#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "Calculator.h"

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
	BinaryTreeNode(string data, BinaryTreeNode* l = nullptr, BinaryTreeNode* r = nullptr)
		: leftChild(l), rightChild(r)	{}
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

	bool printTree(BinaryTreeNode *root);			//带括号输出
	static bool compare(BinaryTreeNode *tree1, BinaryTreeNode *tree2);	//比较两棵树

public:
	char op1, op2;   //运算符
	double n1, n2, n3;  //运算数据
	double re;     //运算结果
	std::stack<char> opt_s; //运算符栈
	std::stack<double> num;   //数据栈

	void push_tree(BinaryTreeNode * root);      //把树各结点压入栈
	double calcResult();	//计算这棵树的结果
};
