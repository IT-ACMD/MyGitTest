
#ifndef __CSTRA_H__
#define __CSTRA_H__
#pragma once
#include "stdafx.h"

class CStrA
{
public:
//	//��������
//	static double round(double x);
//    //double��ȡģ x % y
//    static double mod(double x, double y);
//public:
//    //������ѧ��ʽ
//    static int AnalyticMathFormula(const String& formulaStr, double *result);
//	//����ת��
//	static void ANSCToUnicode(string& out, const char* inSrc);
//	//ѹ���ַ���
//	static int Compress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
//	//�����ַ���
//	static void Contact(wchar_t *str, LPCTSTR str1, LPCTSTR str2 = L"", LPCTSTR str3 = L"");
//	//ת��Ϊǧ��λ
//	static String ConvertThousands(double value, int digit);
//	//���ݿ����תΪ�ļ���
//	static string ConvertDBCodeToFileName(const string& code);
//	//���ݿ����תΪ���˴���
//	static string ConvertDBCodeToSinaCode(const string& code);
//	//���ݿ����תΪ��Ѷ����
//	static string ConvertDBCodeToTencentCode(const string& code);
//	//���˴���תΪ���ݿ����
//	static String ConvertSinaCodeToDBCode(const String& code);
//	static double ConvertStrToDouble(const wchar_t *str);
//	static int ConvertStrToInt(const wchar_t *str);
//	//��Ѷ����תΪ���ݿ����
//	static String ConvertTencentCodeToDBCode(const String& code);
//	//��ѹ���ַ���
//	static int DeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
//	static bool IsBlank(int c);
//    static bool IsChinese(const String& str);
//    static int IsNum(const String& str);
//	static int IsNumeric(const string& str);
//    //���ص�һ�����ֵ��±�û���򷵻�-1 text���ҵ��ı� index��ʼ���ҵ�λ��(Ĭ��Ϊ0)
//    static int FindNum(const String& text, int index = 0);
//	//��ȡ���ݿ��ַ���
//	static String GetDBString(const String& strSrc);
//	//��ȡΨһ��ʶ
//	static string GetGuid();
//	//��ȡ��ʽ������
//	static void GetFormatDate(double date, wchar_t *str);
//	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
//	static String GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
//	//��ȡ�ַ����Ŀռ�
//	static int GetStringCapacity(const string& str);
//	//��ȡ���ַ����Ŀռ�
//	static int GetWStringCapacity(const String& str);
//	//��ȡ����ָ��С��λ�����ַ���
//	static void GetValueByDigit(double value, int digit, wchar_t *str);
//	//��ȡ����ָ��С��λ�����ַ���
//	static String GetValueByDigit2(double value, int digit);
//	// GZIPѹ������
//	static int GZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
//	// GZIP��ѹ������
//	static int GZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
//	//��ȡ������ֵ
//	static double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
//	//ͨ��������ֵ��ȡ������ʱ����
//	static void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
//	//�滻�ַ���
//	static string Replace(const string& str, const string& src, const string& dest);
//	//�滻���ַ���
//	static String Replace(const String& str, const String& src, const String& dest);
//	//����app
//	static void RestartApp();
//	static double RoundFloat(double price);
//	//�ָ��ַ���
//	static vector<string> Split(const string& str, const string& pattern);
//	//�ָ��ַ���
//	static vector<String> Split2(const String& str, const String& pattern);
//	//�ָ���ַ���
//	static vector<String> Split(const String& str, const String& pattern);
//	//ת��Ϊ���ַ���
	static void stringTowstring(wstring &strDest, const string& strSrc);
//	//ת��ΪСд
//	static String ToLower(const String& str);
//	//ת��Ϊ��д
//	static String ToUpper(const String& str);
//	//�ַ���ȥ�ո�
//	static void Trim(string &str);
//	//�ַ���ȥ�ո�
//	static void Trim(String &str);
//    //�ַ���ȥ��ͷ��ĩβ�ո�
//	static void Trim2(String &str);
//	//����ת��
//	static void UnicodeToANSC(string& out, const char* inSrc);
//	//�������Ƿ����
//	static bool ValueEqual(float lhs, float rhs);
//	//�������Ƿ����
//	static bool ValueEqual(double lhs, double rhs);
//	//�ַ�������ת�ַ���
//	static String VecToString(vector<String> *vec);
//	//ת��Ϊխ�ַ���
    static void wstringTostring(string &strDest, const wstring& strSrc);	
//	static string UTF8ToGBK(const string& strUTF8);
//    static string GBKToUTF8(const string& strUTF8);
};
#endif