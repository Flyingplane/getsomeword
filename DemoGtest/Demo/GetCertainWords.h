#ifndef _GETCERTAINWORDS_H_
#define _GETCERTAINWORDS_H_
#include "common_data.h"

#define CHECK_PTR_WITHVALUE( ptr , ReValue )  	if( ptr == NULL ){ return ReValue ; }
#define CHECK_PTR_VOID( ptr )  	if( ptr == NULL )  { return ; }
void testForFIO( void );


int findKeyStrInStrHead(const char* Src , const char* KeyStr);
int findKeyStrInStr(const char* Src , const char* KeyStr  , int &KeyPos);
void GetAllKeyStrInStr(const char * Src , const char* KeyStr , int &TotalKeyNum );


#endif