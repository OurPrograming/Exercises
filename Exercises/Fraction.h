#pragma once

#include <string>
#include <iostream>
#include <regex>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/*
**	 分数类，所有运算数都是此类型
*/
class  Fraction
{
public:
	 Fraction(int numerator = 0, int denominator = 1);
	 Fraction(string number);		//以字符串形式构造
	 ~Fraction();

private:
	int numerator;				//分子
	int denominator;			//分母
	int coefficient;			//系数

public:
	//set get成员
	void setNumerator(int numerator);
	int getNumerator();
	void setDenominator(int denominator);
	int getDenominator();
	int getCoefficient();

	string display();			//输出(string形式)
	void simple();				//化简，约分，带分数化
	void improper();			//假分数化

	//重载运算符
	friend Fraction operator +(Fraction a, Fraction b);
	friend Fraction operator -(Fraction a, Fraction b);
	friend Fraction operator *(Fraction a, Fraction b);
	friend Fraction operator /(Fraction a, Fraction b);

	friend bool operator >(Fraction a, Fraction b);
	friend bool operator <(Fraction a, Fraction b);
	friend bool operator ==(Fraction a, Fraction b);
	friend bool operator !=(Fraction a, Fraction b);
};