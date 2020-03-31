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
	Fraction getFraction();			//���ɷ���

	BinaryTree * genExercise();		//����һ����Ŀ
	void standardization(BinaryTreeNode *& root);			//��׼��һ���ڵ�(����-)	
	bool toString(BinaryTreeNode *root, string &strExercise);		//�������������׺���ʽ(string)
	string getExercise(BinaryTreeNode *root);				//ת��Ҫ�õ��ݹ飬�޷���ʼ��string
};
