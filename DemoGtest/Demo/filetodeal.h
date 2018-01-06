#ifndef _FILETODEAL_H_
#define _FILETODEAL_H_
#include <list>
#include <string.h>
#include "common_data.h"
#include <iostream>
#include <fstream>

using namespace std ; 

class KeyWordFile
{
public:
	list<string > m_keywordlist ;
	int m_numofkeyword ;

public:
	KeyWordFile();

	~KeyWordFile();

	int Initialize( char* keywordFile);
	void showKeyWords();
};

class filetodeal
{
private:
	string m_FileName ;
	char* m_pFileDataBuff;
	long m_FileDataSize ;
	list<string > m_keywordlist ;
public:
	filetodeal();
	filetodeal(char* filename);
	~filetodeal();
	int Initialize( char* Filename);
	void showKeyWords();
};

class calckeyword
{
public:
	KeyWordFile* m_pKeywords ; 
	filetodeal* m_pFiletodeal;
public:
	calckeyword();
	~calckeyword();
	
};

#endif