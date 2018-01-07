#include <iostream>
#include <string>
#include "Demo.h"
#include "GetCertainWords.h"
#include "sourceDataFile.h"
#ifdef _LLTTEST
#include <gtest/gtest.h>
#endif

//´ý²âº¯Êý
int Plus(int a, int b)
{
       return a + b;
}

int main(int argc, char **argv)
{
#ifdef _LLTTEST
       std::cout << "Running main() from gtest_main,cc\n";

       testing::InitGoogleTest(&argc, argv);
       
       return RUN_ALL_TESTS();
#else
	using namespace std ; 
	cout << "hello world" << endl ; 
	testForFIO();
	cout<< "this is end!!!!" << endl ; 

	sourceTest("source.txt");
	return 0 ; 
#endif
}

void sort(char *p , int length )
{
	char temp = 0 ; 
	for(int i = 0 ; i < length-1 ; i++ )
		for( int j = 0 ; j < length-1-i ; j++ )
		{
			if(  p[j] > p[j+1] ) 
			{
				temp = p[j+1];
				p[j+1] = p[j];
				p[j] = temp ; 
			}
		}
}