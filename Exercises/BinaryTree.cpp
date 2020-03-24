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

void BinaryTree::push_tree(BinaryTreeNode * root)      //���������ѹ��ջ
{
	if (root != nullptr)
	{
		//��������� ���ֺ������ �ֱ�ѹ�� ����ջ�������ջ
		BinaryTree::push_tree(root->leftChild);
		if (Calculator::isOperator(root->data.at(0)))
		{
			opt_s.push(root->data.at(0));    //�����ѹ��opt_sջ
		}
		else
		{
			num.push(root->data.at(0));      //����ѹ��numջ
		}
		BinaryTree::push_tree(root->rightChild);
	}
}

double BinaryTree::calcResult()    //����������Ľ��
{
	n1 = num.top();
	op1 = opt_s.top();
	while (!num.empty())
	{
		n2 = num.top();
		op2 = opt_s.top();
		op1 = Calculator::getPriority(op1);  //��ȡ��������ȼ�
		op2 = Calculator::getPriority(op2);  //��ȡ��������ȼ�
		if (op1 >= op2)            //���ȼ��ߵ������������
		{
			n1 = Calculator::calcular(n2, op1, n1);
			opt_s.push(op2);       //���ȼ��͵������������ջ
		}
		else
		{
			n3 = num.top();        //������ȡ����
			n3 = Calculator::calcular(n3, op2, n2);  //�������ȼ��ߵ�����
			num.push(n3);          //��������ջά�ּ�������˳��
			opt_s.push(op1);
		}
	}
	re = n1;
	return re;
}
