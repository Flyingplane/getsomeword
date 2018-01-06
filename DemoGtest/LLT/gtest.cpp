#ifdef _LLTTEST
#include <gtest/gtest.h>
#include "../Demo/Demo.h"
#include "../Demo/GetCertainWords.h"
#include "../Demo/filetodeal.h"
#include "../Demo/common_data.h"

//²âÊÔº¯Êý

TEST(PlusTest, FTest)

{
		int a = 11 ; 
       EXPECT_EQ(2, Plus(1, 1));
		EXPECT_EQ(6 , Plus(3 , 3)) << "3+3 = " <<a;

}

TEST(PlusTest, TEST22)
{
 EXPECT_EQ(2, Plus(1, 1));
}

TEST(findKeyStrInStrHead , TEST1)
{
	char* p_Src  = "Base part according to the electrical characteristics of the base, using dual MCU structure: power part and logic part. In the design of the main power circuit, this paper analyzes the basic principle of the electromagnetic heating circuit, and analyzes the single cycle waveform of the resonant circuit. On the basis of the principle analysis, this paper further analyzes the meaning and main problems of IGBT soft-opening in electromagnetic heating circuit. Finally, this paper presents a PWM-based PWM control scheme, and in hardware and software implementation, The core part: synchronous drive, overcurrent protection, IGBT overvoltage protection and so do a detailed analysis. For the dual-MCU structure, this paper proposes a structure based on data synchronization to synchronize the program, and finally realize the structure of the communication between the master and slave MCU and the function code. In addition the base part of the design, taking full account of a variety of abnormal circumstances such as automatic protection: for example, input overvoltage undervoltage protection, IGBT over-temperature protection and so on.";
	char* p_key  = "Base part";
	char* p_key1 = "so on";
	char* p_key2 = "circuit, this paper analyzes the basic principle of the electromagnetic heating circuit, and analyzes the single cycle waveform of the resonant circuit. On the basis of the principle analysis, this paper further analyzes the meaning and main problems of IGBT soft-opening in electromagnetic heating circuit. Finally, this paper presents a PWM-based PWM control scheme, and in hardware and software implementation, The core part: synchronous drive, overcurrent protection, IGBT overvoltage protection and so do a detailed analysis. For the dual-MCU structure, this paper proposes a structure based on data synchronization to synchronize the program, and finally realize the structure of the communication between the master and slave MCU and the function code. In addition the base part of the design, taking full account of a variety of abnormal circumstances such as automatic protection: for example, input overvoltage undervoltage protection, IGBT over-temperature protection and so on.";
	char* p_key3 = "Base part according to the electrical characteristics of the base, using dual MCU";

	EXPECT_EQ(findKeyStrInStrHead(p_Src , p_key) , ERR_SUCCESS);
	EXPECT_EQ(findKeyStrInStrHead(p_Src , p_key1) , ERR_FAILURE);
	EXPECT_EQ(findKeyStrInStrHead(p_Src , p_key2) , ERR_FAILURE);
	EXPECT_EQ(findKeyStrInStrHead(p_Src , p_key3) , ERR_SUCCESS);

}

