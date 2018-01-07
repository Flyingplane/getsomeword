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
	{"第一节"  } , {"第二节"  } , {"第三节"  } , {"第四节"  } , {"第五节"  } ,
	{"第六节"  } , {"第七节"  } , {"第八节"  } , {"第九节"  } , {"第十节"  } ,
	{"第十一节"} , {"第十二节"} , {"第十三节"} , {"第十四节"} , {"第十五节"} ,
	{"第十六节"} , {"第十七节"} , {"第十八节"} , {"第十九节"} , {"第二十节"}
};
const unsigned int MAX_SECONDTITLE_NUM = 20;
const unsigned int MAX_SECONDTITLE_LENTH = 10;
const char SECONDTITLE[MAX_FIRSTTITLE_NUM][MAX_SECONDTITLE_LENTH] =
{
	{"一、"  } , {"二、"  } , {"三、"  } , {"四、"  } , {"五、"  } ,
	{"六、"  } , {"七、"  } , {"八、"  } , {"九、"  } , {"十、"  } ,
	{"十一、"} , {"十二、"} , {"十三、"} , {"十四、"} , {"十五、"} ,
	{"十六、"} , {"十七、"} , {"十八、"} , {"十九、"} , {"二十、"}

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

//文件读取操作测试
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

// 更新内部数据，包括更新页数，行数。
bool sourcedatafile::updateInnerDatabyLine(const string& OriginalLine)
{
	//读取出来的是空行，不处理
	if (OriginalLine.size() == 0 )
	{
		return true;
	}
	//每读一行，函数加一
	m_lineNum++;
	m_CureDealLine = OriginalLine ;
	if(IsNewPage() == true )
	{	//如果是新的一页，行数重新开始。
		m_lineNum = 0 ; 
	}
	IsFirstTitle(OriginalLine);
	IsSencondTitle(OriginalLine);
	return true ;
}
//显示内部数据
void sourcedatafile::printInnerData()
{
	cout << "current file :" << m_fileName << endl ;
	cout << "page : " << m_PageNum << endl ;
	cout << "line : " << m_lineNum << endl ;
}

//判断是否有新的一页
// 如果是新的一页，则去掉行首的新页标记符。
bool sourcedatafile::IsNewPage( )
{
	const char PAGEMARK = 0x0C ;

	if( m_CureDealLine.length() == 0 )
	{// 如果字符串是空的，先不管他
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

//判断是否为一级标题
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
//判断是否为二级标题
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
	//读取出来的是空行，不处理
	if (OriginalLine.size() == 0 )
	{
		return true;
	}
	//每读一行，函数加一
	m_lineNum++;
	m_CureDealLine = OriginalLine ;
	if(IsNewPage() == true )
	{	//如果是新的一页，行数重新开始。
		m_lineNum = 0 ; 
	}
	UpdateKeyConentFlag();

	outputContent(OriginalLine);
	return true;
}
//查找所需内容提取所需内容段
void GetKeyContent::UpdateKeyConentFlag()
{
	if( getKeyContentFlag() )
	{	// 已找到了开始标记，查找结束标记
		if(FindkeyEndPos())
		{
			setKeyContentFlag(false);
		}
	}
	else
	{   // 没有找到开始标记，查找开始标记
		if(FindKeyStartPos())
		{
			setKeyContentFlag(true);
		}
	}
}

//输出找到的内容到文件
void GetKeyContent::outputContent(const string& Line)
{
	if(getKeyContentFlag())
	{
		Debug_Info(0,Line);
		(*m_pKeyContentfile) << Line << endl;
	}
}
// 更新开始标记，
// 如果标记置为true，则创建文件
// 如果标记置为false ，则关闭文件并释放内存
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

//寻找开始标记
// 开始标记规则：
// 1.是二级标题。
// 2.标题内含 KEYCONTENT 字符串
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
		"第一节 第二节 第三节 第四节 第五节 第六节",
		"",
		"第一",
	};
	for( int indexa = 0 ; indexa < 3 ; indexa ++)
	for(int index = 0 ; index < MAX_FIRSTTITLE_NUM ; index++)
	{
		//cout << indexa << index << ": "<<testStr[indexa].compare(0 , strlen(FIRSTTITLE[index]) ,FIRSTTITLE[index]) << endl;
		cout << indexa << index << ": "<<testStr[indexa].find(FIRSTTITLE[index]) << endl;
	}
	string strTT = "三、公司关于公司未来发展的讨论与分析";
	cout << strTT.find(KEYCONTENT);
}