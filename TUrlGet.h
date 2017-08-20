#pragma once
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
//#include <Windows.h>


#include <iostream>
#include <string>

using namespace std;


class TUrlGet
{

private:
	string _ip;
	string _recvData;
	char _buff[2048];
	bool _err;
	SOCKET _s;
	void parseUrl(const string& url);
	bool sendGet();
	bool selectSend(int timeout);
	bool selectRecv(int timeout);
	bool conn();
	void postRecv();
	void clearRes();
	string queryDNS(const string & url);

	static string UTF8ToGBK(const std::string& strUTF8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
		unsigned short * wszGBK = new unsigned short[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

		len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
		char *szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP,0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
		//strUTF8 = szGBK;
		std::string strTemp(szGBK);
		delete[]szGBK;
		delete[]wszGBK;
		return strTemp;
	}
public:

	string getRecvData(const string& url,int intval)
	{
		string ret = "";
		parseUrl(url);
		conn();
		if(selectSend(intval) == true)
		{
			if(selectRecv(intval) == true)
			{
				return UTF8ToGBK(_recvData);
			}
			else
			{
				return ret;
			}
		}
		else
		{
			return ret;
		}
	}
	TUrlGet(void);
	
public:
	~TUrlGet(void);
};
