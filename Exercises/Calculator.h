#pragma once

#include <string>


using std::string;
/*
**	������
*/
class Calculator
{
public:
	Calculator();
	~Calculator();

public:
	static bool isOperator(char ope);		//�ж��Ƿ�Ϊ������
	static int getPriority(char ope);		//�������ȼ�

	static double calcular(double x1, char op, double x2);   //������������

};