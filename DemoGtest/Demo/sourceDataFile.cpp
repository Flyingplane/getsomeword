#include "sourceDataFile.h"

#include <sstream>

unsigned int debug_mode = 0 ;
unsigned int g_debug_leave = 1 ;
fstream g_debugInfo("debuginfo.txt" , ios_base::out);
#define Debug_Info( lever , info ) \
	if( g_debug_leave == 1 ) \
{ \
	if(lever == 0 ) \
	{ \
		g_debugInfo << info << endl ; \
	} \
	else \
	{ \
		cout << info << endl ; \
	}\
}

const unsigned int MAX_FIRSTTITLE_NUM = 20;
const unsigned int MAX_FIRSTTITLE_LENTH = 10;
const char FIRSTTITLE[MAX_FIRSTTITLE_NUM][MAX_FIRSTTITLE_LENTH] =
{
	{"��һ��"  } , {"�ڶ���"  } , {"������"  } , {"���Ľ�"  } , {"�����"  } ,
	{"������"  } , {"���߽�"  } , {"�ڰ˽�"  } , {"�ھŽ�"  } , {"��ʮ��"  } ,
	{"��ʮһ��"} , {"��ʮ����"} , {"��ʮ����"} , {"��ʮ�Ľ�"} , {"��ʮ���"} ,
	{"��ʮ����"} , {"��ʮ�߽�"} , {"��ʮ�˽�"} , {"��ʮ�Ž�"} , {"�ڶ�ʮ��"}
};
const unsigned int MAX_SECONDTITLE_NUM = 20;
const unsigned int MAX_SECONDTITLE_LENTH = 10;
const char SECONDTITLE[MAX_FIRSTTITLE_NUM][MAX_SECONDTITLE_LENTH] =
{
	{"һ��"  } , {"����"  } , {"����"  } , {"�ġ�"  } , {"�塢"  } ,
	{"����"  } , {"�ߡ�"  } , {"�ˡ�"  } , {"�š�"  } , {"ʮ��"  } ,
	{"ʮһ��"} , {"ʮ����"} , {"ʮ����"} , {"ʮ�ġ�"} , {"ʮ�塢"} ,
	{"ʮ����"} , {"ʮ�ߡ�"} , {"ʮ�ˡ�"} , {"ʮ�š�"} , {"��ʮ��"}

};
sourcedatafile::sourcedatafile(string filename):m_fileName(filename)
{
	m_lineNum = 0 ;
	m_PageNum = 0 ;
	m_CureDealLine = "";
}

sourcedatafile::~sourcedatafile()
{

}

void sourcedatafile::Initialize()
{
	cout << "Initialize" << endl ;
}

//�ļ���ȡ��������
void sourcedatafile::FileReadTest()
{
	ifstream examplefile(m_fileName.c_str());
	cout << m_fileName.c_str();
	string tempLine = "";
	if (! examplefile.is_open())
	{
		cout << "Error opening file"<< m_fileName.c_str()<< endl; 
		return;
	}
	while (!examplefile.eof())
	{
		getline(examplefile , tempLine );
		updateInnerDatabyLine(tempLine);
		
	}
	examplefile.close();
	printInnerData();

}

// �����ڲ����ݣ���������ҳ����������
bool sourcedatafile::updateInnerDatabyLine(const string& OriginalLine)
{
	//��ȡ�������ǿ��У�������
	if (OriginalLine.size() == 0 )
	{
		return true;
	}
	//ÿ��һ�У�������һ
	m_lineNum++;
	m_CureDealLine = OriginalLine ;
	if(IsNewPage() == true )
	{	//������µ�һҳ���������¿�ʼ��
		m_lineNum = 0 ; 
	}
	IsFirstTitle(OriginalLine);
	IsSencondTitle(OriginalLine);
	return true ;
}
//��ʾ�ڲ�����
void sourcedatafile::printInnerData()
{
	cout << "current file :" << m_fileName << endl ;
	cout << "page : " << m_PageNum << endl ;
	cout << "line : " << m_lineNum << endl ;
}

