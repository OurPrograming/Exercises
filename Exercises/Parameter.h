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
**	�����������д����Ĳ���
*/
class Parameter
{
public:
	Parameter(int argc, char *argv[]);
	~Parameter();

private:
	int argc;					//argc
	vector<string> option;		//argv����
	fstream exercises;			//ϰ��
	fstream answers;			//��

public:
	void generateExercises(int num, int range);		//������Ŀ������ļ�
	void disposeParameter();						//�������
};
