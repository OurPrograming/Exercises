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
	//打开文件
	exercises.open(exePath, std::ios::in);
	answers.open(ansPath, std::ios::in);
	grade.open("Grade.txt", std::ios::out);
	if (!exercises.is_open() || !answers.is_open() || !grade.is_open())
	{
		cerr << "文件打开失败" << endl;
	}
	
	string strExercises;		//题目(带序号)
	string strAnswer;			//答案(带序号)

	string exe;
	string ans;
	Fraction result;

	int index;
	
	int count = 0;
	while (!exercises.eof())
	{
		//读取题目和答案
		std::getline(exercises, strExercises);
		std::getline(answers, strAnswer);
		
		//找到点号的下标
		index = strExercises.find('.');
		//提取题目和答案
		exe = strExercises.substr(index + 1);
		ans = strAnswer.substr(index + 1);
		count++;	//题号

		//计算题目结果
		string a = Calculator::toReversePolish(exe);
		cout << a << 'a' << endl;
		//string a = "99 6 * 9/79 /";
		//BinaryTreeNode * b = Calculator::toTree(a);

		//result = Calculator::calcResult(b);	
		result = Calculator::calcResult(Calculator::toTree(Calculator::toReversePolish(exe)));

		//判断结果
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
	//读取完所有题目进行输出
	//输出正确的统计数目
	grade << "Correct:" << correct.size() << "(";
	for (ite = correct.begin(); ite != correct.end(); ite++)
	{
		grade << *ite << ", ";
	}
	grade << ")" << endl;

	//错误的同理
	grade << "Wrong:" << wrong.size() << "(";
	for (ite = wrong.begin(); ite != wrong.end(); ite++)
	{
		grade << *ite << ", ";
	}
	grade << ")" << endl;

	//关闭文件
	exercises.close();
	answers.close();
	grade.close();
}
