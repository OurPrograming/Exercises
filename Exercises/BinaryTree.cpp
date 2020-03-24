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
		//复制树 不是赋值给树，不能直接让指针相等
		//新建一棵树并把节点内容复制过去
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

bool BinaryTree::compare(BinaryTreeNode * tree1, BinaryTreeNode * tree2)
{
	//根节点
	if (tree1->data != tree2->data)
		return false;

	//左右孩子都相等
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

	//交换相等
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

void BinaryTree::push_tree(BinaryTreeNode * root)      //把树各结点压入栈
{
	if (root != nullptr)
	{
		//中序遍历将 数字和运算符 分别压入 数字栈和运算符栈
		BinaryTree::push_tree(root->leftChild);
		if (Calculator::isOperator(root->data.at(0)))
		{
			opt_s.push(root->data.at(0));    //运算符压入opt_s栈
		}
		else
		{
			num.push(root->data.at(0));      //数字压入num栈
		}
		BinaryTree::push_tree(root->rightChild);
	}
}

double BinaryTree::calcResult()    //计算这棵树的结果
{
	n1 = num.top();
	op1 = opt_s.top();
	while (!num.empty())
	{
		n2 = num.top();
		op2 = opt_s.top();
		op1 = Calculator::getPriority(op1);  //获取运算符优先级
		op2 = Calculator::getPriority(op2);  //获取运算符优先级
		if (op1 >= op2)            //优先级高的运算符做运算
		{
			n1 = Calculator::calcular(n2, op1, n1);
			opt_s.push(op2);       //优先级低的运算符重新入栈
		}
		else
		{
			n3 = num.top();        //重新提取数字
			n3 = Calculator::calcular(n3, op2, n2);  //计算优先级高的运算
			num.push(n3);          //运算结果入栈维持计算数据顺序
			opt_s.push(op1);
		}
	}
	re = n1;
	return re;
}
