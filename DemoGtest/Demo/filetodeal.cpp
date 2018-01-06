#include "filetodeal.h"



KeyWordFile::KeyWordFile()
{
	m_numofkeyword = 0 ;
}

KeyWordFile::~KeyWordFile()
{

}
int KeyWordFile::Initialize( char* keywordFilename)
{

	ifstream keywordfile;
	keywordfile.open(keywordFilename, ifstream::in);
	if(!(keywordfile.is_open()))
	{
		cout<< "#############请在本目录下放置正确的被搜索字段############" << endl ; 
		cout<< "#############文件名：" << keywordFilename <<"############" << endl ; 
		cout<< "#############多个关键词请分行写入############" << endl ; 
		return ERR_FAILURE;
	}
	string keywordTemp ;
	char keyWord[1024] = {0} ;
	while(keywordfile.good())
	{
		keywordfile.getline(keyWord,1000);
		keyWord[1000] = '\0';
		keywordTemp = keyWord ;
		m_keywordlist.push_front( keywordTemp );
		m_numofkeyword++;
#ifdef g_debug
		cout << "get keyword success . \n keyword is "<< keywordTemp.c_str() << endl ;
#endif
	}
	keywordfile.close();

	return ERR_SUCCESS;
}

void KeyWordFile::showKeyWords()
{
	list<string>::iterator it;

	cout << " m_keywordlist contains:" << m_keywordlist.size() << " keyword(s)\n";
	int tempcount = 0 ;
	for ( it=m_keywordlist.begin() ; it != m_keywordlist.end(); it++ )
	{
		cout << ++tempcount << ": " << (*it).c_str() << endl;
	}
}




filetodeal::filetodeal()
{
	m_FileDataSize = 0 ;
	m_pFileDataBuff = NULL;
}
filetodeal::filetodeal(char* filename):m_FileName(filename) 
{
	m_FileDataSize = 0 ;
	m_pFileDataBuff = NULL;
}
filetodeal::~filetodeal()
{
	if(m_pFileDataBuff)
	{
		delete [] m_pFileDataBuff;
		m_pFileDataBuff = NULL;
	}
}
int filetodeal::Initialize( char* Filename)
{
	filebuf *pbuf;
	ifstream filestr;

	m_FileName = Filename ;
	filestr.open (Filename, ifstream::in);
	if(!(filestr.is_open()))
	{
		cout<< "#############请在本目录下放置正确的被查文件############" << endl ; 
		cout<< "#############文件名：" << Filename <<"############" << endl ; 
		return ERR_FAILURE;
	}

	// get pointer to associated m_pFileDataBuff object
	pbuf=filestr.rdbuf();

	// get file m_FileDataSize using m_pFileDataBuff's members
	m_FileDataSize=pbuf->pubseekoff (0,ios::end,ios::in);
	pbuf->pubseekpos (0,ios::in);

	// allocate memory to contain file data
	m_pFileDataBuff=new char[m_FileDataSize];

	// get file data  
	pbuf->sgetn (m_pFileDataBuff,m_FileDataSize);

	filestr.close();

#ifdef g_debug
	// write content to stdout
	int temp = (m_FileDataSize > 1000 ) ? 1000 : m_FileDataSize;
	cout.write (m_pFileDataBuff,1000);
	cout << " .....\n";
#endif

	return ERR_SUCCESS;	
}

void filetodeal::showKeyWords()
{
	cout << "file name is " << m_FileName.c_str() << endl ;
	cout << "file size is " << m_FileDataSize << "bits \n";
	if(m_FileDataSize)
	{
		cout << "file contains : \n" ;
		int temp = (m_FileDataSize > 1000 ) ? 1000 : m_FileDataSize;
		cout.write (m_pFileDataBuff,1000);
		cout << " .....\n";
	}
}