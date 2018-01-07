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
			stringstream ss;
			size_t fileLen = m_fileName.length();
			ss << m_fileName.substr(0,fileLen-strlen(".txt"));
			ss << "_keycon_" << m_keyContentCount << ".txt" ; 
			m_keyContentFileList.push_back(ss.str());
			////当前匹配到的结果ID
			//// 在源文件中的页码
			m_pKeyContentfile = new fstream(ss.str().c_str() , ios_base::out);
			//写入文件首2行。
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
		endPos = m_currentline.find("。", endPos+2/*strlen("。")*/);
		string Sentence = ""; // 句子，已句号结尾。
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
	//读取源文件，并将源文件内的有效段提取出来
	GetKeyContent SourceFile(filename) ;
	
	SourceFile.Initialize();

	SourceFile.FileReadTest();


	list<string>::iterator it;

	//一个文件可能获取到多个content
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
//	"第一节 第二节 第三节 第四节 第五节 第六节",
//	"",
//	"第一",
//};
//for( int indexa = 0 ; indexa < 3 ; indexa ++)
//for(int index = 0 ; index < MAX_FIRSTTITLE_NUM ; index++)
//{
//	//cout << indexa << index << ": "<<testStr[indexa].compare(0 , strlen(FIRSTTITLE[index]) ,FIRSTTITLE[index]) << endl;
//	cout << indexa << index << ": "<<testStr[indexa].find(FIRSTTITLE[index]) << endl;
//}
//string strTT = "三、公司关于公司未来发展的讨论与分析";
//cout << strTT.find(KEYCONTENT);