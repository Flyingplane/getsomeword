#ifndef _SOURCEDATAFILE_H_
#define _SOURCEDATAFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

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
	list<string> m_keyContentFileList ;
	fstream* m_pKeyContentfile ;
public:
	GetKeyContent();
	GetKeyContent(string filename);
	~GetKeyContent();
	bool FindKeyStartPos( );
	bool FindkeyEndPos( );
	void UpdateKeyConentFlag(  );
	void outputContent(const string& Line);
	virtual bool updateInnerDatabyLine(const string& Line);
	void setKeyContentFlag( bool newFlag );
	bool getKeyContentFlag( );

};
void sourceTest( string filename , string KeyWordFile);

class exportWordSentence
{
public:
	string m_exportFileName ;
	string m_keyword;
	fstream m_fFile ; 
	unsigned int m_SentenceCount ;
	string m_currentline;
	list<string> sentenceList ;
public:
	exportWordSentence();
	exportWordSentence(string sourcefile,string keyword ) ;
	~exportWordSentence();
	void UpdataInerDatebynewline(const string& line);
	void printfInerData();
	void FindKeyword(const string& sentence);
};
class GetWords
{
public:
	string m_ContentFileName ;
	string m_keyWordFile ;
	map<string ,exportWordSentence*> m_keyWordmap ;
public:
	GetWords();
	GetWords(string contentfile , string keywordfile);
	~GetWords();
	bool Initialize();
	void Extractkeyword();
	void checkcontentfilebyline();
};
#endif