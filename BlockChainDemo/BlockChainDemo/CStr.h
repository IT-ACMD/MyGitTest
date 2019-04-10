
#ifndef __CSTRA_H__
#define __CSTRA_H__
#pragma once
#include "stdafx.h"

class CStrA
{
public:
//	//四舍五入
//	static double round(double x);
//    //double数取模 x % y
//    static double mod(double x, double y);
//public:
//    //解析数学公式
//    static int AnalyticMathFormula(const String& formulaStr, double *result);
//	//编码转换
//	static void ANSCToUnicode(string& out, const char* inSrc);
//	//压缩字符串
//	static int Compress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
//	//连接字符串
//	static void Contact(wchar_t *str, LPCTSTR str1, LPCTSTR str2 = L"", LPCTSTR str3 = L"");
//	//转化为千分位
//	static String ConvertThousands(double value, int digit);
//	//数据库代码转为文件名
//	static string ConvertDBCodeToFileName(const string& code);
//	//数据库代码转为新浪代码
//	static string ConvertDBCodeToSinaCode(const string& code);
//	//数据库代码转为腾讯代码
//	static string ConvertDBCodeToTencentCode(const string& code);
//	//新浪代码转为数据库代码
//	static String ConvertSinaCodeToDBCode(const String& code);
//	static double ConvertStrToDouble(const wchar_t *str);
//	static int ConvertStrToInt(const wchar_t *str);
//	//腾讯代码转为数据库代码
//	static String ConvertTencentCodeToDBCode(const String& code);
//	//解压缩字符串
//	static int DeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
//	static bool IsBlank(int c);
//    static bool IsChinese(const String& str);
//    static int IsNum(const String& str);
//	static int IsNumeric(const string& str);
//    //返回第一个数字的下标没有则返回-1 text查找的文本 index开始查找的位置(默认为0)
//    static int FindNum(const String& text, int index = 0);
//	//获取数据库字符串
//	static String GetDBString(const String& strSrc);
//	//获取唯一标识
//	static string GetGuid();
//	//获取格式化日期
//	static void GetFormatDate(double date, wchar_t *str);
//	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
//	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
//	//获取字符串的空间
//	static int GetStringCapacity(const string& str);
//	//获取宽字符串的空间
//	static int GetWStringCapacity(const String& str);
//	//获取保留指定小数位数的字符串
//	static void GetValueByDigit(double value, int digit, wchar_t *str);
//	//获取保留指定小数位数的字符串
//	static String GetValueByDigit2(double value, int digit);
//	// GZIP压缩数据
//	static int GZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
//	// GZIP解压缩数据
//	static int GZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
//	//获取日期数值
//	static double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
//	//通过日期数值获取年月日时分秒
//	static void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
//	//替换字符串
//	static string Replace(const string& str, const string& src, const string& dest);
//	//替换宽字符串
//	static String Replace(const String& str, const String& src, const String& dest);
//	//重启app
//	static void RestartApp();
//	static double RoundFloat(double price);
//	//分割字符串
//	static vector<string> Split(const string& str, const string& pattern);
//	//分割字符串
//	static vector<String> Split2(const String& str, const String& pattern);
//	//分割宽字符串
//	static vector<String> Split(const String& str, const String& pattern);
//	//转化为宽字符串
	static void stringTowstring(wstring &strDest, const string& strSrc);
//	//转换为小写
//	static String ToLower(const String& str);
//	//转换为大写
//	static String ToUpper(const String& str);
//	//字符串去空格
//	static void Trim(string &str);
//	//字符串去空格
//	static void Trim(String &str);
//    //字符串去开头和末尾空格
//	static void Trim2(String &str);
//	//编码转换
//	static void UnicodeToANSC(string& out, const char* inSrc);
//	//两个数是否相等
//	static bool ValueEqual(float lhs, float rhs);
//	//两个数是否相等
//	static bool ValueEqual(double lhs, double rhs);
//	//字符串集合转字符串
//	static String VecToString(vector<String> *vec);
//	//转化为窄字符串
    static void wstringTostring(string &strDest, const wstring& strSrc);	
//	static string UTF8ToGBK(const string& strUTF8);
//    static string GBKToUTF8(const string& strUTF8);
};
#endif