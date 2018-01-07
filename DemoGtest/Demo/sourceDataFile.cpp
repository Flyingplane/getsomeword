#include "sourceDataFile.h"

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
	string tempLine ;
	if (! examplefile.is_open())
	{
		cout << "Error opening file"; 
		return;
	}
	while (!examplefile.eof())
	{
		//examplefile.getline(tempLine,100);
		getline(examplefile , tempLine );
		//cout << tempLine << endl;
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
			string keyFilename = "KeyConten_";
			keyFilename += (char)((char)m_keyContentCount + '0');
			keyFilename += ".txt";
			m_pKeyContentfile = new fstream(keyFilename.c_str() , ios_base::out);
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
void sourceTest( string filename)
{
	GetKeyContent SourceFile(filename) ;
	
	SourceFile.Initialize();

	SourceFile.FileReadTest();

	g_debugInfo.close();

	string testStr[] ={ 
		"��һ�� �ڶ��� ������ ���Ľ� ����� ������",
		"",
		"��һ",
	};
	for( int indexa = 0 ; indexa < 3 ; indexa ++)
	for(int index = 0 ; index < MAX_FIRSTTITLE_NUM ; index++)
	{
		//cout << indexa << index << ": "<<testStr[indexa].compare(0 , strlen(FIRSTTITLE[index]) ,FIRSTTITLE[index]) << endl;
		cout << indexa << index << ": "<<testStr[indexa].find(FIRSTTITLE[index]) << endl;
	}
	string strTT = "������˾���ڹ�˾δ����չ�����������";
	cout << strTT.find(KEYCONTENT);
}