/***************************************************
Copyright (c) 2009, IvanJ.
All rights reserved.

File:    CommonDef.h
Purpose: 
Version: 0.1

****************************************************/


#ifndef _COMMONDEF_H_INCLUDED_
#define _COMMONDEF_H_INCLUDED_

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <math.h>

#pragma warning(disable : 4996)
using namespace std;

typedef unsigned long   ULONG;
typedef unsigned char   BYTE;
typedef unsigned short  USHORT;
typedef __int64         LLONG;
typedef long            LONG;
typedef double          DOUBLE;

typedef string          STRING;
typedef vector<STRING>  VEC_STR;
typedef vector<ULONG>   VEC_ULONG;
typedef vector<USHORT>  VEC_USHORT;
typedef vector<BYTE>    VEC_BYTE;
typedef vector<LLONG>   IDVector;
typedef vector<ULONG>   IndexVector;

#define FLOAT_EQUAL( x1, x2 )       ( ( x1 > x2 || x1 < x2  ) ? false : true )
#define FLOAT_NOTEQUAL( x1, x2 )    ( ( x1 > x2 || x1 < x2  ) ? true : false )

#define FLOAT_TO_LLONG( dx )        ( LLONG( (dx) + 0.5 ) )
#define FLOAT_TO_LONG( dx )         ( long( (dx) + 0.5 ) )
#define FLOAT_TOULONG( dx )         ( ULONG( (dx) + 0.5 ) )
#define GET_MESHYLINE_COOR( d )     (double)( FLOAT_TO_LLONG( (d) * 10.0 ) / 10 )
#define TOLL_TYPE					33792		//��άPOI���շ�վ������
#define TOLL_NODE					4609		//�շѽڵ������ֵ
#define MAX_COUNT					5000		//һ�β�����������
#define MAX_BUFSIZE					1024

//��������
enum DataType
{
	DATA_SW150,
	DATA_SW152,
	DATA_SW,
	DATA_YTT,
	DATA_RT
};

//����������
enum AdminType
{
	COUNTRY_ADMIN,				//��������������
	PROV_ADMIN,					//ʡ������������
	CITY_ADMIN,					//�ؼ��С�ʡֱϽ������λ������������	
	COUNTY_ADMIN,				//�ء���������������	
	CLIP_ADMIN
};

//ͼ���߽������
enum BoundType
{
	SIMPLE,						//��ͨ��
	MESHBOUNDNODE,				//Դ����ͼ���߽��
	DISTRICTBOUNDNODE,			//���������ָ��
	CROSSLINKCUT,				//����·�ڹ�����link�ָ��,�����ڸ���·�ڵ�link���зֵ�
	PROVINCEBOUNDNODE			//ʡͼ���߽��,����ȫ�����ݺϲ�
};

//��־����
enum LogType
{
	LT_ERROR        = 0,		//������Ϣ
	LT_MSG          = 1,		//��ϸ��Ϣ��Ϣ
	LT_TIMECOUNT    = 2,		//ʱ��ͳ����Ϣ
	LT_TOTAL		= 3			//ʱ��ͳ����Ϣ
};

//�ڵ�·������
enum CrossType
{
	NOT_CROSS_NODE,				//��·�ڽڵ�
	SUB_NODE,					//����·���ӽڵ�
	SINGLE_CROSS,				//��һ·�ڽڵ�
	MAIN_NODE					//����·�����ڵ�
};

//RECT��RECT��λ�ù�ϵ���
enum RectToRectRelation			
{
	RRF_INSRC,					//Ŀ��RECT�ڵ�ǰRECT�ڲ�
	RRF_INDEST,					//��ǰRECT��Ŀ��RECT�ڲ�
	RRF_INTERSECT,				//�ཻ
	RRF_EQUAL,					//���
	RRF_DISCRETE				//����	
};

//����SW1.5���ݰ�����Ԫ�������Ʒֿ����,�����Ǹ�Ԫ�������Ʊ������
enum NameType
{
	IC_NAME = 3,				//IC����
	DR_NAME = 4,				//DR����
	BL_NAME = 5,				//����������
	BP_NAME = 6,				//����������
	T_NAME  = 8,				//����������
	POI_NAME = 9,				//POI����
	POI_ADDRESS = 10,			//POI��ַ	
	ADMIN_NAME	= 14			//������������
};

