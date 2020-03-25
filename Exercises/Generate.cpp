#include "Generate.h"

Generate::Generate(int range)
{
	this->range = range;
	mt.seed(randomDevice());
}

Generate::~Generate()
{

}

int Generate::getNumber()
{
	std::uniform_int_distribution<int> rand(1, range);
	return rand(mt);
}

char Generate::getOperator()
{
	std::uniform_int_distribution<int> rand(1, 4);
	
	int ran = rand(mt);
	switch (ran)
	{
	case 1:
		return '+';
	case 2:
		return '-';
	case 3:
		return '*';
	case 4:
		return '/';
	default:
		return '\0';
	}
}

string Generate::getFraction()
{
	return string();
}

BinaryTree * Generate::genExercise()
{
	//3 --> 2 --> 2
	//	 -> 3 --> 1
	
	//运算符个数
	std::uniform_int_distribution<int> opeCount(1, 3);
	int opeNum = opeCount(mt);

	//先新建出一颗最小树
	BinaryTreeNode *left = new BinaryTreeNode(std::to_string(getNumber()));
	BinaryTreeNode *right = new BinaryTreeNode(std::to_string(getNumber()));
	string *data = new string(1, getOperator());
	BinaryTreeNode *root = new BinaryTreeNode(*data, left, right);
	opeNum--;

	if (opeNum == 0)		//如果运算符只有一个直接返回
	{
		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}

	//用于二选一的随机数
	std::uniform_int_distribution<int> randBool(0, 1);

	//选择下一步是2或3
	if (randBool(mt) == 0 && opeNum == 2)	//再生成一个最小树并连接
	{
		left = new BinaryTreeNode(std::to_string(getNumber()));
		right = new BinaryTreeNode(std::to_string(getNumber()));
		data = new string(1, getOperator());
		BinaryTreeNode *tempRoot = new BinaryTreeNode(*data, left, right);
		opeNum--;

		//选择左右顺序
		if (randBool(mt) == 0)	//新树在左
		{
			left = tempRoot;
			right = root;
		}
		else
		{
			left = root;
			right = tempRoot;
		}
		//连接
		data = new string(1, getOperator());
		root = new BinaryTreeNode(*data, left, right);
		opeNum--;

		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}
	else		//往上插
	{
		do
		{	
			//二选一 左上or右上
			if (randBool(mt) == 0)	//左上
			{
				left = new BinaryTreeNode(std::to_string(getNumber()));
				right = root;
			}
			else			//右上
			{
				left = root;
				right = new BinaryTreeNode(std::to_string(getNumber()));
			}
			data = new string(1, getOperator());
			root = new BinaryTreeNode(*data, left, right);
			opeNum--;
		} while (opeNum > 0);

		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}
	return nullptr;
}

bool Generate::printTree(BinaryTreeNode * root)
{
	if (root == nullptr)
	{
		return true;
	}

	bool lChildBracket = false, rChildBracket = false;			//标志括号
	int leftPriority = 0, curPriority = 0, rightPriority = 0;	//优先级

	//中序遍历
	if (root->leftChild != nullptr)
	{
		//左子树是操作符加括号
		if (Calculator::isOperator(root->leftChild->data.at(0)))
		{
			//得到优先级
			leftPriority = Calculator::getPriority(root->leftChild->data.at(0));
			curPriority = Calculator::getPriority(root->data.at(0));
			if (leftPriority == 0 || curPriority == 0)
			{
				cerr << "表达式树不符合规范" << endl;
				return false;
			}
			if (curPriority > leftPriority)		//优先级大加括号
			{
				cout << "(";
				lChildBracket = true;
			}
		}
		//遍历左子树
		printTree(root->leftChild);
		//补上括号
		if (lChildBracket == true)
		{
			cout << ")";
			lChildBracket = false;
		}
	}

	//中
	if (Calculator::isOperator(root->data.at(0)))
		cout << " " + root->data + " ";
	else
		cout << root->data;

	//右
	if (root->rightChild != nullptr)
	{
		//右子树是操作符加括号
		if (Calculator::isOperator(root->rightChild->data.at(0)))
		{
			//得到优先级
			rightPriority = Calculator::getPriority(root->rightChild->data.at(0));
			curPriority = Calculator::getPriority(root->data.at(0));
			if (rightPriority == 0 || curPriority == 0)
			{
				cerr << "表达式树不符合规范" << endl;
				return false;
			}
			if (curPriority > rightPriority)		//优先级大加括号
			{
				cout << "(";
				rChildBracket = true;
			}
		}
		//遍历右子树
		printTree(root->rightChild);
		//补上括号
		if (rChildBracket == true)
		{
			cout << ")";
			rChildBracket = false;
		}
	}
	return true;
}
