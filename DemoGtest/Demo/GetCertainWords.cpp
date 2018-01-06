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
extern bool ReadUTF8StringFile(CString Path, CString& str);
extern void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)  ;


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
		char ConvertOut[100] ={0};
		Convert(keyWord , ConvertOut , 99 , 99 );
		cout << "ConvertOut" << ConvertOut << endl ; 
	}
	else
	{
		cout<< "#############���ڱ�Ŀ¼�·�����ȷ�ı������ֶ�############" << endl ; 
		cout<< "#############�ļ�����keyword.txt############" << endl ; 
		cout<< "#############�ļ���ֻдһ�С�############" << endl ; 
		return ; 
	}
	CString CskeyWord ;
	CString CskeyWordfile(g_pKeyWord) ;

	ReadUTF8StringFile(CskeyWordfile , CskeyWord);
	LPCTSTR p = CskeyWord;
	cout << p << "\n";

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



///UTF-8 ת ANSI
void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)  
  {  
      int len=strlen(strIn);  
      int unicodeLen=MultiByteToWideChar(sourceCodepage,0,strIn,-1,NULL,0);  
      wchar_t* pUnicode;  
      pUnicode=new wchar_t[unicodeLen+1];  
      memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
      MultiByteToWideChar(sourceCodepage,0,strIn,-1,(LPWSTR)pUnicode,unicodeLen);  
      BYTE * pTargetData = NULL;  
      int targetLen=WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,0,NULL,NULL);  
      pTargetData=new BYTE[targetLen+1];  
      memset(pTargetData,0,targetLen+1);  
      WideCharToMultiByte(targetCodepage,0,(LPWSTR)pUnicode,-1,(char *)pTargetData,targetLen,NULL,NULL);  
      strcpy(strOut,(char*)pTargetData);  
      delete pUnicode;  
      delete pTargetData;  
   } 

bool ReadUTF8StringFile(CString Path, CString& str)
{


	CFile fileR;
	if(!fileR.Open(Path,CFile::modeRead|CFile::typeBinary))
	{
		MessageBox(NULL,_T("�޷����ļ�:")+Path,_T("����"),MB_ICONERROR|MB_OK);
		return false;
	}
	BYTE head[3];
	fileR.Read(head,3);
	if(!(head[0]==0xEF && head[1]==0xBB && head[2]==0xBF))
	{
		fileR.SeekToBegin();
	}
	ULONGLONG FileSize=fileR.GetLength();
	char* pContent=(char*)calloc(FileSize+1,sizeof(char));
	fileR.Read(pContent,FileSize);
	fileR.Close();
	int n=MultiByteToWideChar(CP_UTF8,0,pContent,FileSize+1,NULL,0);
	wchar_t* pWideChar=(wchar_t*)calloc(n+1,sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8,0,pContent,FileSize+1,pWideChar,n);
	str=CString(pWideChar);
	free(pContent);
	free(pWideChar);
	return true;


}