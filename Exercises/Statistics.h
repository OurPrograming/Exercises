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
	vector<int> number;			//�����Ŀ���

	fstream exercises;			//��Ŀ�ļ�
	fstream answers;			//��Ŀ��
	fstream grate;				//�����ͳ�ƽ��

public:
	void countResult();			//ͳ�ƽ��
};