//Ϊ��֤ID��Ψһ�ԣ��ڸ������͵�IDǰ������ض���ǰ׺
enum IDType
{
	ID_LINK,		//link id
	ID_NODE,		//node id
	ID_RULE,		//���� id
	ID_COND,		//��������id
	ID_IC,			//ic id
	ID_DR,			//dr id
	ID_LANE,		//���� id
	ID_POI,			//poi id
	ID_CAMERA,		//������ id
	ID_BACK,		//���� id
	ID_DM,			//DM ID
	ID_BR,			//BR ID
	ID_NONE
};

//ת���������ͣ����С�ʡ��ȫ��
enum ConvertAreaType
{
	CITY,
	PROV,
	COUNTRY
};

//����ͼƬ����
enum ImageType
{
	HIGHWAY_CROSS = 1,		//1�����ٷ���ģʽͼ
	HIGHWAY_ENTRANCE,		//2�����ٳ��ڷŴ�ͼ
	HIGHWAY_EXIT,			//3��������ڷŴ�ͼ
	PATTERN_3D				//4��3dģʽͼ
};

static string IDArray[ID_NONE] = {"110", "120", "130", "140", "150", "160", "170", "180", "190", "200"};

//���ݿ����Ӷ���ṹ��
struct DBInfo
{
	string strServerIP;			//������
	string strPort;				//���ݿ���ʶ˿ں�
	string strDBName;			//���ݿ�����
	string strUserName;			//�û���
	string strPassword;			//����
};

//�����ļ����󣬰��������ļ������е���Ϣ
struct ConfigFile
{
	vector<string> CreateTableSql;				//����������
	DBInfo ServerInfo;							//ȫ���������Ϣ
	DBInfo LocalInfo;							//��ʡ�������Ϣ
	string strTableSpaceName;					//��ռ�����
	string strConvertIP;						//ת����

	multimap<string, string>	mpConvertArea;			//ת������Ӧת��������Ϣ
	map<ULONG, ULONG>			mpDistrictCombine;		//���������Զ���ָ��
	map<ULONG, ULONG>			mpClipByMesh;			//ͼ���и��������(Ŀǰֻ�ж�ݸ)
	map<ULONG, string>			mpAdminCodeToName;		//�����������������������ƵĶ�Ӧ

	string strFolderPath;						//Դ�������ڵ�ַ
	map<ConvertAreaType, string> mpFoldName;	//���治ͬ���ļ������ƣ�level0��level1��level2
	map<ConvertAreaType, VEC_STR> mpBkgLineType;//���治ͬ�㱳���ߵ���ʾ�ֱ�
	map<ConvertAreaType, VEC_STR> mpBkgAreaType;//���治ͬ�㱳�������ʾ�ֱ�
	vector<ULONG>	vProvZhixiaCity;			//ʡֱϽ������λ
};

//ΪԴ������������id
static LLONG MakeID(const STRING& strID, IDType idType)
{
	if (strID == "0" || strID == "")
	{
		return 0;
	}
	string strNewID = IDArray[idType] + strID;
	return _atoi64(strNewID.c_str());
}

static double MyAtof(char* SrcStr)
{
	char buf[256];
	char* pSrc = SrcStr;
	char* pDest = buf;
	int iDec = 0;
	bool bDecBegin = false;
	while( *pSrc != '\0' )
	{
		if( *pSrc >= '0' && *pSrc <= '9' )
		{
			*pDest = *pSrc;
			pDest++;
			if( bDecBegin )
			{
				iDec++;
			}
		}
		else if( *pSrc == '.' )
		{
			bDecBegin = true;
		}
		pSrc++;
	}
	*pDest = '\0';
	__int64 ret = _atoi64( buf );
	double dRet = ret / pow( 10.0, iDec );
	return dRet;
}

