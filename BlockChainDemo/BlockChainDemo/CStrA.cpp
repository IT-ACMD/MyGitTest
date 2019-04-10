#include "stdafx.h"
#include "CStr.h"
#include <queue>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//double queueCalculate(queue<double> *qnum, queue<wchar_t> *qsymbol)
//{
//    double sum = 0.0;
//    while(!qnum->empty())
//    {
//        sum = (double)qnum->front(); 
//        qnum->pop();
//NextCalculate:
//        if(qsymbol->empty())break;
//        wchar_t wc = qsymbol->front();
//        qsymbol->pop();
//        switch(wc)
//        {
//            case L'+': 
//                {
//                    sum += queueCalculate(qnum, qsymbol);
//                    break;
//                }
//            case L'-':
//                {
//                    sum -= queueCalculate(qnum, qsymbol);
//                    break;
//                }
//            case L'*':
//                {
//                    sum *= qnum->front();
//                    qnum->pop();
//                    goto NextCalculate;
//                }
//            case L'/':
//                {
//                    sum /= qnum->front();
//                    qnum->pop();
//                    goto NextCalculate;
//                }
//            /*case L'%':
//                {
//                    sum = (int)sum % (int)dnum;
//                    break;
//                }*/
//        }
//    }
//    return sum;
//}
//
//int CStrA::AnalyticMathFormula(const String& formulaStr, double *result)
//{
//    int state = -1;
//    String text = formulaStr;
//    vector<int> indexs;
//    int size = (int)text.size();
//    for(int i = 0; i < size; i++)
//    {
//        wchar_t lastwc = text[i];
//        if(text[i] == L'(')
//        {
//            int res = text.find(L")");
//            if(res != -1)
//            {
//                double r = 0.0;
//                String a = text.substr(i + 1, res - i);
//                state = AnalyticMathFormula(a, &r);
//                if(state == -1)
//                {
//                    text = CStrA::Replace(text, a, CStr::ConvertDoubleToStr(r));
//                    size = (int)text.size();
//                }
//                else
//                {
//                    return state + i;
//                }
//            }
//            else
//            {
//               return i; 
//            }
//        }
//        if(text[i] == L'+' || text[i] == L'-' || text[i] == L'*' || text[i] == L'/' || text[i] == L'%')
//        {
//            if(i + 1 >= size)
//            {
//                return i;
//            }
//            int reSize = (int)indexs.size();
//            if((reSize > 0 && i - 1 == indexs[reSize - 1]) || i == 0)
//            {
//                return i;
//            }
//            indexs.push_back(i);
//        }
//    }
//    
//    int startIndex = 0, qstart = -1, nsize = (int)indexs.size();
//    double sum = 0;
//    queue<double> qnum;//数字队列
//    queue<wchar_t> qsymbol;//字符队列
//    for(int i = 0; i < nsize; ++i)
//    {
//        String num = text.substr(startIndex, indexs[i] - startIndex);
//        CStrA::Trim2(num);
//        if(!CStrA::IsNum(num))return startIndex + 1;
//        double dnum = CStrA::ConvertStrToDouble(num.c_str());
//        qnum.push(dnum);
//        qsymbol.push(text[indexs[i]]);
//        startIndex = indexs[i] + 1;
//    }
//    if(startIndex < size)
//    {
//        String num = text.substr(startIndex, size);
//        CStrA::Trim2(num);
//        if(!CStrA::IsNum(num))return startIndex;
//        double dnum = CStrA::ConvertStrToDouble(num.c_str());
//        qnum.push(dnum); 
//    }
//    *result = queueCalculate(&qnum, &qsymbol);
//    return state;
//}
//
//double CStrA::round(double x) 
//{     
//	int sa = 0, si = 0;  
//	if(x == 0.0)   
//	{
//		return 0.0; 
//	}
//	else    
//	{
//		if(x > 0.0)  
//		{
//			sa = (int)x;   
//			si = (int)(x + 0.5);        
//			if(sa == floor((double)si))   
//			{
//				return sa;    
//			}
//			else     
//			{
//				return sa + 1; 
//			}
//		}       
//		else    
//		{
//			sa = (int)x;   
//			si = (int)(x - 0.5);      
//			if(sa == ceil((double)si))  
//			{
//				return sa;       
//			}
//			else         
//			{
//				return sa - 1;      
//			}
//		}
//	}
//}
//
////double数取模 x % y
//double CStrA::mod(double x, double y)
//{
//    //double取余
//    //printf("x:%f ", x);
//    double deres = x / y; 
//    double intres = floor(deres);
//    //printf("intres:%f ", intres);
//    deres -= intres;
//    //printf("floatres:%f ", deres);
//    //printf("res:%f ", deres * y);
//    double res = deres * y;
//    return res;
//}
//
//void CStrA::ANSCToUnicode(string& out, const char* inSrc)
//{
//	if (!inSrc)
//	{
//		return ;
//	}
//	out = CodeConvert_Win(inSrc, CP_UTF8, CP_ACP).ToString();
//}
//
//int CStrA::Compress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata)
//{
//	return compress(zdata, nzdata, data, ndata);
//}
//
//void CStrA::Contact(wchar_t *str, LPCTSTR str1, LPCTSTR str2, LPCTSTR str3)
//{
//	str[0] = _T('\0');
//	lstrcat(str, str1);
//	if(lstrlen(str2) > 0)
//	{
//		lstrcat(str, str2);
//	}
//	if(lstrlen(str3) > 0)
//	{
//		lstrcat(str, str3);
//	}
//}
//
//String CStrA::ConvertThousands(double value, int digit)
//{
//	if(digit == 0)
//	{
//		double newValue = round(value);
//		if(abs(newValue - value) < 1)
//		{
//			value = newValue;
//		}
//	}
//	wchar_t szValue[100] = {0};
//	String strValue = CStr::ConvertDoubleToStr(value);
//	strValue = strValue.substr(0, strValue.find(L"."));
//    strValue = CStrA::Replace(strValue, L"-", L"");
//	//_stprintf_s(szValue, 99, L"%I64d", (_int64)abs(round(value)));
//	String str = strValue;
//	int strSize = (int)str.size();
//	String result = L"";
//	for(int i = 0; i < strSize; i++)
//	{
//		result = str[strSize - i - 1] + result;
//		if(i != strSize - 1 && (i > 0 && (i + 1) % 3 == 0))
//		{
//			result = L"," + result;
//		}
//	}
//	if(value < 0)
//	{
//		result = L"-" + result;
//	}
//	if(digit > 0)
//	{
//		GetValueByDigit(value, digit, szValue);
//		String dszValue = szValue;
//		if(dszValue.find(L".") != -1)
//		{
//			result += L"." + dszValue.substr(dszValue.find(L".") + 1);
//		}
//	}
//	return result;
//}
//
//string CStrA::ConvertDBCodeToFileName(const string& code)
//{
//	string fileName = code;
//	if (fileName.find(".") != -1)
//    {
//        fileName = fileName.substr(fileName.find('.') + 1) + fileName.substr(0, fileName.find('.'));
//    }
//	fileName += ".txt";
//	return fileName;
//}
//
//string CStrA::ConvertDBCodeToSinaCode(const string& code)
//{
//	string securityCode = code;
//	int index = (int)securityCode.find(".SH");
//    if (index > 0)
//    {
//        securityCode = "sh" + securityCode.substr(0, securityCode.find("."));
//    }
//    else
//    {
//        securityCode = "sz" + securityCode.substr(0, securityCode.find("."));
//    }
//	return securityCode;
//}
//
//string CStrA::ConvertDBCodeToTencentCode(const string& code)
//{
//	string securityCode = code;
//	int index = (int)securityCode.find(".");
//	if(index > 0)
//	{
//		index = (int)securityCode.find(".SH");
//		if (index > 0)
//		{
//			securityCode = "sh" + securityCode.substr(0, securityCode.find("."));
//		}
//		else
//		{
//			securityCode = "sz" + securityCode.substr(0, securityCode.find("."));
//		}
//	}
//	return securityCode;
//}
//
//String CStrA::ConvertSinaCodeToDBCode(const String& code)
//{
//	int equalIndex = (int)code.find(L"=");
//	int startIndex = (int)code.find(L"var hq_str_") + 11;
//	String securityCode = equalIndex > 0 ?code.substr(startIndex, equalIndex - startIndex) : code;
//	if (securityCode.find(L"sh") == 0 || securityCode.find(L"SH") == 0)
//	{
//		securityCode = securityCode.substr(2) + L".SH";
//	}
//	else if (securityCode.find(L"sz") == 0 || securityCode.find(L"SZ") == 0)
//	{
//		securityCode = securityCode.substr(2) + L".SZ";
//	}
//	return securityCode;
//}
//
//double CStrA::ConvertStrToDouble(const wchar_t *str)
//{
//	return _wtof(str);
//}
//
//int CStrA::ConvertStrToInt(const wchar_t *str)
//{
//	return _wtoi(str);
//}
//
//String CStrA::ConvertTencentCodeToDBCode(const String& code)
//{
//	int equalIndex = (int)code.find(L'=');
//	String securityCode = equalIndex > 0 ? code.substr(0, equalIndex) : code;
//	if (securityCode.find(L"v_sh") == 0)
//	{
//		securityCode = securityCode.substr(4) + L".SH";
//	}
//	else if (securityCode.find(L"v_sz") == 0)
//	{
//		securityCode = securityCode.substr(4) + L".SZ";
//	}
//	return securityCode;
//}
//
//int CStrA::DeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata)
//{
//	return uncompress(data, ndata, zdata, nzdata);
//}
//
//bool CStrA::IsBlank(int c)
//{
//  if((c == ' ') || (c == '\t'))
//  {
//    return true;
//  }
//  else
//  {
//    return false;
//  }
//}
//
//bool CStrA::IsChinese(const String& str)
//{
//    //char szChinese[3] = {0}; 
//    //string pagChar;
//    //CStr::wstringTostring(pageChar, str);
//    //const char *szText = pageChar.c_str();
//    //int i = 0, nLen = (int)strlen(szText); 
//    //for(; i < length; i++) 
//    //{ 
//    //    if( szText[i] >= 0 && szText[i] <= 127 ) //不是全角字符？ 
//    //    else //是全角字符 
//    //    szChinese[0] = szText[i], szChinese[1] = szText[i + 1], i++, length++;//中文是2个字节,所以i++ 
//    //}
//    return true;
//}
//
//int CStrA::IsNum(const String& str)
//{
//    string text;
//    CStrA::wstringTostring(text, str);
//    return IsNumeric(text);
//}
//
//int CStrA::IsNumeric(const string& str)
//{
//  if (str == "") 
//  {
//    return 0;  
//  }
//  int size = (int)str.size();
//  int count = 0;
//  int base = 10;  
//  const char *ptr = str.c_str();
//  //char *ptr = new char[size];
//  //memset(ptr, 0, size);
//  // memcpy(ptr, str.c_str(), size);
//  //str.copy(ptr, size, 0);
//  int type = 0;
//  /* skip blank */  
//  while (IsBlank(*ptr)) 
//  {  
//    ptr++;  
//  }  
//
//  /* skip sign */  
//  if (*ptr == '-' || *ptr == '+') 
//  {
//    ptr++;  
//  }  
//  /* first char should be digit or dot*/  
//  if (isdigit(*ptr) || ptr[0]=='.') 
//  {  
//    if (ptr[0]!='.') 
//    {
//      /* handle hex numbers */  
//      if (ptr[0] == '0' && ptr[1] && (ptr[1] == 'x' || ptr[1] == 'X')) 
//      {
//        type = 2;  
//        base = 16;  
//        ptr += 2;  
//      }
//      /* Skip any leading 0s */
//      while (*ptr == '0')
//      {  
//        ptr++;  
//      }
//      /* Skip digit */  
//      while (isdigit(*ptr) || (base == 16 && isxdigit(*ptr)))
//      {  
//        ptr++;  
//      }  
//    }  
//
//    /* Handle dot */  
//    if (base == 10 && *ptr && ptr[0] == '.')
//    {  
//      type = 3;  
//      ptr++;  
//    }  
//
//    /* Skip digit */  
//    while (type == 3 && base == 10 && isdigit(*ptr)) 
//    {  
//      ptr++;  
//    }  
//
//    /* if end with 0, it is number */  
//    if (*ptr == 0)
//    {
//      //return (type > 0 ) ? type : 1;
//      type = (type >0 ) ? type : 1;
//    }
//    else 
//    {
//      type = 0;
//    }
//  }
//  return type;
//}
//
//int CStrA::FindNum(const String& text, int index)
//{
//    int size = (int)text.size();
//    int i = index;
//	for(; i < size; ++i)
//	{
//		if(isdigit(text[i]))
//		{
//			return i;
//		}
//	}
//	return -1;
//}
//
//String CStrA::GetDBString(const String& strSrc)
//{
//	String str = Replace(strSrc, L"'", L"''");
//	return str;
//}
//
//string CStrA::GetGuid()
//{
//	static char buf[64] = {0};
//	GUID guid;
//	if (S_OK == ::CoCreateGuid(&guid))
//	{
//		_snprintf(buf, sizeof(buf)
//			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
//			, guid.Data1
//			, guid.Data2
//			, guid.Data3
//			, guid.Data4[0], guid.Data4[1]
//		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
//		, guid.Data4[6], guid.Data4[7]
//		);
//	}
//	return buf;
//}
//
//void CStrA::GetFormatDate(double date, wchar_t *str)
//{
//
//	int year = 0,month = 0,day = 0,hour = 0,minute = 0,second = 0,msecond = 0;
//	M130(date, &year, &month, &day, &hour, &minute, &second, &msecond);
//	_stprintf_s(str, 99, L"%d/%d/%d", year, month, day);
//}
//
//String CStrA::GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second)
//{
//	static wchar_t str[100] = {0};
//	_stprintf_s(str, 99, format.c_str(), year, month, day, hour, minute, second);
//	return str;
//}
//
//String CStrA::GetFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec)
//{
//	static wchar_t str[100] = {0};
//	_stprintf_s(str, 99, format.c_str(), year, month, day, hour, minute, second, msec);
//	return str;
//}
//
//int CStrA::GetStringCapacity(const string& str)
//{
//	return (int)str.length() + 1 + sizeof(_int64);
//}
//
//int CStrA::GetWStringCapacity(const String& str)
//{
//	return ((int)str.length() + 1) * 2 + sizeof(_int64);
//}
//
//void CStrA::GetValueByDigit(double value, int digit, wchar_t *str)
//{
//	if(digit == 0)
//	{
//		double newValue = round(value);
//		if(abs(newValue - value) < 1)
//		{
//			value = newValue;
//		}
//	}
//	switch(digit)
//	{
//	case 1:
//		_stprintf_s(str, 99, L"%.1f", value);
//		break;
//	case 2:
//		_stprintf_s(str, 99, L"%.2f", value);
//		break;
//	case 3:
//		_stprintf_s(str, 99, L"%.3f", value);
//		break;
//	case 4:
//		_stprintf_s(str, 99, L"%.4f", value);
//		break;
//	case 5:
//		_stprintf_s(str, 99, L"%.5f", value);
//		break;
//	default:
//		_stprintf_s(str, 99, L"%d", (long)value);
//	}
//	str = 0;
//}
//
//String CStrA::GetValueByDigit2(double value, int digit)
//{
//    wchar_t wchar[1024] = {0};
//    GetValueByDigit(value, digit, wchar);
//    String str = wchar;
//    return str;
//}
//
///* Compress gzip data */
///* data 原数据 ndata 原数据长度 zdata 压缩后数据 nzdata 压缩后长度 */
//int CStrA::GZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata)
//{
//	z_stream c_stream;
//	int err = 0;
//
//	if(data && ndata > 0) 
//	{
//		c_stream.zalloc = Z_NULL;
//		c_stream.zfree = Z_NULL;
//		c_stream.opaque = Z_NULL;
//		//只有设置为MAX_WBITS + 16才能在在压缩文本中带header和trailer
//		if(deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
//			MAX_WBITS + 16, 6, Z_DEFAULT_STRATEGY) != Z_OK) 
//		{
//			return -1;
//		}
//
//		c_stream.next_in  = data;
//		c_stream.avail_in  = ndata;
//		c_stream.next_out = zdata;
//		c_stream.avail_out  = *nzdata;
//		while(c_stream.avail_in != 0 && c_stream.total_out < *nzdata) 
//		{
//			if(deflate(&c_stream, Z_NO_FLUSH) != Z_OK) 
//			{
//				return -1;
//			}
//		}
//
//		if(c_stream.avail_in != 0) 
//		{
//			return c_stream.avail_in;
//		}
//
//		for(;;) 
//		{
//			if((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END)
//			{
//				break;
//			}
//			if(err != Z_OK)
//			{
//				return -1;
//			}
//		}
//
//		if(deflateEnd(&c_stream) != Z_OK)
//		{
//			return -1;
//		}
//		*nzdata = c_stream.total_out;
//		return 0;
//	}
//	return -1;
//}
//
///* Uncompress gzip data */
///* zdata 数据 nzdata 原数据长度 data 解压后数据 ndata 解压后长度 */
//int CStrA::GZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata)
//{
//	int err = 0;
//	z_stream d_stream = {0}; /* decompression stream */
//	static char dummy_head[2] = 
//	{
//		0x8 + 0x7 * 0x10,
//		(((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
//	};
//
//	d_stream.zalloc = Z_NULL;
//	d_stream.zfree = Z_NULL;
//	d_stream.opaque = Z_NULL;
//	d_stream.next_in  = zdata;
//	d_stream.avail_in = 0;
//	d_stream.next_out = data;
//	//只有设置为MAX_WBITS + 16才能在解压带header和trailer的文本
//	if(inflateInit2(&d_stream, MAX_WBITS + 16) != Z_OK) 
//	{
//		return -1;
//	}
//
//	//if(inflateInit2(&d_stream, 47) != Z_OK) return -1;
//	while(d_stream.total_out < *ndata && d_stream.total_in < nzdata) 
//	{
//		d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
//		if((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END)
//		{
//			break;
//		}
//		if(err != Z_OK) 
//		{
//			if(err == Z_DATA_ERROR) 
//			{
//				d_stream.next_in = (Bytef*) dummy_head;
//				d_stream.avail_in = sizeof(dummy_head);
//
//				if((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK) 
//				{
//					return -1;
//				}
//			} else
//			{
//				return -1;
//			}
//		}
//	}
//	if(inflateEnd(&d_stream) != Z_OK)
//	{
//		return -1;
//	}
//	*ndata = d_stream.total_out;
//	return 0;
//}
//
//double CStrA::M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec)
//{
//	struct tm t;
//	time_t tn;
//	t.tm_sec = tm_sec;
//	t.tm_min = tm_min;
//	t.tm_hour = tm_hour;
//	t.tm_mday = tm_mday;
//	t.tm_mon = tm_mon - 1;
//	t.tm_year = tm_year - 1900;
//	tn = mktime(&t);
//	return (double)tn + (double)tm_msec / 1000 + 28800;
//}
//
//void CStrA::M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec)
//{
//	time_t tn = (_int64)num;
//	struct tm* t = gmtime(&tn);
//	*tm_sec = t->tm_sec;
//	*tm_min = t->tm_min;
//	*tm_hour = t->tm_hour;
//	*tm_mday = t->tm_mday;
//	*tm_mon = t->tm_mon + 1;
//	*tm_year = t->tm_year + 1900;
//	*tm_msec = (int)((num * 1000 - floor(num) * 1000));
//}
//
//string CStrA::Replace(const string& str, const string& src, const string& dest)
//{
//	string newStr = str;
//	std::string::size_type pos = 0;
//	while( (pos = newStr.find(src, pos)) != string::npos )
//	{
//		newStr.replace(pos, src.length(), dest);
//		pos += dest.length();
//	}
//	return newStr;
//}
//
//String CStrA::Replace(const String& str, const String& src, const String& dest)
//{
//	String newStr = str;
//	String::size_type pos = 0;
//	while( (pos = newStr.find(src, pos)) != string::npos )
//	{
//		newStr.replace(pos, src.length(), dest);
//		pos += dest.length();
//	}
//	return newStr;
//}
//
//double CStrA::RoundFloat(double price)
//{
//    return (floor(price * 100 + 0.5)) / 100;
//}
//
//vector<string> CStrA::Split(const string& str, const string& pattern)
//{
//	 int pos = -1;
//	 vector<string> result;
//	 string newStr = str;
//	 newStr += pattern;
//	 int size = (int)str.size();
//	 for(int i = 0; i < size; i++)
//	 {
//		pos = (int)newStr.find(pattern, i);
//		if((int)pos <= size)
//		{
//			string s = newStr.substr(i, pos - i);
//			if(s.length() > 0)
//			{
//				result.push_back(s);
//			}
//			i = pos + (int)pattern.size() - 1;
//		}
//	}
//	return result;
//}
//
//vector<String> CStrA::Split2(const String& str, const String& pattern)
//{
//	  int pos = -1;
//	 vector<String> result;
//	 String newStr = str;
//	 newStr += pattern;
//	 int size = (int)newStr.size();
//	 for(int i = 0; i < size; i++)
//	 {
//		pos = (int)newStr.find(pattern, i);
//		if((int)pos <= size)
//		{
//			String s = newStr.substr(i, pos - i);
//			result.push_back(s);
//			i = pos + (int)pattern.size() - 1;
//		}
//	}
//	return result;
//}
//
//vector<String> CStrA::Split(const String& str, const String& pattern)
//{
//	 int pos = -1;
//	 vector<String> result;
//	 String newStr = str;
//	 newStr += pattern;
//	 int size = (int)str.size();
//	 for(int i = 0; i < size; i++)
//	 {
//		pos = (int)newStr.find(pattern, i);
//		if((int)pos <= size)
//		{
//			String s = newStr.substr(i, pos - i);
//			result.push_back(s);
//			i = pos + (int)pattern.size() - 1;
//		}
//	}
//	return result;
//}
//
void CStrA::stringTowstring(wstring &strDest, const string& strSrc)
{
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), -1, 0, 0);
	wchar_t *pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode,0,(unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, strSrc.c_str(), - 1, (LPWSTR)pUnicode, unicodeLen);
	strDest = ( wchar_t* )pUnicode;
	delete[] pUnicode;
}
//
//String CStrA::ToLower(const String& str)
//{
//	String lowerStr = str;
//	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), tolower);
//	return lowerStr;
//}
//
//String CStrA::ToUpper(const String& str)
//{
//	String upperStr = str;
//	transform(upperStr.begin(), upperStr.end(), upperStr.begin(), toupper);
//	return upperStr;
//}
//
//void CStrA::Trim(string &str)
//{
//	int index = 0;
//    if((int)str.length() > 0)
//    {
//        while((index = str.find(' ', index)) != string::npos)
//        {
//            str.erase(index, 1);
//        }
//    }
//}
//
//void CStrA::Trim(String &str)
//{
//	int index = 0;
//	if((int)str.length() > 0)
//    {
//        while((index = str.find(L' ', index)) != String::npos)
//        {
//            str.erase(index, 1);
//        }
//    }
//}
//
//void CStrA::Trim2(String &str)
//{
//	int i , len ;
//    //先去除左边的空格
//    len = str.length();
//    for(i = 0; i < len; i++)
//    {
//        if(str[i] != L' ') break ;
//    }
//    str.erase(0, i);
//
//    //再去除右边的空格
//    len = str.length();
//    for(i = len - 1; i >= 0; i--)
//    {
//        if(str[i] != L' ') break ;
//    }
//    str.erase(++i, len);
//
//    return ;
//}
//
//void CStrA::UnicodeToANSC(string& out, const char* inSrc)
//{
//	if (!inSrc)
//	{
//		return ;
//	}
//	out = CodeConvert_Win(inSrc, CP_ACP, CP_UTF8).ToString();
//}
//
//bool CStrA::ValueEqual(float lhs, float rhs)
//{
//	return lhs - rhs >= -0.00001 && lhs - rhs <= 0.00001;
//}
//
//bool CStrA::ValueEqual(double lhs, double rhs)
//{
//	return lhs - rhs >= -0.00001 && lhs - rhs <= 0.00001;
//}
//
//String CStrA::VecToString(vector<String> *vec)
//{
//	String result;
//	int size = vec->size();
//	for(int i = 0; i < size; i++)
//	{
//		result += (L"," + (*vec)[i]);
//	}
//	return result;
//}
//
void CStrA::wstringTostring(string &strDest, const wstring& strSrc)
{
	int iTextLen = WideCharToMultiByte(CP_ACP, 0, strSrc.c_str(), -1, NULL, 0, NULL, NULL);
	char *pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte(CP_ACP, 0, strSrc.c_str(), - 1, pElementText, iTextLen, 0, 0);
	strDest = pElementText;
	delete[] pElementText;
}
//
//void CStrA::RestartApp()    
//{
//    char szAppPath[1024];
//	::GetModuleFileNameA( NULL, szAppPath, 1024);
//	string appPath = szAppPath;
//	int pos = (int)appPath.rfind("\\") + 1;
//	string szExeName = appPath.substr(pos, appPath.length() - pos);
//	char content[1024] = {0};
//	sprintf(content, "@echo off\n:a\n taskkill /F /IM %s\n start \"\" \"%s\" \ndel %%0", szExeName.c_str(), szAppPath);
//	string cmPath = DataCenter::GetAppPath() + "restart.cmd";
//	CFileA::Write(cmPath.c_str(), content);
//    STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//	int sisize = sizeof(si);
//    ZeroMemory(&si, sisize);
//    ZeroMemory(&pi, sizeof(pi));
//    si.cb = sisize;
//    si.dwFlags = STARTF_USESHOWWINDOW;
//    si.wShowWindow = SW_HIDE;
//    wchar_t winSysDir[1024];
//	::ZeroMemory(winSysDir, sizeof(winSysDir));
//    ::GetSystemDirectory(winSysDir, 1024);
//    String appName = winSysDir;
//    appName += L"\\cmd.exe";
//	String wCmPath;
//	CStrA::stringTowstring(wCmPath, cmPath);
//	wchar_t cm[1024] = {0};
//	swprintf(cm, 1023, L"/c %s", wCmPath.c_str());
//	::CreateProcess(appName.c_str(), cm, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
//}
//
//string CStrA::UTF8ToGBK(const string& strUTF8)
//{  
//	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);  
//	WCHAR* wszGBK = new WCHAR[len+1];
//	memset(wszGBK, 0, len * 2 + 2);  
//	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)(LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);
// 
//	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
//	char *szGBK = new char[len + 1];  
//	memset(szGBK, 0, len + 1);  
//	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);   
//	std::string strTemp(szGBK);  
//	delete[]szGBK;  
//	delete[]wszGBK;  
//	return strTemp;  
//}
//
//string CStrA::GBKToUTF8(const string& gbk)
//{
//    int len = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);
//    wchar_t* wstr = new wchar_t[len + 1];
//    memset(wstr, 0, len + 1);
//    
//    MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, wstr, len);
//    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//    
//    char* str = new char[len + 1];
//    memset(str, 0, len + 1);
//    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//
//    delete[] wstr;
//    return str;
//}