//�ж��Ƿ����µ�һҳ
// ������µ�һҳ����ȥ�����׵���ҳ��Ƿ���
bool sourcedatafile::IsNewPage( )
{
	const char PAGEMARK = 0x0C ;

	if( m_CureDealLine.length() == 0 )
	{// ����ַ����ǿյģ��Ȳ�����
		return false ;
	}
	char firstchar = m_CureDealLine.at(0);
	if( firstchar == PAGEMARK )
	{
		m_CureDealLine.erase( 0 ,1 );
		m_PageNum++ ;
		return true ;
	}
	return false ;
}

//�ж��Ƿ�Ϊһ������
bool sourcedatafile::IsFirstTitle( const string& line )
{
	for(int index = 0 ; index < MAX_FIRSTTITLE_NUM ; index++)
	{
		if( m_CureDealLine.compare(0 , strlen(FIRSTTITLE[index]) ,FIRSTTITLE[index]) == 0 )
		{
			Debug_Info(debug_mode ,m_CureDealLine);
			return true ;
		}
	}
	return false ;
}
//�ж��Ƿ�Ϊ��������
bool sourcedatafile::IsSencondTitle(const string& Line)
{
	for(int index = 0 ; index < MAX_SECONDTITLE_NUM ; index++)
	{
		if( m_CureDealLine.compare(0 , strlen(SECONDTITLE[index]) ,SECONDTITLE[index]) == 0 )
		{
			Debug_Info(debug_mode ,m_CureDealLine);
			return true ;
		}
	}
	return false ;
}


GetKeyContent::GetKeyContent(string filename):sourcedatafile(filename)
{
	m_keyContentFlag = false ;
	m_keyContentCount = 0 ;
	m_pKeyContentfile = NULL ;
	m_keyContentFileList.clear();
};
GetKeyContent::~GetKeyContent()
{
	m_keyContentFileList.clear();
	setKeyContentFlag(false);
	m_keyContentCount = 0 ;
};
bool GetKeyContent::updateInnerDatabyLine(const string& OriginalLine)
{
	//��ȡ�������ǿ��У�������
	if (OriginalLine.size() == 0 )
	{
		return true;
	}
	//ÿ��һ�У�������һ
	m_lineNum++;
	m_CureDealLine = OriginalLine ;
	if(IsNewPage() == true )
	{	//������µ�һҳ���������¿�ʼ��
		m_lineNum = 0 ; 
	}
	UpdateKeyConentFlag();

	outputContent(OriginalLine);
	return true;
}
//��������������ȡ�������ݶ�
void GetKeyContent::UpdateKeyConentFlag()
{
	if( getKeyContentFlag() )
	{	// ���ҵ��˿�ʼ��ǣ����ҽ������
		if(FindkeyEndPos())
		{
			setKeyContentFlag(false);
		}
	}
	else
	{   // û���ҵ���ʼ��ǣ����ҿ�ʼ���
		if(FindKeyStartPos())
		{
			setKeyContentFlag(true);
		}
	}
}

