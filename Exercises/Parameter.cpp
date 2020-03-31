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

void Parameter::generateExercises(int num, int range)
{
	if (num == 0 || range == 0)
		return;
	
	//打开文件
	exercises.open("Exercises.txt", std::ios::out | std::ios::trunc);
	answers.open("Answers.txt", std::ios::out | std::ios::trunc);
	if (!exercises.is_open() || !answers.is_open())
		return;
	
	//每生成一个表达式都与其他元素比较，不重复就入组
	vector<BinaryTreeNode *> exe;			//用于存放表达式树
	exe.reserve(num);						//预留空间避免过多扩容

	vector<BinaryTreeNode *>::iterator ite;
	Generate *generate = generate = new Generate(range);
	BinaryTree *tree = nullptr;
	bool flag = false;					//标志是否重复

	for (int i = 0; i < num; i++)			//生成num个
	{
		do
		{
			tree = generate->genExercise();
			for (ite = exe.begin(); ite != exe.end(); ite++)
			{
				flag = BinaryTree::compare(tree->pRoot, *ite);
				if (flag == true)		//匹配到重复就跳出判断，避免标志被更改
				{
					//重复就删除生成的树
					delete tree;
					tree = nullptr;
					break;
				}
			}			
		} while (flag == true);

		if (flag == false)		//未重复就push
		{
			exe.push_back(tree->pRoot);
		}
	}

	for (int i = 0; i < (int)exe.size(); i++)
	{
		string strExercises = generate->getExercise(exe.at(i));
		exercises << i + 1 << "." << strExercises.c_str() << endl;
		
		//转成计算器计算结果避免出错
		BinaryTreeNode *result = Calculator::toTree(Calculator::toReversePolish(strExercises));
		string strAnswers = Calculator::calcResult(result).display();
		answers << i + 1 << "." << strAnswers.c_str() << endl;
	}

	cout << "题目与答案已写入到文件" << endl;

	delete generate;
	//关闭文件
	exercises.close();
	answers.close();
}

void Parameter::disposeParameter()
{
	int num = 0;
	//	-n 10 题目数量10
	int range = 0;
	//	-r 10 自然数、分数值、分数分母的最大值
	//	-e exercises.txt -a answers.txt		打开题目文件和答案并判断对错
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

			if (option.at(1) == "-r" || option.at(3) == "-r")
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
			//得到num， range之后生成题目和答案
			generateExercises(num, range);

			//去统计类
			if (option.at(1) == "-e")
			{
				Statistics statistics(option.at(2), option.at(4));
				statistics.countResult();
				cout << "统计结果已输出到Grade.txt" << endl;
			}
		}
		catch (std::out_of_range)
		{
			cerr << "参数格式不正确!" << endl;
		}
	}
	else
	{
		cerr << "请输入正确的参数!" << endl << endl;
	}
}
