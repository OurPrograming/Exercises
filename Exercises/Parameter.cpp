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
	
	//���ļ�
	exercises.open("Exercises.txt", std::ios::out | std::ios::trunc);
	answers.open("Answers.txt", std::ios::out | std::ios::trunc);
	if (!exercises.is_open() || !answers.is_open())
		return;
	
	//ÿ����һ�����ʽ��������Ԫ�رȽϣ����ظ�������
	vector<BinaryTreeNode *> exe;			//���ڴ�ű��ʽ��
	exe.reserve(num);						//Ԥ���ռ�����������

	vector<BinaryTreeNode *>::iterator ite;
	Generate *generate = generate = new Generate(range);
	BinaryTree *tree = nullptr;
	bool flag = false;					//��־�Ƿ��ظ�

	for (int i = 0; i < num; i++)			//����num��
	{
		do
		{
			tree = generate->genExercise();
			for (ite = exe.begin(); ite != exe.end(); ite++)
			{
				flag = BinaryTree::compare(tree->pRoot, *ite);
				if (flag == true)		//ƥ�䵽�ظ��������жϣ������־������
				{
					//�ظ���ɾ�����ɵ���
					delete tree;
					tree = nullptr;
					break;
				}
			}			
		} while (flag == true);

		if (flag == false)		//δ�ظ���push
		{
			exe.push_back(tree->pRoot);
		}
	}

	for (int i = 0; i < (int)exe.size(); i++)
	{
		string strExercises = generate->getExercise(exe.at(i));
		exercises << i + 1 << "." << strExercises.c_str() << endl;
		
		//ת�ɼ������������������
		BinaryTreeNode *result = Calculator::toTree(Calculator::toReversePolish(strExercises));
		string strAnswers = Calculator::calcResult(result).display();
		answers << i + 1 << "." << strAnswers.c_str() << endl;
	}

	cout << "��Ŀ�����д�뵽�ļ�" << endl;

	delete generate;
	//�ر��ļ�
	exercises.close();
	answers.close();
}

void Parameter::disposeParameter()
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
			//�õ�num�� range֮��������Ŀ�ʹ�
			generateExercises(num, range);

			//ȥͳ����
			if (option.at(1) == "-e")
			{
				Statistics statistics(option.at(2), option.at(4));
				statistics.countResult();
				cout << "ͳ�ƽ���������Grade.txt" << endl;
			}
		}
		catch (std::out_of_range)
		{
			cerr << "������ʽ����ȷ!" << endl;
		}
	}
	else
	{
		cerr << "��������ȷ�Ĳ���!" << endl << endl;
	}
}