//����ҵ������ݵ��ļ�
void GetKeyContent::outputContent(const string& Line)
{
	if(getKeyContentFlag())
	{
		Debug_Info(0,Line);
		(*m_pKeyContentfile) << Line << endl;
	}
}
// ���¿�ʼ��ǣ�
// ��������Ϊtrue���򴴽��ļ�
// ��������Ϊfalse ����ر��ļ����ͷ��ڴ�
void GetKeyContent::setKeyContentFlag( bool newFlag )
{
	if(newFlag != m_keyContentFlag)
	{
		m_keyContentFlag = newFlag;
		if(newFlag == true)
		{
			m_keyContentCount++;
			stringstream ss;
			size_t fileLen = m_fileName.length();
			ss << m_fileName.substr(0,fileLen-strlen(".txt"));
			ss << "_keycon_" << m_keyContentCount << ".txt" ; 
			m_keyContentFileList.push_back(ss.str());
			////��ǰƥ�䵽�Ľ��ID
			//// ��Դ�ļ��е�ҳ��
			m_pKeyContentfile = new fstream(ss.str().c_str() , ios_base::out);
			//д���ļ���2�С�
			(*m_pKeyContentfile) << "sourceFile: " << m_fileName <<endl;
			(*m_pKeyContentfile) << "page:" << m_PageNum << " line :" << m_lineNum  << endl;
		}
		else
		{
			if(m_pKeyContentfile != NULL)
			{
				m_pKeyContentfile->close();
				delete m_pKeyContentfile ;
				m_pKeyContentfile = NULL ;
			}
		}
	}
}
bool GetKeyContent::getKeyContentFlag()
{
	return m_keyContentFlag;
}

