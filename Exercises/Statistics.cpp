#include "Statistics.h"

Statistics::Statistics(string exe, string ans)
{
	this->exePath = exe;
	this->ansPath = ans;
}

Statistics::~Statistics()
{

}

void Statistics::countResult()
{
	//���ļ�
	exercises.open(exePath, std::ios::in);
	answers.open(ansPath, std::ios::in);
	grade.open("Grade.txt", std::ios::out);
	if (!exercises.is_open() || !answers.is_open() || !grade.is_open())
	{
		cerr << "�ļ���ʧ��" << endl;
	}
	
	string strExercises;		//��Ŀ(�����)
	string strAnswer;			//��(�����)

	string exe;
	string ans;
	Fraction result;

	int index;
	
	int count = 0;
	while (!exercises.eof())
	{
		//��ȡ��Ŀ�ʹ�
		std::getline(exercises, strExercises);
		std::getline(answers, strAnswer);
		
		//�ҵ���ŵ��±�
		index = strExercises.find('.');
		//��ȡ��Ŀ�ʹ�
		exe = strExercises.substr(index + 1);
		ans = strAnswer.substr(index + 1);
		count++;	//���

		//������Ŀ���
		string a = Calculator::toReversePolish(exe);
		cout << a << 'a' << endl;
		//string a = "99 6 * 9/79 /";
		//BinaryTreeNode * b = Calculator::toTree(a);

		//result = Calculator::calcResult(b);	
		result = Calculator::calcResult(Calculator::toTree(Calculator::toReversePolish(exe)));

		//�жϽ��
		if (result.display() == ans)
		{
			correct.push_back(count);
		}
		else
		{
			wrong.push_back(count);
		}
	}

	vector<int>::iterator ite;
	//��ȡ��������Ŀ�������
	//�����ȷ��ͳ����Ŀ
	grade << "Correct:" << correct.size() << "(";
	for (ite = correct.begin(); ite != correct.end(); ite++)
	{
		grade << *ite << ", ";
	}
	grade << ")" << endl;

	//�����ͬ��
	grade << "Wrong:" << wrong.size() << "(";
	for (ite = wrong.begin(); ite != wrong.end(); ite++)
	{
		grade << *ite << ", ";
	}
	grade << ")" << endl;

	//�ر��ļ�
	exercises.close();
	answers.close();
	grade.close();
}
