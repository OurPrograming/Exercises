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
	
	//���������
	std::uniform_int_distribution<int> opeCount(1, 3);
	int opeNum = opeCount(mt);

	//���½���һ����С��
	BinaryTreeNode *left = new BinaryTreeNode(std::to_string(getNumber()));
	BinaryTreeNode *right = new BinaryTreeNode(std::to_string(getNumber()));
	string *data = new string(1, getOperator());
	BinaryTreeNode *root = new BinaryTreeNode(*data, left, right);
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
		left = new BinaryTreeNode(std::to_string(getNumber()));
		right = new BinaryTreeNode(std::to_string(getNumber()));
		data = new string(1, getOperator());
		BinaryTreeNode *tempRoot = new BinaryTreeNode(*data, left, right);
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
				left = new BinaryTreeNode(std::to_string(getNumber()));
				right = root;
			}
			else			//����
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
				cerr << "���ʽ�������Ϲ淶" << endl;
				return false;
			}
			if (curPriority > leftPriority)		//���ȼ��������
			{
				cout << "(";
				lChildBracket = true;
			}
		}
		//����������
		printTree(root->leftChild);
		//��������
		if (lChildBracket == true)
		{
			cout << ")";
			lChildBracket = false;
		}
	}

	//��
	if (Calculator::isOperator(root->data.at(0)))
		cout << " " + root->data + " ";
	else
		cout << root->data;

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
				cerr << "���ʽ�������Ϲ淶" << endl;
				return false;
			}
			if (curPriority > rightPriority)		//���ȼ��������
			{
				cout << "(";
				rChildBracket = true;
			}
		}
		//����������
		printTree(root->rightChild);
		//��������
		if (rChildBracket == true)
		{
			cout << ")";
			rChildBracket = false;
		}
	}
	return true;
}
