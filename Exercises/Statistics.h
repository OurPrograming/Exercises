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
	vector<int> number;			//错的题目序号

	fstream exercises;			//题目文件
	fstream answers;			//题目答案
	fstream grate;				//输出到统计结果

public:
	void countResult();			//统计结果
};
