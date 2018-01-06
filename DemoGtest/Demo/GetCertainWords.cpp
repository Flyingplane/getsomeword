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

// 从Src的头部开始查找KeyStr的字段，如果Src的头部字段与KeyStr的字段一致则返回成功，否则返回失败。
int findKeyStrInStrHead(const char* Src , const char* KeyStr)
{
	int i = 0 ;
	while( *(KeyStr+i) != NULL )
	{
		if(  (*(Src+i) ==  *(KeyStr+i)) /*|| (*(Src) == ' ' )*/ ) // pdf转出来的，有可能字间有空格。去掉。是否，需要后续考虑。。。。
		{
		}
		else 
		{
			return ERR_FAILURE ; //匹配失败。
		}
		i++;
	}
	return ERR_SUCCESS ; // 匹配成功。

}
// 在Src子串中插在KeyStr子串，找到则返回成功，并返回KeyStr所在位置 ， 如果查找不到，则KeyPos返回KeyStr的尾巴。
int findKeyStrInStr(const char* Src , const char* KeyStr  , int &KeyPos)
{
	const char * p_Source = Src ; 
	int Temp_pos = 0 ; 
	while( *(p_Source+Temp_pos) != NULL )
	{
		if( findKeyStrInStrHead( (p_Source+Temp_pos) , KeyStr) == ERR_SUCCESS )
		{	// 找到一个匹配成功的 ， 单词。
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

//从Src 中找出所有的KeyStr ， 
void GetAllKeyStrInStr(const char * Src , const char* KeyStr , int &TotalKeyNum )
{

		CHECK_PTR_VOID(Src );
		CHECK_PTR_VOID(KeyStr );
		const char* pSrc_temp = Src ;

		// 找出这一句中所有的关键词
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


// 获取指定位置一句话 ， 已句号或起点为边界。
extern bool ReadUTF8StringFile(CString Path, CString& str);
extern void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage)  ;


int g_NumTotalKeys = 0 ; 
void testForFIO( void )
{
	// 1.读取keywords 
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
		cout<< "#############请在本目录下放置正确的被搜索字段############" << endl ; 
		cout<< "#############文件名：keyword.txt############" << endl ; 
		cout<< "#############文件内只写一行。############" << endl ; 
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



///UTF-8 转 ANSI
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
		MessageBox(NULL,_T("无法打开文件:")+Path,_T("错误"),MB_ICONERROR|MB_OK);
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