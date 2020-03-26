#include "Fraction.h"

Fraction::Fraction(int numerator, int denominator)
{
	if (denominator == 0 || numerator < 0 || denominator < 0)
	{
		//�������������ʧ�ܣ��׳��쳣
		throw 1;
	}
	this->numerator = numerator;
	this->denominator = denominator;
	this->coefficient = 0;
}

Fraction::Fraction(string number)
{
	std::regex fraction("([0-9]*)('?)[0-9]+/[1-9]([0-9]*)");	//��������ʽ
	if (!std::regex_match(number, fraction))
	{
		//ƥ��ʧ���׳�
		throw 1;
	}
	else 
	{
		//�е���Ǵ�����
		if (std::regex_search(number, std::regex("'")))
		{
			//�õ������±�
			int index1 = number.find('\'');
			int index2 = number.find('/');
			//��ȡ��������
			this->coefficient = std::stoi(number.substr(0, index1));
			this->numerator = std::stoi(number.substr(index1 + 1, index2 - index1 - 1));
			this->denominator = std::stoi(number.substr(index2 + 1));
		}
		else
		{
			//�ָ��ַ�����ȡ��
			int index = number.find('/');		//�ҵ����ŵ��±�
			//��ȡ���Ӵ�
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
	//���� ����Ϊ0(ϵ������)�����ϵ��
	//�����(ϵ��Ϊ0�ҷ��Ӳ�Ϊ0)		a/b
	//������(ϵ����Ϊ0�ҷ��Ӳ�Ϊ0)	a'b/c
	if (numerator == 0)			//����
	{
		return string(std::to_string(coefficient));
	}
	else if (coefficient == 0)	//ϵ��Ϊ0�������
	{
		string num = std::to_string(numerator) + "/" + std::to_string(denominator);
		return string(num);
	}
	else						//ϵ����Ϊ0��������
	{
		string num1 = std::to_string(coefficient) + "'";
		string num2 = std::to_string(numerator) + "/" + std::to_string(denominator);
		return string(num1 + num2);
	}
}

void Fraction::simple()
{
	//����
	//ȡС
	int k;
	k = numerator < denominator ? numerator : denominator;
	
	for (int i = 2; i <= k; i++)
	{
		//���i�������ͻ���(��Ҫ���)
		while ( (numerator % i == 0) && (denominator % i == 0) )
		{
			numerator /= i;
			denominator /= i;
		}
	}

	//����ɴ�����
	while (numerator >= denominator)
	{
		//���Ӽ�һ�η�ĸ��ϵ����1
		numerator -= denominator;
		coefficient++;
	}
}

void Fraction::improper()
{
	//ϵ���˷�ĸ
	numerator += coefficient * denominator;
	coefficient = 0;
}

Fraction operator+(Fraction a, Fraction b)
{
	Fraction result;
	//ϵ��������ӣ���������ͨ�����
	result.coefficient = a.coefficient + b.coefficient;
	result.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	return result;
}

Fraction operator-(Fraction a, Fraction b)
{
	Fraction result;
	//ϵ�������������������ͨ�����
	result.coefficient = a.coefficient - b.coefficient;
	result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	return result;
}

Fraction operator*(Fraction a, Fraction b)
{
	//�Ȼ��ɼٷ���
	a.improper();
	b.improper();

	//������
	Fraction result;
	result.numerator = a.numerator * b.numerator;
	result.denominator = a.denominator * b.denominator;
	result.simple();

	//��a b�����ȥ
	a.simple();
	b.simple();
	return result;
}

Fraction operator/(Fraction a, Fraction b)
{
	//�Ȼ��ɼٷ���
	a.improper();
	b.improper();

	//������
	Fraction result;
	result.numerator = a.numerator * b.denominator;
	result.denominator = a.denominator * b.numerator;
	result.simple();

	//��a b�����ȥ
	a.simple();
	b.simple();
	return result;
}

bool operator>(Fraction a, Fraction b)
{
	//��Ϊ�ٷ���
	a.improper();
	b.improper();

	//������ֵ
	double trueNumA = (double)a.numerator / (double)a.denominator;
	double trueNumB = (double)b.numerator / (double)b.denominator;

	//����ǰ����
	a.simple();
	b.simple();

	if (trueNumA > trueNumB)
		return true;
	else
		return false;
}

bool operator<(Fraction a, Fraction b)
{
	//��Ϊ�ٷ���
	a.improper();
	b.improper();

	//������ֵ
	double trueNumA = (double)a.numerator / (double)a.denominator;
	double trueNumB = (double)b.numerator / (double)b.denominator;

	//����ǰ����
	a.simple();
	b.simple();

	if (trueNumA < trueNumB)
		return true;
	else
		return false;
}

bool operator==(Fraction a, Fraction b)
{
	//��Ϊ�ٷ���
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
	//��Ϊ�ٷ���
	a.improper();
	b.improper();

	bool flag = false;
	if (a.numerator * b.denominator != a.denominator * b.numerator)
		flag = true;

	a.simple();
	b.simple();
	return flag;
}
