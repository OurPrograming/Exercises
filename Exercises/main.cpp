#include "main.h"

#include "Generate.h"

int main(int argc, char *argv[])
{
	/*//处理参数
	Parameter par(argc, argv); 
	par.disposeParameter();*/

	Generate *test = new Generate(30);
	BinaryTree *tree = test->genExercise();
	test->printTree(tree->pRoot);
	cout << endl << Calculator::calcResult(tree->pRoot);
	
	system("pause");
	return 0;
}