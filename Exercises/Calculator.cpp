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

Fraction Calculator::calculate(Fraction x1, char op, Fraction x2)
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
		return Fraction(0);
	}
}

string Calculator::toReversePolish(string expression)  //������׺���ʽתΪ�沨��ʽ
{
	std::stack<string> S1;  //�����ջ
	std::stack<string> S2;  //�沨��ʽջ
	string *ope, *fat;     //�����,����
	string *exp = new string;  //�沨��ʽ
	string *leftbracket = new string(1, '(');    //������

	for (int i = 0; i != expression.length(); i++)  //��expression�����ȡ���ַ�
	{
		ope = new string;
		if (isOperator(expression.at(i)))  //��ȡ�������
		{
			if (S1.empty() || expression.at(i) == '(')
			{
				ope = new string(1, expression.at(i));
				S1.push(*ope);   
			}
			else if(expression.at(i) == ')')
			{
				do
				{   //����ȡ��')'����ջS1�е���������ȡ��
					*ope = S1.top();   S1.pop();
					if (*ope != *leftbracket)
					{
						S2.push(*ope);  
					}
				} while (*ope != *leftbracket);  //ȡ��'('��ֹͣѭ����������'('
			}
			else if (getPriority(expression.at(i)) > getPriority(S1.top().at(0)))  //�Ƚ����ȼ�
			{
				ope = new string(1, expression.at(i));
				S1.push(*ope);  //����������ȼ���ջ����������ȼ��ߣ�ֱ����ջ
			}
			else
			{
				do
				{   //�������ջS1���ȡ���������ѹ����ʽջS2��ֱ������������ȼ���ջ����������ȼ���
					*ope = S1.top();   S1.pop();
					S2.push(*ope);  
				} while (getPriority(expression.at(i)) > getPriority(S1.top().at(0)));
				ope = new string(1, expression.at(i));
				S1.push(*ope);   //��ɲ��������������ȼ���ջ����������ȼ��ߣ��������ջS1
			}
		}
		else
		{ 
			if (expression.at(i) == ' ')  i++;  //�����һ���ո�
			fat = new string;
			do  
			{   //��������ַ���
				*fat += expression.at(i++);
			} while (expression.at(i) = ' ');
			S2.push(*fat);    //���ɷ����ַ�������ѹ����ʽջS2
		}
	}
	ope = new string;
	while (!S2.empty())   //�����ʽջ����
	{
		*ope = S2.top();   S2.pop();
		S1.push(*ope);
	}
	while(!S1.empty())  //��װ�沨��ʽ
	{
		*exp = *exp + S1.top() + ' ';   S1.pop();
	}
	return *exp;  //�����沨��ʽ
}

BinaryTreeNode * Calculator::toTree(string exp)  //�沨��ʽתΪ��
{
	std::stack<BinaryTreeNode*> num;    //����ջ
	BinaryTreeNode *exp_ptr = nullptr;  //���ָ��
	BinaryTreeNode *right = nullptr;    //�Һ���ָ��
	BinaryTreeNode *left = nullptr;     //����ָ��
	string *data, *fat;         //�������,����

	for (int i = 1; i != exp[exp.length()]; i++)  //����ַ���ȡ�沨��ʽ
	{
		exp_ptr = new BinaryTreeNode();
		if (isOperator(exp.at(i)))     //��ȡ�������
		{
			right = num.top();  num.pop();
			left = num.top();  num.pop();
			data = new string(1,exp.at(i));     //�������ת��Ϊstring���ͣ��������������data
			
			BinaryTreeNode *exp_root = new BinaryTreeNode(*data, left, right);  //��������
			num.push(exp_root);
		}
		else
		{   //��ȡ�����֣��������������ַ�������ѹ������ջnum
			if (exp.at(i) == ' ')   i++;   //�����һ���ո�
			do
			{   //��������ַ���
				*fat += exp.at(i++);
			} while (exp.at(i) = ' ');
			exp_ptr->data = *fat;
			num.push(exp_ptr);
		}
	}
	exp_ptr = num.top();  num.pop();  //��ջ��ȡ�����õ����ĸ����
	return exp_ptr;   //�������ĸ����
}

Fraction Calculator::calcResult(BinaryTreeNode * root)
{
	Fraction left, right;
	if (root != nullptr)
	{
		left = calcResult(root->leftChild);
		right = calcResult(root->rightChild);
		if (!isOperator(root->data.at(0)))		//����ֱ�ӷ���
		{
			return Fraction(root->data);
		}
		else
		{
			return calculate(left, root->data.at(0), right);
		}
	}
	return Fraction(0);
}
