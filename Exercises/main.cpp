#include "main.h"

int main(int argc, char *argv[])
{
	//处理参数
	Parameter par(argc, argv); 
	par.disposeParameter();

	system("pause");
	return 0;
}