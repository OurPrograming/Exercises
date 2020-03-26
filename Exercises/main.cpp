#include "main.h"

#include "Generate.h"

int main(int argc, char *argv[])
{
	/*//处理参数
	Parameter par(argc, argv); 
	par.disposeParameter();*/

	/*Generate *test = new Generate(30);
	BinaryTree *tree = test->genExercise();
	test->printTree(tree->pRoot);
	cout << endl << Calculator::calcResult(tree->pRoot);*/

	Fraction test1("4/3");
	Fraction test2("6/4");		
	cout << (test1 / test2).display() << endl;
	/*cout << (test1 + test2).display() << endl;
	(test1 + test2).simple();	//化简
	cout << (test1 + test2).display() << endl;*/
	
	system("pause");
	return 0;
}