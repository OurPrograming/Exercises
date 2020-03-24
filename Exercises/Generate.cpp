#include "Generate.h"

Generate::Generate(int range)
{
	this->range = range;
	mt.seed(randomDevice());
}

Generate::~Generate()
{

}

int Generate::getNumber()
{
	std::uniform_int_distribution<int> rand(1, range);
	return rand(mt);
}

char Generate::getOperator()
{
	std::uniform_int_distribution<int> rand(1, 4);
	
	int ran = rand(mt);
	switch (ran)
	{
	case 1:
		return '+';
	case 2:
		return '-';
	case 3:
		return '*';
	case 4:
		return '/';
	default:
		return '\0';
	}
}

BinaryTree * Generate::genExercise()
{
	//3 --> 2 --> 2
	//	 -> 3 --> 1
	
	//ÔËËã·û¸öÊı
	std::uniform_int_distribution<int> opeCount(1, 3);

	return nullptr;
}