TEST(findKeyStrInStr , TEST2)
{
	char* p_Src  = "Base part according to the electrical characteristics of the base, using dual MCU structure: power part and logic part. In the design of the main power circuit, this paper analyzes the basic principle of the electromagnetic heating circuit, and analyzes the single cycle waveform of the resonant circuit. On the basis of the principle analysis, this paper further analyzes the meaning and main problems of IGBT soft-opening in electromagnetic heating circuit. Finally, this paper presents a PWM-based PWM control scheme, and in hardware and software implementation, The core part: synchronous drive, overcurrent protection, IGBT overvoltage protection and so do a detailed analysis. For the dual-MCU structure, this paper proposes a structure based on data synchronization to synchronize the program, and finally realize the structure of the communication between the master and slave MCU and the function code. In addition the base part of the design, taking full account of a variety of abnormal circumstances such as automatic protection: for example, input overvoltage undervoltage protection, IGBT over-temperature protection and so on.";
	char* p_key  = "Base part";
	char* p_key1 = "so on";
	char* p_key2 = "circuit, this paper analyzes the basic principle of the electromagnetic heating circuit, and analyzes the single cycle waveform of the resonant circuit. On the basis of the principle analysis, this paper further analyzes the meaning and main problems of IGBT soft-opening in electromagnetic heating circuit. Finally, this paper presents a PWM-based PWM control scheme, and in hardware and software implementation, The core part: synchronous drive, overcurrent protection, IGBT overvoltage protection and so do a detailed analysis. For the dual-MCU structure, this paper proposes a structure based on data synchronization to synchronize the program, and finally realize the structure of the communication between the master and slave MCU and the function code. In addition the base part of the design, taking full account of a variety of abnormal circumstances such as automatic protection: for example, input overvoltage undervoltage protection, IGBT over-temperature protection and so on.";
	char* p_key3 = "part according to the electrical characteristics of the base, using dual MCU";
	char* p_key4 = "Base Part";
	char* p_key5 = " so on.oooo";
	int PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key , PosTemp) , ERR_SUCCESS);
	EXPECT_EQ(PosTemp , 0 );
	PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key1 , PosTemp) , ERR_SUCCESS);
	EXPECT_EQ(PosTemp , 1135 );
	PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key2 , PosTemp) , ERR_SUCCESS);
	EXPECT_EQ(PosTemp , 152 );
	PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key3 , PosTemp) , ERR_SUCCESS);
	EXPECT_EQ(PosTemp , 5 );
	PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key4 , PosTemp) , ERR_FAILURE);
	EXPECT_EQ(PosTemp , 1141 );
	PosTemp = -1 ; 
	EXPECT_EQ(findKeyStrInStr(p_Src , p_key5 , PosTemp) , ERR_FAILURE);
	EXPECT_EQ(PosTemp , 1141 );

	testForFIO();

}
TEST(GetAllKeyStrInStr , TEST3)
{
	//char* p_Src  = "Base part according to the electrical characteristics of the base, using dual MCU structure: power part and logic part. In the design of the main power circuit, this paper analyzes the basic principle of the electromagnetic heating circuit, and analyzes the single cycle waveform of the resonant circuit. On the basis of the principle analysis, this paper further analyzes the meaning and main problems of IGBT soft-opening in electromagnetic heating circuit. Finally, this paper presents a PWM-based PWM control scheme, and in hardware and software implementation, The core part: synchronous drive, overcurrent protection, IGBT overvoltage protection and so do a detailed analysis. For the dual-MCU structure, this paper proposes a structure based on data synchronization to synchronize the program, and finally realize the structure of the communication between the master and slave MCU and the function code. In addition the base part of the design, taking full account of a variety of abnormal circumstances such as automatic protection: for example, input overvoltage undervoltage protection, IGBT over-temperature protection and so on.";
	//char* p_key  = "part";
	//int TotalNum = 0;
	//GetAllKeyStrInStr( p_Src , p_key , TotalNum );
	//EXPECT_EQ( 5 , TotalNum );
	//GetAllKeyStrInStr( p_Src , "circuit" , TotalNum );
	//EXPECT_EQ( 9 , TotalNum );

}


//test for class KeyWordFile
char g_keywordTestFile1[] = "keywordstest1.txt";
char g_keywordTestFileFail[] = "keywordstestFail.txt";

TEST(KeyWordFile , Initialize_OK)
{
	KeyWordFile keyWords;
	EXPECT_EQ(keyWords.Initialize(g_keywordTestFile1 ) , ERR_SUCCESS);
	keyWords.showKeyWords();
}
TEST(KeyWordFile , Initialize_Fail)
{
	KeyWordFile keyWords;
	EXPECT_EQ(keyWords.Initialize(g_keywordTestFileFail ) , ERR_FAILURE);
	keyWords.showKeyWords();
}


//test for class filetodeal
char g_sourceDataTestFile1[] = "sourcetest1.txt";
char g_sourceDataTestFileFail[] = "sourcetestFail.txt";

TEST(filetodeal , Initialize_OK)
{
	filetodeal fileData;
	EXPECT_EQ(fileData.Initialize(g_sourceDataTestFile1) , ERR_SUCCESS );
	fileData.showKeyWords();
}
TEST(filetodeal , Initialize_FAIL)
{
	filetodeal fileData;
	EXPECT_EQ(fileData.Initialize(g_sourceDataTestFileFail) , ERR_FAILURE );
	fileData.showKeyWords();
}
#endif 


