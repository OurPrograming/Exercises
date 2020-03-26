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

string Calculator::toReversePolish(string expression)  //传入中缀表达式转为逆波兰式
{
	std::stack<char> S1;  //运算符栈
	std::stack<char> S2;  //逆波兰式栈
	char ope;

	for (int i = 0; i != expression.length(); i++)  //从expression中逐个取出字符
	{
		if (isOperator(expression[i]))  //若取出运算符
		{
			if (S1.empty() || expression[i] == '(')
			{
				S1.push(expression[i]);   //若栈空或运算符为'('直接入栈S1
			}
			else if(expression[i] == ')')
			{
				do
				{   //若提取到')'，将栈S1中的运算符逐个取出
					ope = S1.top();   S1.pop();
					if (ope != '(')
					{
						S2.push(ope);  //若取出的不是'('，则压入栈S2
					}
				} while (ope != '(');  //取出'('后停止循环，并抛弃'('
			}
			else if (getPriority(expression[i]) > getPriority(S1.top()))  //比较优先级
			{
				S1.push(expression[i]);  //该运算符优先级比栈顶运算符优先级高，直接入栈
			}
			else
			{
				do
				{   //从运算符栈S1逐个取出运算符并压入表达式栈S2，直到该运算符优先级比栈顶运算符优先级高
					ope = S1.top();   S1.pop();
					S2.push(ope);  
				} while (getPriority(expression[i]) > getPriority(S1.top()));
				S1.push(expression[i]);   //完成操作后该运算符优先级比栈顶运算符优先级高，入运算符栈S1
			}
		}
		else
		{
			S2.push(expression[i]);   //若取出数字，直接入表达式栈S2
		}
	}
	while (!S2.empty())   //将表达式栈逆序
	{
		ope = S2.top();   S2.pop();
		S1.push(ope);
	}
	for (int j = 0; !S1.empty(); j++)  //输出逆波兰式
	{
		expression[j] = S1.top();   S1.pop();
	}
	return expression;  //返回逆波兰式
}

BinaryTreeNode * Calculator::toTree(string exp)  //逆波兰式转为树
{
	std::stack<BinaryTreeNode*> num;  //数字栈
	BinaryTreeNode *exp_ptr;  //结点指针
	BinaryTreeNode *right;    //右孩子指针
	BinaryTreeNode *left;     //左孩子指针
	string data;              //结点数据

	for (int i = 1; i != exp[exp.length()]; i++)  //逐个字符读取逆波兰式
	{
		exp_ptr = new BinaryTreeNode();
		if (isOperator(exp[i]))     //读取到运算符
		{
			right = num.top();  num.pop();
			left = num.top();  num.pop();
			data.push_back(exp[i]);      //将运算符转化为string类型，并赋给结点数据data
			BinaryTreeNode *exp_root = new BinaryTreeNode(data, left, right);  //构建新树
			num.push(exp_root);
		}
		else
		{   //读取到数字，直接压入数字栈num
			exp_ptr->data = exp[i];
			num.push(exp_ptr);
		}
	}
	exp_ptr = num.top();  num.pop();  //从栈顶取出建好的树的根结点
	return exp_ptr;   //返回树的根结点
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
