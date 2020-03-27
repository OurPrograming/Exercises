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
	//��ѡһ ����0���Ƿ���1
	std::uniform_int_distribution<int> randBool(0, 1);
	if (randBool(mt) == 0)		//����
	{
		Fraction number(getNumber());	//��ĸĬ��ֵΪ1
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
	
	//���������
	std::uniform_int_distribution<int> opeCount(1, 3);
	int opeNum = opeCount(mt);

	//���½���һ����С��
	BinaryTreeNode *left = new BinaryTreeNode(getFraction().display());
	BinaryTreeNode *right = new BinaryTreeNode(getFraction().display());
	string *data = new string(1, getOperator());
	BinaryTreeNode *root = new BinaryTreeNode(*data, left, right);
	standardization(root);
	opeNum--;

	if (opeNum == 0)		//��������ֻ��һ��ֱ�ӷ���
	{
		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}

	//���ڶ�ѡһ�������
	std::uniform_int_distribution<int> randBool(0, 1);

	//ѡ����һ����2��3
	if (randBool(mt) == 0 && opeNum == 2)	//������һ����С��������
	{
		left = new BinaryTreeNode(getFraction().display());
		right = new BinaryTreeNode(getFraction().display());
		data = new string(1, getOperator());
		BinaryTreeNode *tempRoot = new BinaryTreeNode(*data, left, right);
		standardization(tempRoot);
		opeNum--;

		//ѡ������˳��
		if (randBool(mt) == 0)	//��������
		{
			left = tempRoot;
			right = root;
		}
		else
		{
			left = root;
			right = tempRoot;
		}
		//����
		data = new string(1, getOperator());
		root = new BinaryTreeNode(*data, left, right);
		standardization(root);
		opeNum--;

		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}
	else		//���ϲ�
	{
		do
		{	
			//��ѡһ ����or����
			if (randBool(mt) == 0)	//����
			{
				left = new BinaryTreeNode(getFraction().display());
				right = root;
			}
			else			//����
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
		if (left < right)		//С�ھͷ���
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

	bool lChildBracket = false, rChildBracket = false;			//��־����
	int leftPriority = 0, curPriority = 0, rightPriority = 0;	//���ȼ�

	//�������
	if (root->leftChild != nullptr)
	{
		//�������ǲ�����������
		if (Calculator::isOperator(root->leftChild->data.at(0)))
		{
			//�õ����ȼ�
			leftPriority = Calculator::getPriority(root->leftChild->data.at(0));
			curPriority = Calculator::getPriority(root->data.at(0));
			if (leftPriority == 0 || curPriority == 0)
			{
				return false;
			}
			if (curPriority > leftPriority)		//���ȼ��������
			{
				strExercise = strExercise +  "(";
				lChildBracket = true;
			}
		}
		//����������
		toString(root->leftChild, strExercise);
		//��������
		if (lChildBracket == true)
		{
			strExercise = strExercise + ")";
			lChildBracket = false;
		}
	}

	//��
	if (Calculator::isOperator(root->data.at(0)))
		strExercise = strExercise + " " + root->data + " ";
	else
		strExercise = strExercise + root->data;

	//��
	if (root->rightChild != nullptr)
	{
		//�������ǲ�����������
		if (Calculator::isOperator(root->rightChild->data.at(0)))
		{
			//�õ����ȼ�
			rightPriority = Calculator::getPriority(root->rightChild->data.at(0));
			curPriority = Calculator::getPriority(root->data.at(0));
			if (rightPriority == 0 || curPriority == 0)
			{
				return false;
			}
			if (curPriority > rightPriority)		//���ȼ��������
			{
				strExercise = strExercise + "(";
				rChildBracket = true;
			}
		}
		//����������
		toString(root->rightChild, strExercise);
		//��������
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
	//ת���ɹ�
	if (toString(root, strExercise))
	{
		return strExercise;
	}
	else
	{
		return string("");
	}
}
