#pragma once
#include "IPVersion.h"
#include "PResult.h"
#include <iostream>
#include <string>
#include <vector>
#include <WS2tcpip.h>

using namespace std; 

namespace PNet
{
	class IPEndPoint
	{
	private:
		IpVersion ipversion = IpVersion::Ipv4;
		string hostname; 
		string ip_string; 
		vector <uint8_t> ip_bytes; 
		unsigned short port = 0; 
	public:
		// Khoi tao IPEndPoint tu 1 chuoi IP va 1 port 
		IPEndPoint(string ip, unsigned short port);
		IPEndPoint(sockaddr* addr);
		string GetHostName();
		IpVersion GetIpVersion();
		string GetIpString(); 
		vector<uint8_t> GetIpBytes(); 
		unsigned short GetPort();
		sockaddr_in GetSockAddrIpv4();
		void Print();

	};
}