//��Դ�����ṩ��id���ָ�Ϊid����
static void SetIDVector(IDVector& IDVec, const STRING& strSrcField, char chSplite, const IDType& type)
{
	if (strSrcField == "")
	{
		return;
	}
	string strTemp = strSrcField;
	size_t ipos = strTemp.find(chSplite);
	LLONG llID = 0;
	while(ipos != string::npos)
	{
		llID = MakeID(strTemp.substr(0, ipos), type);
		IDVec.push_back(llID);
		strTemp = strTemp.substr(++ipos);
		ipos = strTemp.find(chSplite);
	}
	if (strTemp != "0")
	{
		llID = MakeID(strTemp.substr(0, ipos), type);
		IDVec.push_back(llID);
	}
}

static void MyTolower(char* str)
{
	size_t i = strlen(str);
	int pos = 'A' - 'a';
	for (size_t j = 0; j < i; j++)
	{
		if (str[j] >= 'A' && str[j] <= 'Z')
		{
			str[j] -= pos;
		}
	}
}

//��Դ����mid�ļ���һ�а���","���зָ�
static void GetField(const string& strSource, VEC_STR& vField )
{
	size_t sSubstrStart = 0;
	size_t sSubstrEnd = 0;
	size_t sOldStart = 0;

	while (1)
	{
		sSubstrEnd = strSource.find( ',', sSubstrStart );
		if ( sSubstrEnd != string::npos )
		{
			string field = strSource.substr( sOldStart, sSubstrEnd - sOldStart );
			size_t find = field.find( '\"');
			if( find != string::npos && find == field.rfind( '\"' ) )
			{
				sSubstrStart = sSubstrEnd + 1;
			}
			else
			{
				sOldStart = sSubstrEnd + 1;
				sSubstrStart = sOldStart;

				size_t nPos = 0;
				while ( ( nPos = field.find('\"', nPos ) ) != string::npos )
				{
					field.erase(nPos, 1);
				}
				vField.push_back( field );
			}
		}
		else
		{
			break;
		}
	}
	size_t nPos = 0;
	string lastField = strSource.substr( sSubstrStart );
	while ( ( nPos = lastField.find( '\"', nPos ) ) != string::npos )
	{
		lastField.erase( nPos, 1 );
	}
	vField.push_back( lastField );
}

static void GetField(char* buf, char* AttrBuf, vector<char*>& strVec)
{
	char* pSrc = buf;
	char* pOne = AttrBuf;
	char* pos = pOne;
	while (*pSrc)
	{
		if (*pSrc == '\"')				//����+���ŷָ�
		{
			++pSrc;
			while (*pSrc != '\"' ||
				(*(pSrc + 1) && *(pSrc + 1) != 0x0a && *(pSrc + 1) != ','))
			{
				if (*pSrc == '\"' && *(pSrc + 1) == '\"')
				{
					pSrc++;
				}
				else
				{
					*pos++ = *pSrc++;
				}
			}
			++pSrc;
		}
		else							//���ŷָ�
		{
			while (*pSrc != ',' && *pSrc)
			{
				*pos++ = *pSrc++;
			}
		}
		*pos = '\0';
		pos = pOne;
		strVec.push_back(pos);
		pOne += strlen(pos) + 1;
		pos = pOne;

		if (!*pSrc)
		{
			break;
		}
		++pSrc;
	}
}

//ȥ���ַ�����������Ŀո�
static void TrimLeftAndRight(string& strSrc)
{
	size_t i = 0, j = 0;
	for (; i < strSrc.size(); i++)
	{
		if (strSrc[i] != ' ')
		{
			break;
		}
	}
	for (j = strSrc.size() - 1; j > 0; j--)
	{
		if (strSrc[j] != ' ')
		{
			break;
		}
	}
	strSrc = strSrc.substr(i, j - i + 1);
}

//���ݵ�������ȡ������map
static int GetMapIDByPoint(double dx, double dy)
{
	if ( dx < 0.000006 || dy < 0.000006 )
	{
		return 0;
	}
	//��595673feǰ����λ
	double dxTail, dyTail;
	int ndx, ndy;
	int nX, nY;  
	int nX2, nY2;	//����λ�͵���λ
	dy = dy * 3.0 / 2;

	ndx	= (int)dx;
	ndy	= (int)dy;
	nX	= ndx - 60;	
	nY	= ndy;

	dxTail = dx - ndx;
	dyTail = dy - ndy;
	nX2 = (int)(dxTail / 0.125);
	nY2 = (int)(dyTail / 0.125);

	char buf[256];
	sprintf_s(buf, "%02d%02d%d%d", nY, nX, nY2, nX2);
	return atoi(buf);
}

