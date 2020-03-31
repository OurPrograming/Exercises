#pragma once

#include <string>


using std::string;
/*
**	计算类
*/
class Calculator
{
public:
	Calculator();
	~Calculator();

public:
	static bool isOperator(char ope);		//判断是否为操作符
	static int getPriority(char ope);		//返回优先级

	static double calcular(double x1, char op, double x2);   //两数四则运算

};