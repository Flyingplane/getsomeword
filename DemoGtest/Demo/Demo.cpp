#include <iostream>
#include <string>
#include "Demo.h"
#include "GetCertainWords.h"
#include "sourceDataFile.h"
#ifdef _LLTTEST
#include <gtest/gtest.h>
#endif


// 传入参数：需转换的文件名
int main(int argc, char **argv)
{
#ifdef _LLTTEST
       std::cout << "Running main() from gtest_main,cc\n";

       testing::InitGoogleTest(&argc, argv);
       
       return RUN_ALL_TESTS();
#else
	//解决中文文件名打不开问题
	std::locale::global(std::locale(""));

	//如果没有输入参数，则默认使用source.txt文件
	string SourceFile = "source.txt" ;
	string Keywordfile = "keyword.txt";
	//打印输入的参数
	for(int i=0;i<argc;i++)
	{
		cout<<argv[i]<<'\t';
		if((i == 1) && (argv[i] != 0 ))
		{
			SourceFile = argv[i];
		}
	}
	cout<<'\n';
	
	//using namespace std ; 
	//cout << "hello world" << endl ; 
	//testForFIO();
	//cout<< "this is end!!!!" << endl ; 

	sourceTest(SourceFile , Keywordfile);
	return 0 ; 
#endif
}