//��ʽ��ʱ������е�ʱ����Ϣ
static void FormatHour(const string& strInHour, string& strOutHour)
{
	string strTemp = strInHour;
	transform(strTemp.begin(), strTemp.end(), strTemp.begin(), ::tolower);
	size_t iHpos = strTemp.find("h");
	strTemp = strTemp.substr(++iHpos);
	size_t iMpos = strTemp.find("m");
	if (iMpos == string::npos)
	{
		strTemp += ":00";
	}
	else
	{
		strTemp[iMpos] = ':';
	}
	strOutHour += strTemp;
}

static string DBCToSBC(const string& strSrc)
{
	wchar_t wcs[1024];
	int ret = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(), (int)strSrc.size(), wcs, 1024 );
	wcs[ret] = 0;
	for (int i = 0; i < ret; i++)
	{
		if (wcs[i] == 32)
		{
			wcs[i] = 12288;
			continue;
		}
		if (wcs[i] < 127)
			wcs[i] = (wchar_t)(wcs[i] + 65248);
	}
	char buf[2048];
	ret = WideCharToMultiByte( CP_ACP, 0,wcs, ret, buf, sizeof(buf), NULL, NULL );
	buf[ret] = '\0';
	return buf;
}

//���������ַ��ָ��ַ���
static void SeparateString(const char* pSrc, vector<char*>* pStrs)
{
	if( pSrc == NULL )
		return;
	size_t nLen = strlen( pSrc );
	if( nLen == 0 )
		return;

	size_t sum = strlen(pSrc);
	for(size_t i = 1, j = 1; i < sum; i++)
	{
		if((*(pSrc+i) == ';') || (*(pSrc+i) == ','))
		{
			char* str = new char[i-j+1];
			strncpy(str,pSrc+j,i-j);
			*(str+i-j) = '\0';

			pStrs->push_back(str);
			j = i+1;
		}
		else if(*(pSrc+i) == '}')
		{
			char* str = new char[i-j+1];
			strncpy(str,pSrc+j,i-j);
			*(str+i-j) = '\0';

			pStrs->push_back(str);
			break;
		}
		else if(*(pSrc+i) == '\0')
		{
			char* str = new char[i-j+1];
			strncpy(str,pSrc+j,i-j);
			*(str+i-j) = '\0';

			pStrs->push_back(str);
			j = i+1;
		}
	}
}

//��utf8������ַ���תΪasc������ַ���
static bool UTF8ToASC(const wchar_t* pUnicode,string& asc)
{
	unsigned __int32 i64Num = WideCharToMultiByte(CP_ACP,NULL,pUnicode,-1,NULL,0,NULL,FALSE);
	char *psText;
	psText = new char[i64Num];
	if(!psText)
	{   
		delete []psText;
		return false;
	}
	WideCharToMultiByte (CP_ACP,NULL,pUnicode,-1,psText,i64Num,NULL,FALSE);
	asc = psText;
	delete[] psText;
	return true;
}

//��utf8������ַ���תΪasc������ַ���
static bool UTF8ToASC(const char* pUnicode,string& asc)
{
	unsigned __int32 i64Num = MultiByteToWideChar(CP_UTF8,NULL,pUnicode,-1,NULL,0);
	wchar_t* psText;
	psText = new wchar_t[i64Num];
	if(!psText)
	{   
		delete []psText;
		return false;
	}
	MultiByteToWideChar(CP_UTF8,NULL,pUnicode,-1,psText,i64Num);
	UTF8ToASC(psText,asc);
	delete[] psText;
	return true;
}

//��Unicode������ַ���תΪutf8������ַ���
static bool UnicodeToUTF8(const wchar_t* pUnicode,string& utf8 )
{
	unsigned __int32 i64Num = WideCharToMultiByte(CP_UTF8, NULL, pUnicode, -1, NULL, 0, NULL, FALSE);
	char *psText;
	psText = new char[i64Num];
	if(!psText)
	{   
		delete []psText;
		return false;
	}
	WideCharToMultiByte (CP_UTF8, NULL, pUnicode, -1, psText, i64Num, NULL, FALSE);
	utf8 = psText;
	delete[] psText;
	return true;
}

