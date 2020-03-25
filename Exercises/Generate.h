#pragma once

#include <random>
#include <iostream>
#include <string>
#include "BinaryTree.h"
#include "Calculator.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
/*
**	���ɱ��ʽ
*/
class Generate
{
public:
	Generate(int range);
	~Generate();

private:
	int range;

	//���������
	std::random_device randomDevice;
	std::mt19937 mt;

public:
	int getNumber();				//ȡ�����
	char getOperator();				//ȡ������
	string getFraction();			//���ɷ���

	BinaryTree * genExercise();		//����һ����Ŀ
	bool printTree(BinaryTreeNode *root);		//�������������׺���ʽ
};
