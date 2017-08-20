#include "StdAfx.h"
#include "TUrlGet.h"

TUrlGet::TUrlGet(void)
{
	_err = false;
	WSADATA wsadata;
	if( WSAStartup( MAKEWORD( 2, 0 ), &wsadata ) != 0 )
	{
		cout << "unable to start winsock error " << GetLastError( ) << endl;
		_err = true;
	}
	memset(_buff,0,2048);
}

TUrlGet::~TUrlGet(void)
{
	clearRes();
	WSACleanup( );
}

string TUrlGet::queryDNS(const string & url)
{
	string ret = "";
	hostent * remoteHost;
	if( (remoteHost = gethostbyname(url.c_str())) == NULL)
	{
		cout<< "gethostbyname error!" << GetLastError( ) << endl;
		_err = true;
	}
	else
	{
		ret += (string)inet_ntoa(*(IN_ADDR*)remoteHost->h_addr_list[0]);  
	}
	return ret;
}

void TUrlGet::parseUrl(const string& url)
{
	string tmpstr = "http://";
	string turl = url.substr(tmpstr.length(),url.length() - tmpstr.length());
	size_t len = turl.find_first_of('/');
	string rurl = turl.substr(0,len);
	string loc = turl.substr(len,turl.length() - len);
	_ip = queryDNS(rurl);
	strcat(_buff,"GET ");
	strcat(_buff,loc.c_str());
	strcat(_buff," HTTP/1.1");
	strcat(_buff,"\r\n");

	strcat(_buff,"Accept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-shockwave-flash, application/x-silverlight, */*");
	strcat(_buff,"\r\n");

	strcat(_buff,"Accept-Language: zh-CN");
	strcat(_buff,"\r\n");

	
	strcat(_buff, "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0)");
	strcat(_buff,"\r\n");

	//strcat(_buff,"Accept-Encoding: gzip, deflate");
	//strcat(_buff,"\r\n");

	strcat(_buff,"Host: ");
	strcat(_buff, rurl.c_str());
	strcat(_buff,"\r\n");

	strcat(_buff, "Connection: Closed");
	strcat(_buff,"\r\n");
	strcat(_buff, "Cache-Control: no-cache");
	strcat(_buff,"\r\n\r\n");
	cout << _buff << endl;
}
bool TUrlGet::conn()
{
	if(_err)
		return false;
	_s = WSASocket(AF_INET, SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
	int nNetTimeout=10000;//10Ãë£¬
	setsockopt(_s,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));
	setsockopt(_s,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(_ip.c_str());
	servaddr.sin_port = htons(80);
	int result = connect(_s, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(result == -1){
		cout << "connect error" <<  GetLastError( ) << endl;
		_err = true;
		return false;
	}
	return true;
}
bool TUrlGet::sendGet()
{
	cout << "i am here" << endl;
	int i = send(_s,_buff,strlen(_buff),0);
	if(i == strlen(_buff))
	{
		_err = false;
		postRecv();
	}
	else
	{
		_err = true;
		cout << "send error" <<  GetLastError( ) << endl;
		return false;
	}

	return true;
}
void TUrlGet::postRecv()
{
	if(_err == true)
		return;
	char rcvBuff[1024] = {0};
	while(true)
	{
		memset(rcvBuff,1024,0);
		int l = recv(_s,rcvBuff,1024,0);
		if(l == 0)
		{
			cout << "server closed" << endl;
			break;
		}
		else if(l < 0)
		{
			cout << "recv error" <<  GetLastError( ) << endl;
			_err = true;
			break;
		}
		else
		{
			_recvData.append(rcvBuff,l);
			cout << l << endl;
			Sleep(10);
		}
	}
	cout << UTF8ToGBK(_recvData) << endl; 
}

void TUrlGet::clearRes()
{
	if(_s != INVALID_SOCKET)
	{
		closesocket(_s);
		_s = INVALID_SOCKET;
	}
}


bool TUrlGet::selectSend(int timeout)
{
	fd_set fdSend;
	timeval TimeOut;
	bool retu = true;
	int ret=0,nLeft=strlen(_buff),idx=0;

	TimeOut.tv_sec=timeout;
	TimeOut.tv_usec=0;

	FD_ZERO(&fdSend);
	FD_SET(_s,&fdSend);
	while(nLeft>0)
	{
		ret=::select(0,NULL,&fdSend,NULL,&TimeOut);
		if(ret==SOCKET_ERROR)
		{
			retu = false;
			break;
		}
		if(ret>0)
		{
			ret=::send(_s,_buff+idx,nLeft,0);
			if(ret==SOCKET_ERROR)
			{
				retu = false;
				break;
			}
			else
			{
				nLeft-=ret;
				idx+=ret;
			}
		}
		else //³¬Ê±
		{
			retu = false;
			cout << "selectSend timeout" << endl;
			break;
		}
	}
	return retu;
}
bool TUrlGet::selectRecv(int timeout)
{
	fd_set fdRecv;
	timeval TimeOut;
	bool retu = true;
	int ret=0,idx=0;

	TimeOut.tv_sec=timeout;
	TimeOut.tv_usec=0;
	char buff[1024];
	FD_ZERO(&fdRecv);
	FD_SET(_s,&fdRecv);
	while(true)
	{
		ret=::select(0,&fdRecv,NULL,NULL,&TimeOut);
		if(ret==SOCKET_ERROR)
		{
			retu = false;
			break;
		}
		if(ret>0)
		{
			memset(buff,1024,0);
			ret=::recv(_s,buff,1024,0);
			if(ret < 0) //SOCKET_ERROR
			{
				retu = false;
				break;
			}
			else if(ret == 0)
			{
				break;
			}
			else
			{
				_recvData.append(buff,ret);
				//cout << ret << endl;
			}
		}
		else //³¬Ê±
		{
			retu = false;
			cout << "selectRecv timeout" << endl;
			break;
		}
	}
	return retu;
}