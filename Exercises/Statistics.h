#pragma once

#include <vector>
#include <fstream>
#include "Calculator.h"

using std::vector;
using std::fstream;
/*
**	统计类，对于给定题目答案的对错进行统计
*/
class Statistics
{
public:
	Statistics(string exe, string ans);
	~Statistics();

private:
	vector<int> correct;		//错的题目序号
	vector<int> wrong;			//错误题目序号

	string exePath;				//路径
	string ansPath;

	fstream exercises;			//题目文件
	fstream answers;			//题目答案
	fstream grade;				//输出到统计结果

public:
	void countResult();			//统计结果
};
