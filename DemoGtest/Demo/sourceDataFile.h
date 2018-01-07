#ifndef _SOURCEDATAFILE_H_
#define _SOURCEDATAFILE_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class sourcedatafile 
{
public:
	//�ļ���·��
	string m_fileName ;
	// �ļ�����ҳ�����
	unsigned int m_PageNum ;
	// �ļ�������������
	unsigned int m_lineNum ;

	string m_CureDealLine ;


public:
	sourcedatafile(string filename);
	~sourcedatafile();
	void Initialize();
	void FileReadTest();
	bool IsNewPage( );
	//�ж��Ƿ�Ϊ��������
	bool IsSencondTitle( const string& Line);
	//�ж��Ƿ�Ϊһ������
	bool IsFirstTitle( const string& line );

	virtual bool updateInnerDatabyLine(const string& Line);
	void printInnerData();
};

const char KEYCONTENT[] = "��˾δ����չ";
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