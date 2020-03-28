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
		if (ope == '+' || ope == '-')
			return 1;
		if (ope == '*' || ope == '/')
			return 2;
		if (ope == '(' || ope == ')')
			return 3;
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
	std::stack<char> s;		//�����ջ
	string result = "";
	string::iterator ite;		//string������

	for (ite = expression.begin(); ite != expression.end(); ite++)
	{
		//�ո�����
		if (*ite == ' ')
		{
			continue;
		}

		//����ֱ���������
		if (!isOperator(*ite))
		{
			//�Կո�Ϊ�����һ��������
			do 
			{
				result.push_back(*ite);
				ite++;
				if (ite == expression.end() || *ite == ')')
				{
					ite--;		//�˻�һλ����Խ����������
					break;
				}
			} while (*ite != ' ');
			result += " ";	//�����ӿո�����������
		}
		else	//�����
		{
			//ջΪ��ֱ����ջ
			if (s.empty())
			{
				s.push(*ite);
			}
			else if (*ite == ')')	//�����Ű�������֮ǰ�������������ջ
			{
				//ջ�����������ž�һֱ���
				while (!s.empty() && s.top() != '(')
				{
					result.push_back(s.top());
					s.pop();
					result += " ";
				}
				//���������ź�͵���(�����)
				if (s.top() == '(')
				{
					s.pop();
				}
			}
			else if (*ite == '(')
			{
				s.push(*ite);
			}
			else	//�������Ž�����������ȼ��Ƚ�
			{
				//�õ�ջ���͵�ǰ�����ȼ�
				int topPriority = 0, curPriority = 0;
				do
				{
					topPriority = getPriority(s.top());
					curPriority = getPriority(*ite);
					if (topPriority == 3)
					{
						break;
					}
					//��ǰ�����ȼ�С�����
					if (curPriority <= topPriority)
					{
						result.push_back(s.top());
						s.pop();
						result += " ";
					}
					else
					{
						break;
					}
				} while (!s.empty());

				//��ջ�����󽫵�ǰ�����ѹջ
				s.push(*ite);
			}
		}
	}

	//��string������ɶ�ջ����Ԫ��
	while (!s.empty())
	{
		//ȫ����ջ
		result.push_back(s.top());
		s.pop();
		result += " ";
	}

	//���ؽ��
	return result;
}

BinaryTreeNode * Calculator::toTree(string exp)  //�沨��ʽתΪ��
{
	//�ڵ�ջ
	std::stack<BinaryTreeNode *> nodeStack;

	//���ڹ���ڵ�����
	string *data = nullptr;
	BinaryTreeNode *node = nullptr;
	BinaryTreeNode *left = nullptr, *right = nullptr;

	string::iterator ite;
	for (ite = exp.begin(); ite != exp.end(); ite++)
	{
		//�ո�����
		if (*ite == ' ')
		{
			continue;
		}

		//����
		if (!isOperator(*ite))
		{
			//�ַ������ڱ�������
			data = new string("");

			//�Կո�����Ԫ��
			do
			{
				data->push_back(*ite);
				ite++;
				if (ite == exp.end())
				{
					ite--;
					break;
				}
			} while (*ite != ' ');

			//��ȡ�����ֺ����ڵ���ջ
			node = new BinaryTreeNode(*data);
			nodeStack.push(node);
		}
		else	//�����
		{
			//�õ��������� 
			right = nodeStack.top();
			nodeStack.pop();
			left = nodeStack.top();
			nodeStack.pop();

			//��ǰ���������ڵ�����
			data = new string(1, *ite);
			node = new BinaryTreeNode(*data, left, right);
			//������������ջ
			nodeStack.push(node);
		}
	}

	return node;
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
