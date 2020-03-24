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

		BinaryTree *tree = new BinaryTree(root);
		return tree;
	}
	else		//���ϲ�
	{
		
	}
	
	return nullptr;
}
