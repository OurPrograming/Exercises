#include "main.h"

#include "Generate.h"

int main(int argc, char *argv[])
{
	//处理参数
	Parameter par(argc, argv); 
	par.disposeParameter();

	/*int range = 30;
	Generate *test = new Generate(range);
	BinaryTree *tree = test->genExercise();
	Generate::printTree(tree->pRoot);
	cout << endl;
	cout << Calculator::calcResult(tree->pRoot).display() << endl;
	delete test;
	delete tree;

	test = new Generate(range);
	tree = test->genExercise();
	Generate::printTree(tree->pRoot);
	cout << endl;
	cout << Calculator::calcResult(tree->pRoot).display() << endl;
	delete test;
	delete tree;*/

	//Fraction test1("4/3");
	//Fraction test2("6/4");		
	//cout << (test1 / test2).display() << endl;
	//cout << (test1 + test2).display() << endl;
	//(test1 + test2).simple();	//化简
	//cout << (test1 + test2).display() << endl;
	
	system("pause");
	return 0;
}