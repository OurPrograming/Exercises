#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Generate.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::fstream;

/*
**	处理命令行中传来的参数
*/
class Parameter
{
public:
	Parameter(int argc, char *argv[]);
	~Parameter();

private:
	int argc;					//argc
	vector<string> option;		//argv数组
	fstream exercises;			//习题
	fstream answers;			//答案

public:
	void generateExercises(int num, int range);		//生成题目输出到文件
	void disposeParameter();						//处理参数
};
