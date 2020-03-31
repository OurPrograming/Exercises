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

string Calculator::toReversePolish(string expression)  //传入中缀表达式转为逆波兰式
{
	std::stack<string> S1;  //运算符栈
	std::stack<string> S2;  //逆波兰式栈
	string *ope;     //运算符,分数
	string *exp = new string;  //逆波兰式
	string *leftbracket = new string(1, '(');    //左括号

	for (int i = 0; i < expression.length(); i++)  //从expression中逐个取出字符
	{
		if (isOperator(expression.at(i)))  //若取出运算符
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
				while ((*ope).at(0) != '(')  //取出'('后停止循环，并抛弃'('
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
			else if (getPriority(expression.at(i)) > getPriority(S1.top().at(0)))  //比较优先级
			{
				ope = new string(1, expression.at(i));
				S1.push(*ope);  //该运算符优先级比栈顶运算符优先级高，直接入栈
			}
			else
			{
				if (!S1.empty())
				{
					while (getPriority(expression.at(i)) <= getPriority(S1.top().at(0)))
					{   //从运算符栈S1逐个取出运算符并压入表达式栈S2，直到该运算符优先级比栈顶运算符优先级高
						ope = new string;
						*ope = S1.top();   S1.pop();
						S2.push(*ope);
						if (S1.empty()) break;
					}
				}
				ope = new string(1, expression.at(i));
				S1.push(*ope);   //完成操作后该运算符优先级比栈顶运算符优先级高，入运算符栈S1
			}
		}
		else
		{ 
			if (expression.at(i) == ' ')  i++;  //隔离第一个空格
			string fat;
			while (expression.at(i) != ' ' && expression.at(i) != '(' && expression.at(i) != ')')
			{   //保存分数字符串
				fat.push_back(expression.at(i));
				i++;
				if (i >= expression.length()) break;
			}
			if (!fat.empty())
			{
				S2.push(fat);    //生成分数字符串，并压入表达式栈S2
			}
			if (i < expression.length())
			{
				if (expression.at(i) == '(' || expression.at(i) == ')')  i--;
			}
		}
	}
	while (!S2.empty())   //将表达式栈逆序
	{
		string op;
		op = S2.top();   S2.pop();
		S1.push(op);
	}
	exp = new string;
	while(!S1.empty())  //组装逆波兰式
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
	return *exp;  //返回逆波兰式
}

BinaryTreeNode * Calculator::toTree(string exp)  //逆波兰式转为树
{
	std::stack<BinaryTreeNode*> num;    //数字栈
	BinaryTreeNode *exp_ptr = nullptr;  //结点指针
	BinaryTreeNode *right = nullptr;    //右孩子指针
	BinaryTreeNode *left = nullptr;     //左孩子指针
	string *data_exp;         //结点数据

	for (int i = 0; i < exp.length(); i++)  //逐个字符读取逆波兰式
	{
		if (isOperator(exp.at(i)))     //读取到运算符
		{
			right = num.top();  num.pop(); 
			left = num.top();  num.pop();
			data_exp = new string(1,exp.at(i));     //将运算符转化为string类型，并赋给结点数据data

			BinaryTreeNode *exp_root = new BinaryTreeNode(*data_exp, left, right);  //构建新树
			num.push(exp_root);  
		}
		else
		{   //读取到数字，生成完整分数字符串，并压入数字栈num
			if (exp.at(i) == ' ')   i++;   //隔离第一个空格
			if (!isOperator(exp.at(i)))
			{
				string fat;
				while (exp.at(i) != ' ')
				{   //保存分数字符串
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
	exp_ptr = num.top();  num.pop();  //从栈顶取出建好的树的根结点
	return exp_ptr;   //返回树的根结点
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