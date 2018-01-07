#ifndef _SOURCEDATAFILE_H_
#define _SOURCEDATAFILE_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class sourcedatafile 
{
public:
	//文件的路径
	string m_fileName ;
	// 文件读入页码计数
	unsigned int m_PageNum ;
	// 文件读入行数计数
	unsigned int m_lineNum ;

	string m_CureDealLine ;


public:
	sourcedatafile(string filename);
	~sourcedatafile();
	void Initialize();
	void FileReadTest();
	bool IsNewPage( );
	//判断是否为二级标题
	bool IsSencondTitle( const string& Line);
	//判断是否为一级标题
	bool IsFirstTitle( const string& line );

	virtual bool updateInnerDatabyLine(const string& Line);
	void printInnerData();
};

const char KEYCONTENT[] = "公司未来发展";
class GetKeyContent :public sourcedatafile
{
public:
	bool m_keyContentFlag ;
	int m_keyContentCount ;
	fstream* m_pKeyContentfile ;
public:
	GetKeyContent();
	GetKeyContent(string filename):sourcedatafile(filename)
	{
		m_keyContentFlag = false ;
		m_keyContentCount = 0 ;
		m_pKeyContentfile = NULL ;
	};
	~GetKeyContent()
	{

	};
	bool FindKeyStartPos( );
	bool FindkeyEndPos( );
	void UpdateKeyConentFlag(  );
	void outputContent(const string& Line);
	virtual bool updateInnerDatabyLine(const string& Line);
	void setKeyContentFlag( bool newFlag );
	bool getKeyContentFlag( );

};
void sourceTest( string filename);

#endif