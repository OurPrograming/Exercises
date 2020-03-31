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
**	生成表达式
*/
class Generate
{
public:
	Generate(int range);
	~Generate();

private:
	int range;

	//随机数引擎
	std::random_device randomDevice;
	std::mt19937 mt;

public:
	int getNumber();				//取随机数
	char getOperator();				//取操作符
	Fraction getFraction();			//生成分数

	BinaryTree * genExercise();		//生成一道题目
	void standardization(BinaryTreeNode *& root);			//标准化一个节点(处理-)	
	bool toString(BinaryTreeNode *root, string &strExercise);		//带括号输出成中缀表达式(string)
	string getExercise(BinaryTreeNode *root);				//转换要用到递归，无法初始化string
};
