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
	string *ope;     //�����,����
	string *exp = new string;  //�沨��ʽ
	string *leftbracket = new string(1, '(');    //������

	for (int i = 0; i < expression.length(); i++)  //��expression�����ȡ���ַ�
	{
		if (isOperator(expression.at(i)))  //��ȡ�������
		{
			if (S1.empty() || expression.at(i) == '(')
			{
				ope = new string(1, expression.at(i));
				S1.push(*ope);   
			}
			else if(expression.at(i) == ')')
			{
				ope = new string;
				*ope = S1.top();   S1.pop();
				while ((*ope).at(0) != '(')  //ȡ��'('��ֹͣѭ����������'('
				{
					if ((*ope).at(0) != '(')
					{
						S2.push(*ope);
					}
					ope = new string;
					*ope = S1.top();   S1.pop();
				}
				i++;
			}
			else if (getPriority(expression.at(i)) > getPriority(S1.top().at(0)))  //�Ƚ����ȼ�
			{
				ope = new string(1, expression.at(i));
				S1.push(*ope);  //����������ȼ���ջ����������ȼ��ߣ�ֱ����ջ
			}
			else
			{
				if (!S1.empty())
				{
					while (getPriority(expression.at(i)) <= getPriority(S1.top().at(0)))
					{   //�������ջS1���ȡ���������ѹ����ʽջS2��ֱ������������ȼ���ջ����������ȼ���
						ope = new string;
						*ope = S1.top();   S1.pop();
						S2.push(*ope);
						if (S1.empty()) break;
					}
				}
				ope = new string(1, expression.at(i));
				S1.push(*ope);   //��ɲ��������������ȼ���ջ����������ȼ��ߣ��������ջS1
			}
		}
		else
		{ 
			if (expression.at(i) == ' ')  i++;  //�����һ���ո�
			string fat;
			while (expression.at(i) != ' ' && expression.at(i) != '(' && expression.at(i) != ')')
			{   //��������ַ���
				fat.push_back(expression.at(i));
				i++;
				if (i >= expression.length()) break;
			}
			if (!fat.empty())
			{
				S2.push(fat);    //���ɷ����ַ�������ѹ����ʽջS2
			}
			if (i < expression.length())
			{
				if (expression.at(i) == '(' || expression.at(i) == ')')  i--;
			}
		}
	}
	while (!S2.empty())   //�����ʽջ����
	{
		string op;
		op = S2.top();   S2.pop();
		S1.push(op);
	}
	exp = new string;
	while(!S1.empty())  //��װ�沨��ʽ
	{
		string str = S1.top();  S1.pop();
		if (!S1.empty())
		{
			*exp = *exp + str + ' ';
		}
		else
		{
			*exp = *exp + str;
		}
	}
	return *exp;  //�����沨��ʽ
}

BinaryTreeNode * Calculator::toTree(string exp)  //�沨��ʽתΪ��
{
	std::stack<BinaryTreeNode*> num;    //����ջ
	BinaryTreeNode *exp_ptr = nullptr;  //���ָ��
	BinaryTreeNode *right = nullptr;    //�Һ���ָ��
	BinaryTreeNode *left = nullptr;     //����ָ��
	string *data_exp;         //�������

	for (int i = 0; i < exp.length(); i++)  //����ַ���ȡ�沨��ʽ
	{
		if (isOperator(exp.at(i)))     //��ȡ�������
		{
			right = num.top();  num.pop(); 
			left = num.top();  num.pop();
			data_exp = new string(1,exp.at(i));     //�������ת��Ϊstring���ͣ��������������data

			BinaryTreeNode *exp_root = new BinaryTreeNode(*data_exp, left, right);  //��������
			num.push(exp_root);  
		}
		else
		{   //��ȡ�����֣��������������ַ�������ѹ������ջnum
			if (exp.at(i) == ' ')   i++;   //�����һ���ո�
			if (!isOperator(exp.at(i)))
			{
				string fat;
				while (exp.at(i) != ' ')
				{   //��������ַ���
					fat.push_back(exp.at(i));
					i++;
					if (i >= exp.length()) break;
				}
				exp_ptr = new BinaryTreeNode;
				if (!fat.empty())
				{
					exp_ptr->data = fat;
					num.push(exp_ptr);
				}
			}
			else
			{
				i--;
			}
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