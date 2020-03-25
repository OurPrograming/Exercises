#include "Calculator.h"

bool Calculator::isOperator(char ope)
{
	if (ope == '+' || ope == '-' || ope == '*' || ope == '/')
		return true;
	else
		return false;
}

int Calculator::getPriority(char ope)
{
	if (isOperator(ope) == true)
	{
		if (ope == '+' || ope == '-')
			return 1;
		if (ope == '*' || ope == '/')
			return 2;
	}
	return 0;
}

double Calculator::calculate(double x1, char op, double x2)
{
	switch (op)
	{
	case '+':
		return x1 + x2;
	case '-':
		return x1 - x2;
	case '*':
		return x1 * x2;
	case '/':
		return x1 / x2;
	default:
		return 0.0;
	}
}

string Calculator::toReversePolish(string expression)
{
	return string();
}

BinaryTreeNode * Calculator::toTree(string exp)
{
	return nullptr;
}

double Calculator::calcResult(BinaryTreeNode * root)
{
	std::stack<double> num;			//数字栈
	double num1, num2, result;

	if (root != nullptr)
	{
		calcResult(root->leftChild);
		calcResult(root->rightChild);
		if (isOperator(root->data.at(0)))
		{
			num.push(root->data.at(0));    //运算符压入num栈
		}
		else
		{   //结点为运算符时进行运算
			num1 = num.top();  num.pop();
			num2 = num.top();  num.pop();
			result = calculate(num2, root->data.at(0), num1);
			num.push(result);   //运算结果压入栈
		}
	}
	return num.top();
}
