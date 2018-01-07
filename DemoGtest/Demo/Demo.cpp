#include <iostream>
#include <string>
#include "Demo.h"
#include "GetCertainWords.h"
#include "sourceDataFile.h"
#ifdef _LLTTEST
#include <gtest/gtest.h>
#endif


// �����������ת�����ļ���
int main(int argc, char **argv)
{
#ifdef _LLTTEST
       std::cout << "Running main() from gtest_main,cc\n";

       testing::InitGoogleTest(&argc, argv);
       
       return RUN_ALL_TESTS();
#else
	//��������ļ����򲻿�����
	std::locale::global(std::locale(""));

	//���û�������������Ĭ��ʹ��source.txt�ļ�
	string SourceFile = "source.txt" ;
	string Keywordfile = "keyword.txt";
	//��ӡ����Ĳ���
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

