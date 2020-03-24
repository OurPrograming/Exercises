#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

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
	vector<string> option;		//argv转入

public:
	bool disposeParameter();	//处理参数
};
