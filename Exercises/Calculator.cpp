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
	double left, right;
	if (root != nullptr)
	{
		left = calcResult(root->leftChild);
		right = calcResult(root->rightChild);
		if (!isOperator(root->data.at(0)))		//数字直接返回
		{
			return std::stoi(root->data);
		}
		else
		{
			return calculate(left, root->data.at(0), right);
		}
	}
	return 0.0;
}
