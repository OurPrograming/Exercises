#include "Calculator.h"

bool Calculator::isOperator(char ope)
{
	if (ope == '+' || ope == '-' || ope == '*' || ope == '/' || ope == '(' || ope == ')')
		return true;
	else
		return false;
}

int Calculator::getPriority(char ope)
{
	if (isOperator(ope) == true)
	{
		if (ope == '(' || ope == ')')
			return 0;
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

string Calculator::toReversePolish(string expression)  //������׺���ʽתΪ�沨��ʽ
{
	std::stack<char> S1;  //�����ջ
	std::stack<char> S2;  //�沨��ʽջ
	char ope;

	for (int i = 0; i != expression.length(); i++)  //��expression�����ȡ���ַ�
	{
		if (isOperator(expression[i]))  //��ȡ�������
		{
			if (S1.empty() || expression[i] == '(')
			{
				S1.push(expression[i]);   //��ջ�ջ������Ϊ'('ֱ����ջS1
			}
			else if(expression[i] == ')')
			{
				do
				{   //����ȡ��')'����ջS1�е���������ȡ��
					ope = S1.top();   S1.pop();
					if (ope != '(')
					{
						S2.push(ope);  //��ȡ���Ĳ���'('����ѹ��ջS2
					}
				} while (ope != '(');  //ȡ��'('��ֹͣѭ����������'('
			}
			else if (getPriority(expression[i]) > getPriority(S1.top()))  //�Ƚ����ȼ�
			{
				S1.push(expression[i]);  //����������ȼ���ջ����������ȼ��ߣ�ֱ����ջ
			}
			else
			{
				do
				{   //�������ջS1���ȡ���������ѹ����ʽջS2��ֱ������������ȼ���ջ����������ȼ���
					ope = S1.top();   S1.pop();
					S2.push(ope);  
				} while (getPriority(expression[i]) > getPriority(S1.top()));
				S1.push(expression[i]);   //��ɲ��������������ȼ���ջ����������ȼ��ߣ��������ջS1
			}
		}
		else
		{
			S2.push(expression[i]);   //��ȡ�����֣�ֱ������ʽջS2
		}
	}
	while (!S2.empty())   //�����ʽջ����
	{
		ope = S2.top();   S2.pop();
		S1.push(ope);
	}
	for (int j = 0; !S1.empty(); j++)  //����沨��ʽ
	{
		expression[j] = S1.top();   S1.pop();
	}
	return expression;
}

BinaryTreeNode * Calculator::toTree(string exp)  //�沨��ʽתΪ��
{
	BinaryTreeNode *exp_root;

	return nullptr;
}

double Calculator::calcResult(BinaryTreeNode * root)
{
	std::stack<double> num;			//����ջ
	double num1, num2, result;

	if (root != nullptr)
	{
		calcResult(root->leftChild);
		calcResult(root->rightChild);
		if (isOperator(root->data.at(0)))
		{
			num.push(root->data.at(0));    //����ѹ��numջ
		}
		else
		{   //���Ϊ�����ʱ��������
			num1 = num.top();  num.pop();
			num2 = num.top();  num.pop();
			result = calculate(num2, root->data.at(0), num1);
			num.push(result);   //������ѹ��ջ
		}
	}
	return num.top();
}
