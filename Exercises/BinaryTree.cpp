#include "BinaryTree.h"

BinaryTree::BinaryTree(BinaryTreeNode *root)
{
	pRoot = root;
}

BinaryTree::BinaryTree(const BinaryTree & tree)
{
	pRoot = copy(tree.pRoot);
}

BinaryTree::~BinaryTree()
{
	destroy(pRoot);
}

void BinaryTree::destroy(BinaryTreeNode * &root)
{
	if (root != nullptr)
	{
		destroy(root->leftChild);
		destroy(root->rightChild);

		delete root;
		root = nullptr;
	}
}

BinaryTreeNode * BinaryTree::copy(BinaryTreeNode * root)
{
	if (root != nullptr)
	{
		//������ ���Ǹ�ֵ����������ֱ����ָ�����
		//�½�һ�������ѽڵ����ݸ��ƹ�ȥ
		BinaryTreeNode *newRoot = new BinaryTreeNode(root->data);
		newRoot->leftChild = copy(root->leftChild);
		newRoot->rightChild = copy(root->rightChild);
		return newRoot;
	}
	return nullptr;
}

bool BinaryTree::printTree(BinaryTreeNode * root)
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

bool BinaryTree::compare(BinaryTreeNode * tree1, BinaryTreeNode * tree2)
{
	//���ڵ�
	if (tree1->data != tree2->data)
		return false;

	//���Һ��Ӷ����
	if (compare(tree1->leftChild, tree2->leftChild) == true)
	{
		if (compare(tree1->rightChild, tree2->rightChild) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//�������
	if (compare(tree1->leftChild, tree2->rightChild) == true)
	{
		if (compare(tree1->rightChild, tree2->leftChild) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

void BinaryTree::calcResult(BinaryTreeNode * root)   //����������Ľ��
{
	if (root != nullptr)
	{
		calcResult(root->leftChild);
		calcResult(root->rightChild);
		if (Calculator::isOperator(root->data.at(0)))
		{
			num.push(root->data.at(0));    //�����ѹ��numջ
		}
		else
		{   //���Ϊ�����ʱ��������
			n1 = num.top();  num.pop();
			n2 = num.top();  num.pop();
			n3 = Calculator::calcular(n3, root->data.at(0), n2);
			num.push(n3);   //������ѹ��ջ
		}
	}
}

double BinaryTree::Result(BinaryTreeNode * root)    //����������Ľ��
{
	calcResult(root);
	re = num.top();  num.pop();  //��ȡ��������ɾ��ջ��Ԫ��
	return re;
}
