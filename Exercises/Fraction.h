#pragma once

#include <string>
#include <iostream>
#include <regex>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

/*
**	 �����࣬�������������Ǵ�����
*/
class  Fraction
{
public:
	 Fraction(int numerator = 0, int denominator = 1);
	 Fraction(string number);		//���ַ�����ʽ����
	 ~Fraction();

private:
	int numerator;				//����
	int denominator;			//��ĸ
	int coefficient;			//ϵ��

public:
	//set get��Ա
	void setNumerator(int numerator);
	int getNumerator();
	void setDenominator(int denominator);
	int getDenominator();
	int getCoefficient();

	string display();			//���(string��ʽ)
	void simple();				//����Լ�֣���������
	void improper();			//�ٷ�����

	//���������
	friend Fraction operator +(Fraction a, Fraction b);
	friend Fraction operator -(Fraction a, Fraction b);
	friend Fraction operator *(Fraction a, Fraction b);
	friend Fraction operator /(Fraction a, Fraction b);

	friend bool operator >(Fraction a, Fraction b);
	friend bool operator <(Fraction a, Fraction b);
	friend bool operator ==(Fraction a, Fraction b);
	friend bool operator !=(Fraction a, Fraction b);
};