#pragma once

#include <stack>
#include <string>
#include "BinaryTree.h"

using std::string;

/*
**	计算类
*/
class Calculator
{
public:
	static bool isOperator(char ope);		//判断是否为操作符
	static int getPriority(char ope);		//返回优先级
	static double calculate(double x1, char op, double x2);   //两数四则运算

	static string toReversePolish(string expression);	//传入中缀表达式转为逆波兰式
	static BinaryTreeNode * toTree(string exp);			//逆波兰式转为树
	static double calcResult(BinaryTreeNode *root);		//计算树的结果
};
