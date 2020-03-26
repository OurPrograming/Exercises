#include "Fraction.h"

Fraction::Fraction(int numerator, int denominator)
{
	if (denominator == 0 || numerator < 0 || denominator < 0)
	{
		//不符合情况构造失败，抛出异常
		throw 1;
	}
	this->numerator = numerator;
	this->denominator = denominator;
	this->coefficient = 0;
}

Fraction::Fraction(string number)
{
	std::regex fraction("([0-9]*)('?)[0-9]+/[1-9]([0-9]*)");	//分数的形式
	if (!std::regex_match(number, fraction))
	{
		//匹配失败抛出
		throw 1;
	}
	else 
	{
		//有点就是带分数
		if (std::regex_search(number, std::regex("'")))
		{
			//得到两个下标
			int index1 = number.find('\'');
			int index2 = number.find('/');
			//提取出三个数
			this->coefficient = std::stoi(number.substr(0, index1));
			this->numerator = std::stoi(number.substr(index1 + 1, index2 - index1 - 1));
			this->denominator = std::stoi(number.substr(index2 + 1));
		}
		else
		{
			//分割字符串来取数
			int index = number.find('/');		//找到除号的下标
			//提取出子串
			this->numerator = std::stoi(number.substr(0, index));
			this->denominator = std::stoi(number.substr(index + 1));
			this->coefficient = 0;
		}
	}
}

Fraction::~Fraction()
{

}

void Fraction::setNumerator(int numerator)
{
	this->numerator = numerator;
}

int Fraction::getNumerator()
{
	return this->numerator;
}

void Fraction::setDenominator(int denominator)
{
	this->denominator = denominator;
}

int Fraction::getDenominator()
{
	return this->denominator;
}

int Fraction::getCoefficient()
{
	return this->coefficient;
}

string Fraction::display()
{
	//整数 分子为0(系数任意)，输出系数
	//真分数(系数为0且分子不为0)		a/b
	//带分数(系数不为0且分子不为0)	a'b/c
	if (numerator == 0)			//整数
	{
		return string(std::to_string(coefficient));
	}
	else if (coefficient == 0)	//系数为0，真分数
	{
		string num = std::to_string(numerator) + "/" + std::to_string(denominator);
		return string(num);
	}
	else						//系数不为0，带分数
	{
		string num1 = std::to_string(coefficient) + "'";
		string num2 = std::to_string(numerator) + "/" + std::to_string(denominator);
		return string(num1 + num2);
	}
}

void Fraction::simple()
{
	//化简
	//取小
	int k;
	k = numerator < denominator ? numerator : denominator;
	
	for (int i = 2; i <= k; i++)
	{
		//如果i能整除就化简(需要多次)
		while ( (numerator % i == 0) && (denominator % i == 0) )
		{
			numerator /= i;
			denominator /= i;
		}
	}

	//处理成带分数
	while (numerator >= denominator)
	{
		//分子减一次分母，系数加1
		numerator -= denominator;
		coefficient++;
	}
}

void Fraction::improper()
{
	//系数乘分母
	numerator += coefficient * denominator;
	coefficient = 0;
}

Fraction operator+(Fraction a, Fraction b)
{
	Fraction result;
	//系数部分相加，分数部分通分相加
	result.coefficient = a.coefficient + b.coefficient;
	result.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	return result;
}

Fraction operator-(Fraction a, Fraction b)
{
	Fraction result;
	//系数部分相减，分数部分通分相减
	result.coefficient = a.coefficient - b.coefficient;
	result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	return result;
}

Fraction operator*(Fraction a, Fraction b)
{
	//先化成假分数
	a.improper();
	b.improper();

	//计算结果
	Fraction result;
	result.numerator = a.numerator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	//把a b化简回去
	a.simple();
	b.simple();
	return result;
}

Fraction operator/(Fraction a, Fraction b)
{
	//先化成假分数
	a.improper();
	b.improper();

	//计算结果
	Fraction result;
	result.numerator = a.numerator * b.denominator;
	result.denominator = a.denominator * b.numerator;
	result.simple();

	//把a b化简回去
	a.simple();
	b.simple();
	return result;
}

bool operator>(Fraction a, Fraction b)
{
	//化为假分数
	a.improper();
	b.improper();

	//计算真值
	double trueNumA = (double)a.numerator / (double)a.denominator;
	double trueNumB = (double)b.numerator / (double)b.denominator;

	//返回前化简
	a.simple();
	b.simple();

	if (trueNumA > trueNumB)
		return true;
	else
		return false;
}

bool operator<(Fraction a, Fraction b)
{
	//化为假分数
	a.improper();
	b.improper();

	//计算真值
	double trueNumA = (double)a.numerator / (double)a.denominator;
	double trueNumB = (double)b.numerator / (double)b.denominator;

	//返回前化简
	a.simple();
	b.simple();

	if (trueNumA < trueNumB)
		return true;
	else
		return false;
}

bool operator==(Fraction a, Fraction b)
{
	//化为假分数
	a.improper();
	b.improper();

	bool flag = false;
	if (a.numerator * b.denominator == a.denominator * b.numerator)
		flag = true;

	a.simple();
	b.simple();
	return flag;
}

bool operator!=(Fraction a, Fraction b)
{
	//化为假分数
	a.improper();
	b.improper();

	bool flag = false;
	if (a.numerator * b.denominator != a.denominator * b.numerator)
		flag = true;

	a.simple();
	b.simple();
	return flag;
}
