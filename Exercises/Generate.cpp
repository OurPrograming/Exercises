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

Fraction Generate::getFraction()
{
	//二选一 整数0还是分数1
	std::uniform_int_distribution<int> randBool(0, 1);
	if (randBool(mt) == 0)		//整数
	{
		Fraction number(getNumber());	//分母默认值为1
		number.simple();
		return number;
	}
	else
	{
		Fraction number(getNumber(), getNumber());
		number.simple();
		return number;
	}
}

BinaryTree * Generate::genExercise()
{
	//3 --> 2 --> 2
	//	 -> 3 --> 1
	
	//运算符个数
	std::uniform_int_distribution<int> opeCount(1, 3);
	int opeNum = opeCount(mt);

	//先新建出一颗最小树
	BinaryTreeNode *left = new BinaryTreeNode(getFraction().display());
	BinaryTreeNode *right = new BinaryTreeNode(getFraction().display());
	string *data = new string(1, getOperator());
	BinaryTreeNode *root = new BinaryTreeNode(*data, left, right);
	standardization(root);
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
		left = new BinaryTreeNode(getFraction().display());
		right = new BinaryTreeNode(getFraction().display());
		data = new string(1, getOperator());
		BinaryTreeNode *tempRoot = new BinaryTreeNode(*data, left, right);
		standardization(tempRoot);
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
		standardization(root);
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
				left = new BinaryTreeNode(getFraction().display());
				right = root;
			}
			else			//右上
			{
				left = root;
				right = new BinaryTreeNode(getFraction().display());
			}
			data = new string(1, getOperator());
			root = new BinaryTreeNode(*data, left, right);
			standardization(root);
			opeNum--;
		} while (opeNum > 0);

		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}
	return nullptr;
}

void Generate::standardization(BinaryTreeNode *& root)
{
	if (root->data.at(0) == '-')
	{
		Fraction left, right;
		left = Calculator::calcResult(root->leftChild);
		right = Calculator::calcResult(root->rightChild);
		if (left < right)		//小于就反向
		{
			BinaryTreeNode *temp = root->leftChild;
			root->leftChild = root->rightChild;
			root->rightChild = temp;
			temp = nullptr;
		}
	}
}

bool Generate::toString(BinaryTreeNode * root, string &strExercise)
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
				return false;
			}
			if (curPriority > leftPriority)		//优先级大加括号
			{
				strExercise = strExercise +  "(";
				lChildBracket = true;
			}
		}
		//遍历左子树
		toString(root->leftChild, strExercise);
		//补上括号
		if (lChildBracket == true)
		{
			strExercise = strExercise + ")";
			lChildBracket = false;
		}
	}

	//中
	if (Calculator::isOperator(root->data.at(0)))
		strExercise = strExercise + " " + root->data + " ";
	else
		strExercise = strExercise + root->data;

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
				return false;
			}
			if (curPriority > rightPriority)		//优先级大加括号
			{
				strExercise = strExercise + "(";
				rChildBracket = true;
			}
		}
		//遍历右子树
		toString(root->rightChild, strExercise);
		//补上括号
		if (rChildBracket == true)
		{
			strExercise = strExercise + ")";
			rChildBracket = false;
		}
	}
	return true;
}

string Generate::getExercise(BinaryTreeNode * root)
{
	string strExercise("");
	//转换成功
	if (toString(root, strExercise))
	{
		return strExercise;
	}
	else
	{
		return string("");
	}
}
