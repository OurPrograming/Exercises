#include "Parameter.h"

Parameter::Parameter(int argc, char * argv[])
{
	this->argc = argc;
	
	int i;
	for (i = 0; i < argc; i++)
	{
		option.push_back(argv[i]);
	}
}

Parameter::~Parameter()
{
	option.clear();
}

bool Parameter::disposeParameter()
{
	int num = 0;
	//	-n 10 ��Ŀ����10
	int range = 0;
	//	-r 10 ��Ȼ��������ֵ��������ĸ�����ֵ
	//	-e exercises.txt -a answers.txt		����Ŀ�ļ��ʹ𰸲��ж϶Դ�
	if (argc >= 2)
	{
		try
		{
			if (option.at(1) == "-n" || option.at(3) == "-n")
			{
				if (option.at(1) == "-n")
				{
					//string to int
					num = std::stoi(option.at(2));
				}
				else
				{
					num = std::stoi(option.at(4));
				}
			}

			if (option.at(1) == "-r" || option.at(3) == "r")
			{
				if (option.at(1) == "-r")
				{
					//string to int
					range = std::stoi(option.at(2));
				}
				else
				{
					range = std::stoi(option.at(4));
				}
			}

			//ȥͳ����
			if (option.at(1) == "-e")
			{

			}
		}
		catch (std::out_of_range)
		{
			cerr << "������ʽ����ȷ!" << endl;
		}
	}

	cerr << "��������ȷ�Ĳ���!" << endl << endl;
	return false;
}
