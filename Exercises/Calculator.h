#pragma once

#include <stack>
#include <string>
#include "BinaryTree.h"

using std::string;

/*
**	������
*/
class Calculator
{
public:
	static bool isOperator(char ope);		//�ж��Ƿ�Ϊ������
	static int getPriority(char ope);		//�������ȼ�
	static double calculate(double x1, char op, double x2);   //������������

	static string toReversePolish(string expression);	//������׺���ʽתΪ�沨��ʽ
	static BinaryTreeNode * toTree(string exp);			//�沨��ʽתΪ��
	static double calcResult(BinaryTreeNode *root);		//�������Ľ��
};
