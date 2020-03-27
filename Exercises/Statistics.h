#pragma once

#include <vector>
#include <fstream>
#include "Calculator.h"

using std::vector;
using std::fstream;
/*
**	ͳ���࣬���ڸ�����Ŀ�𰸵ĶԴ����ͳ��
*/
class Statistics
{
public:
	Statistics(string exe, string ans);
	~Statistics();

private:
	vector<int> correct;		//�����Ŀ���
	vector<int> wrong;			//������Ŀ���

	string exePath;				//·��
	string ansPath;

	fstream exercises;			//��Ŀ�ļ�
	fstream answers;			//��Ŀ��
	fstream grade;				//�����ͳ�ƽ��

public:
	void countResult();			//ͳ�ƽ��
};