//Ѱ�ҿ�ʼ���
// ��ʼ��ǹ���
// 1.�Ƕ������⡣
// 2.�����ں� KEYCONTENT �ַ���
bool GetKeyContent::FindKeyStartPos( )
{
	if(IsFirstTitle( " " ) )
	{
		return false ;
	}
	if(IsSencondTitle( " " ) )
	{
		size_t Position = m_CureDealLine.find(KEYCONTENT);
		if(Position != string::npos )
		{
			return true ;
		}
	}
	return false ;
}
bool GetKeyContent::FindkeyEndPos()
{
	if (IsFirstTitle("") || IsSencondTitle(""))
	{
		return true ;
	}
	return false ;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
exportWordSentence::exportWordSentence()
{

}

exportWordSentence::exportWordSentence(string sourcefile ,string keyword ):m_keyword(keyword)
{
	m_SentenceCount = 0;
	size_t fileLen = sourcefile.length();
	m_exportFileName = sourcefile.substr(0,fileLen-strlen(".txt"));
	m_exportFileName += "_";
	m_exportFileName += m_keyword.c_str() ;
	m_exportFileName += ".csv";
	m_currentline = "";
	sentenceList.clear();
}
exportWordSentence::~exportWordSentence()
{
	sentenceList.clear();
}
void exportWordSentence::UpdataInerDatebynewline(const string& line)
{
	m_currentline = line ;
	size_t beginPos = 0 ;
	size_t endPos = 0;
	do 
	{		
		endPos = m_currentline.find("��", endPos+2/*strlen("��")*/);
		string Sentence = ""; // ���ӣ��Ѿ�Ž�β��
		if(endPos != string::npos )
		{
			 Sentence = m_currentline.substr(beginPos , endPos-beginPos );
		}
		else
		{
			Sentence = m_currentline.substr(beginPos);
		}
		beginPos = endPos ;
		FindKeyword(Sentence);
	} while (beginPos != string::npos );
}
void exportWordSentence::FindKeyword(const string& sentence)
{
	size_t found = sentence.find(m_keyword);
	if(found == string::npos)
	{
		return ;
	}
	do 
	{
		m_SentenceCount++;
		sentenceList.push_back(sentence);
		found = sentence.find(m_keyword , found+m_keyword.length()); 
	} while (found != string::npos);
}
void exportWordSentence::printfInerData()
{
	size_t fileLen = m_exportFileName.length();
	m_exportFileName = m_exportFileName.substr(0,fileLen-strlen(".txt"));
	stringstream ss ;
	ss << m_exportFileName << "_" << m_SentenceCount << ".csv";
	fstream outputfile(ss.str().c_str() , ios_base::out );
	list<string>::iterator it;

	outputfile << "begin" <<endl;
	for ( it=sentenceList.begin() ; it != sentenceList.end(); it++ )
	{
		outputfile << m_keyword << "," << (*it).c_str() << endl;
	}
	outputfile << "end" <<endl;
	outputfile.close();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
GetWords::GetWords()
{

}
GetWords::GetWords(string contentfile , string keywordfile):
			m_ContentFileName(contentfile),m_keyWordFile(keywordfile)
{
	m_keyWordmap.clear();
}
GetWords::~GetWords()
{
	map<string ,exportWordSentence*>::iterator it;
	// show content:
	for ( it=m_keyWordmap.begin() ; it != m_keyWordmap.end(); it++ )
	{
		exportWordSentence* pOutputTemp = (*it).second ;
		delete pOutputTemp ;
	}
	m_keyWordmap.clear();
}
bool GetWords::Initialize()
{
	return true ;
}

void GetWords::Extractkeyword()
{
	ifstream examplefile(m_keyWordFile.c_str());
	cout << m_keyWordFile.c_str() << endl;
	string tempLine = "";
	if (! examplefile.is_open())
	{
		cout << "Error opening file"<< m_keyWordFile.c_str()<< endl; 
		return;
	}
	while (!examplefile.eof())
	{
		getline(examplefile , tempLine );
		exportWordSentence* pOutputTemp = new exportWordSentence(m_ContentFileName ,tempLine );
		m_keyWordmap.insert(pair<string ,exportWordSentence*>(tempLine , pOutputTemp) );
	}
	examplefile.close();
}
void GetWords::checkcontentfilebyline()
{
	ifstream examplefile(m_ContentFileName.c_str());
	cout << m_ContentFileName.c_str() << endl;
	string tempLine = "";
	if (! examplefile.is_open())
	{
		cout << "Error opening file"<< m_ContentFileName.c_str()<< endl; 
		return;
	}
	while (!examplefile.eof())
	{
		getline(examplefile , tempLine );
		map<string ,exportWordSentence*>::iterator it;

		// show content:
		for ( it=m_keyWordmap.begin() ; it != m_keyWordmap.end(); it++ )
		{
			//cout << (*it).first << endl;
			exportWordSentence* pOutputTemp = (*it).second ;
			pOutputTemp->UpdataInerDatebynewline(tempLine);
		}
	}
	examplefile.close();

	map<string ,exportWordSentence*>::iterator it;
	// show content:
	for ( it=m_keyWordmap.begin() ; it != m_keyWordmap.end(); it++ )
	{
		//cout << (*it).first << endl;
		exportWordSentence* pOutputTemp = (*it).second ;
		pOutputTemp->printfInerData();
	}
}
void sourceTest( string filename , string KeyWordFile)
{
	//��ȡԴ�ļ�������Դ�ļ��ڵ���Ч����ȡ����
	GetKeyContent SourceFile(filename) ;
	
	SourceFile.Initialize();

	SourceFile.FileReadTest();


	list<string>::iterator it;

	//һ���ļ����ܻ�ȡ�����content
	for ( it=(SourceFile.m_keyContentFileList).begin() ; it != (SourceFile.m_keyContentFileList).end(); it++ )
	{
		cout << " " << *it<< endl;
		GetWords getwords( *it , KeyWordFile );
		getwords.Initialize();
		getwords.Extractkeyword();
		getwords.checkcontentfilebyline();
	}
	g_debugInfo.close();


}


//string testStr[] ={ 
//	"��һ�� �ڶ��� ������ ���Ľ� ����� ������",
//	"",
//	"��һ",
//};
//for( int indexa = 0 ; indexa < 3 ; indexa ++)
//for(int index = 0 ; index < MAX_FIRSTTITLE_NUM ; index++)
//{
//	//cout << indexa << index << ": "<<testStr[indexa].compare(0 , strlen(FIRSTTITLE[index]) ,FIRSTTITLE[index]) << endl;
//	cout << indexa << index << ": "<<testStr[indexa].find(FIRSTTITLE[index]) << endl;
//}
//string strTT = "������˾���ڹ�˾δ����չ�����������";
//cout << strTT.find(KEYCONTENT);