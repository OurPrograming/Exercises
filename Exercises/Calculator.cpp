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

string Calculator::toReversePolish(string expression)  //传入中缀表达式转为逆波兰式
{
	std::stack<char> s;		//运算符栈
	string result = "";
	string::iterator ite;		//string迭代器

	for (ite = expression.begin(); ite != expression.end(); ite++)
	{
		//空格跳过
		if (*ite == ' ')
		{
			continue;
		}

		//数字直接输出即可
		if (!isOperator(*ite))
		{
			//以空格为界输出一整个数字
			do 
			{
				result.push_back(*ite);
				ite++;
				if (ite == expression.end() || *ite == ')')
				{
					ite--;		//退回一位以免越界或忽略括号
					break;
				}
			} while (*ite != ' ');
			result += " ";	//输出完加空格以区分数字
		}
		else	//运算符
		{
			//栈为空直接入栈
			if (s.empty())
			{
				s.push(*ite);
			}
			else if (*ite == ')')	//右括号把左括号之前的所有运算符出栈
			{
				//栈顶不是左括号就一直输出
				while (!s.empty() && s.top() != '(')
				{
					result.push_back(s.top());
					s.pop();
					result += " ";
				}
				//遇到左括号后就弹出(不输出)
				if (s.top() == '(')
				{
					s.pop();
				}
			}
			else if (*ite == '(')
			{
				s.push(*ite);
			}
			else	//其他符号进行运算符优先级比较
			{
				//得到栈顶和当前的优先级
				int topPriority = 0, curPriority = 0;
				do
				{
					topPriority = getPriority(s.top());
					curPriority = getPriority(*ite);
					if (topPriority == 3)
					{
						break;
					}
					//当前的优先级小就输出
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

				//出栈结束后将当前运算符压栈
				s.push(*ite);
			}
		}
	}

	//若string遍历完成而栈还有元素
	while (!s.empty())
	{
		//全部出栈
		result.push_back(s.top());
		s.pop();
		result += " ";
	}

	//返回结果
	return result;
}

BinaryTreeNode * Calculator::toTree(string exp)  //逆波兰式转为树
{
	//节点栈
	std::stack<BinaryTreeNode *> nodeStack;

	//用于构造节点数据
	string *data = nullptr;
	BinaryTreeNode *node = nullptr;
	BinaryTreeNode *left = nullptr, *right = nullptr;

	string::iterator ite;
	for (ite = exp.begin(); ite != exp.end(); ite++)
	{
		//空格跳过
		if (*ite == ' ')
		{
			continue;
		}

		//数字
		if (!isOperator(*ite))
		{
			//字符串用于保存数字
			data = new string("");

			//以空格区分元素
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

			//提取出数字后建立节点入栈
			node = new BinaryTreeNode(*data);
			nodeStack.push(node);
		}
		else	//运算符
		{
			//得到左右子树 
			right = nodeStack.top();
			nodeStack.pop();
			left = nodeStack.top();
			nodeStack.pop();

			//当前运算符构造节点数据
			data = new string(1, *ite);
			node = new BinaryTreeNode(*data, left, right);
			//构造完树后入栈
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
		if (!isOperator(root->data.at(0)))		//数字直接返回
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