//��Unicode������ַ���תΪutf8������ַ���
static bool UnicodeToUTF8(const char* pUnicode,string& utf8 )
{
	unsigned __int32 i64Num = MultiByteToWideChar(CP_NONE, NULL, pUnicode, -1, NULL, 0);
	wchar_t* psText;
	psText = new wchar_t[i64Num];
	if(!psText)
	{   
		delete []psText;
		return false;
	}
	MultiByteToWideChar(CP_NONE, NULL, pUnicode, -1, psText, i64Num);
	UnicodeToUTF8(psText, utf8 );
	delete[] psText;
	return true;
}

//��asc������ַ���תΪutf8������ַ���
static bool ASC2UTF8(char *cASCII, char *cUTF8, int char_len)   
{   
	wchar_t wbuf[1024];   
	char utf8buf[1024];   

	ZeroMemory(wbuf,sizeof(wbuf));   
	int nret= MultiByteToWideChar(CP_ACP,0,cASCII,char_len,wbuf,sizeof(wbuf)/sizeof(wbuf[0]));   
	if(nret > 0 && nret < sizeof(wbuf))   
	{ 
		nret = WideCharToMultiByte(CP_UTF8,0,wbuf,nret,utf8buf,sizeof(utf8buf),NULL,NULL);   
		if(nret <= 0 && nret >= sizeof(utf8buf))   
			return false;   
	}
	else
		return false;   
	utf8buf[nret] = '\0';   
	strcpy(cUTF8, utf8buf);   
	return true;
}

static bool IsZhiXia(ULONG ulAdminCode)
{
	USHORT usPos = USHORT(ulAdminCode / 10000);
	if (usPos == 11 || usPos == 12 || usPos == 31 || usPos == 50)
	{
		return true;
	}
	return false;
}

static string GetCurrentData()
{
	time_t t = time(NULL);
	char szCurrentDate[64];
	strftime( szCurrentDate, sizeof( szCurrentDate ), "%Y%m%d", localtime(&t) ); 
	string strCurrentDate = szCurrentDate;
	return strCurrentDate;
}

static void CutString(const string& strSrc, char chBuf, VEC_STR& OutVec)
{
	string strTemp = strSrc;
	size_t ipos = strTemp.find_first_of(chBuf);
	while (ipos != string::npos)
	{
		OutVec.push_back(strTemp.substr(0, ipos));
		strTemp = strTemp.substr(++ipos);
		ipos = strTemp.find_first_of(chBuf);
	}
	OutVec.push_back(strTemp);
}

//ָ�����������ͷ�
template <class T> 
void ReleaseVect( vector<T*>& vItems )
{
	size_t iSize = vItems.size();
	for (size_t i = 0; i < iSize; i++)
	{	
		if (vItems.at(i) != NULL)
		{
			delete vItems[i];
		}
	}
	vItems.clear();
}

//ָ��map�����ͷ�
template< class Key, class Data >
void ReleaseMap( map<Key, Data>& mItems )
{
	for ( map<Key, Data>::iterator it = mItems.begin(); it != mItems.end(); ++it )
	{
		if (it->second != NULL)
		{ 
			delete it->second;
			it->second = NULL;
		}
	}
	mItems.clear();
}

//ָ��multimap�����ͷ�
template< class Key, class Data >
void ReleaseMultimap( multimap<Key, Data>& mItems )
{
	for ( multimap<Key, Data>::iterator it = mItems.begin(); it != mItems.end(); ++it )
	{
		if (it->second != NULL)
		{ 
			delete it->second;
			it->second = NULL;
		}
	}
	mItems.clear();
}

template<class key, class data>
void InsertVecMap(key keyval, data* pData, map<key, vector<data*>>& mpValue)
{
	map<key, vector<data*>>::iterator itF = mpValue.find(keyval);
	if(itF == mpValue.end())
	{
		vector<data*> TempVec;
		TempVec.push_back(pData);
		mpValue.insert(make_pair(keyval, TempVec));
	}
	else
	{
		itF->second.push_back(pData);
	}
}
#endif