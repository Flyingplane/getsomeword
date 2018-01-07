#include "GetCertainWords.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <afx.h>
using namespace std;

const char *g_pSourceFile = "source.txt";
const char *g_pKeyWord = "keyword.txt";
const char *g_pReslultFile = "result.csv";

// ��Src��ͷ����ʼ����KeyStr���ֶΣ����Src��ͷ���ֶ���KeyStr���ֶ�һ���򷵻سɹ������򷵻�ʧ�ܡ�
int findKeyStrInStrHead(const char* Src , const char* KeyStr)
{
	int i = 0 ;
	while( *(KeyStr+i) != NULL )
	{
		if(  (*(Src+i) ==  *(KeyStr+i)) /*|| (*(Src) == ' ' )*/ ) // pdfת�����ģ��п����ּ��пո�ȥ�����Ƿ���Ҫ�������ǡ�������
		{
		}
		else 
		{
			return ERR_FAILURE ; //ƥ��ʧ�ܡ�
		}
		i++;
	}
	return ERR_SUCCESS ; // ƥ��ɹ���

}
// ��Src�Ӵ��в���KeyStr�Ӵ����ҵ��򷵻سɹ���������KeyStr����λ�� �� ������Ҳ�������KeyPos����KeyStr��β�͡�
int findKeyStrInStr(const char* Src , const char* KeyStr  , int &KeyPos)
{
	const char * p_Source = Src ; 
	int Temp_pos = 0 ; 
	while( *(p_Source+Temp_pos) != NULL )
	{
		if( findKeyStrInStrHead( (p_Source+Temp_pos) , KeyStr) == ERR_SUCCESS )
		{	// �ҵ�һ��ƥ��ɹ��� �� ���ʡ�
			KeyPos = Temp_pos ; 
			return ERR_SUCCESS ; 
		}
		
		Temp_pos++;
	}
	KeyPos = Temp_pos;
	return ERR_FAILURE;
}

//ofstream g_Resultfile;
fstream g_Resultfile;

//��Src ���ҳ����е�KeyStr �� 
void GetAllKeyStrInStr(const char * Src , const char* KeyStr , int &TotalKeyNum )
{

		CHECK_PTR_VOID(Src );
		CHECK_PTR_VOID(KeyStr );
		const char* pSrc_temp = Src ;

		// �ҳ���һ�������еĹؼ���
		while(*(pSrc_temp) != NULL )
		{
			int Position = 0 ; 
			if( findKeyStrInStr(pSrc_temp , KeyStr , Position) == ERR_SUCCESS )
			{
				//cout <<  TotalKeyNum << ',' << KeyStr << ',' << pSrc_temp << endl ;
				g_Resultfile <<  TotalKeyNum+1 << ',' << KeyStr << ',' << pSrc_temp << endl ;
				TotalKeyNum++;
				pSrc_temp = (pSrc_temp + Position + sizeof(KeyStr) ); 
			}
			else
			{
				pSrc_temp = (pSrc_temp + Position);
			}
		}
}


// ��ȡָ��λ��һ�仰 �� �Ѿ�Ż����Ϊ�߽硣
int g_NumTotalKeys = 0 ; 
void testForFIO( void )
{
	// 1.��ȡkeywords 
	ifstream keyfile;
	keyfile.open (g_pKeyWord, ifstream::in);
	char keyWord[1024] = {0} ;
	if (keyfile.is_open())
    {
		keyfile.getline(keyWord,1000);
		keyWord[1000] = '\0';
		keyfile.close();
		cout << "get keyword success . \n keyword is "<< keyWord << endl ;
	}
	else
	{
		cout<< "#############���ڱ�Ŀ¼�·�����ȷ�ı������ֶ�############" << endl ; 
		cout<< "#############�ļ�����keyword.txt############" << endl ; 
		cout<< "#############�ļ���ֻдһ�С�############" << endl ; 
		return ; 
	}

	ifstream infile;
	infile.open ( g_pSourceFile , ifstream::in);
	g_Resultfile.open(g_pReslultFile, fstream::app) ;

	const int MAXCHAR_NUM = 10240 ; 
	char* pbuffer = new char[MAXCHAR_NUM];
	
	while (infile.good())
	{
		memset( pbuffer , 0 , MAXCHAR_NUM  ) ; 
        infile.getline(pbuffer,MAXCHAR_NUM-1);
		pbuffer[MAXCHAR_NUM - 1 ]= '\0';
		GetAllKeyStrInStr( pbuffer , keyWord , g_NumTotalKeys );
		//_sleep(5*10);
    }
	delete [] pbuffer ; 
	pbuffer = NULL ; 

	infile.close();
	g_Resultfile.close();
	cout<<"there are "<<g_NumTotalKeys<< " KeysWords." << endl;
}


