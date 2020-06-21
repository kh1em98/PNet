#include "IPEndPoint.h"

namespace PNet
{
	IPEndPoint::IPEndPoint(string ip, unsigned short port)
	{
		this->port = port; 
		const char* ipChar = ip.c_str();


		in_addr addr; // Luu dia chi IP
		int result = inet_pton(AF_INET, ipChar, &addr); // Chuyen dang presentation IP sang dang 
		if (result == 1)
		{
			hostname = ip; 
			ip_string = ip; 
			ip_bytes.resize(sizeof(u_long)); // 4 phan tu
			memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(u_long));
			return; 
		}
		else
		{
			cout << "Day khong phai IPv4" << endl; 
		}
	}

	IPEndPoint::IPEndPoint(sockaddr* addr)
	{
		sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
		port = ntohs(addrv4->sin_port);
		ip_bytes.resize(4);
		memcpy(&ip_bytes[0], &addrv4->sin_addr.S_un.S_addr, 4);
		ip_string.resize(16);
		inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
		hostname = ip_string;
	}

	string IPEndPoint::GetHostName()
	{
		return hostname; 
	}

	IpVersion IPEndPoint::GetIpVersion()
	{
		return ipversion; 
	}

	string IPEndPoint::GetIpString()
	{
		return ip_string;
	}
	vector<uint8_t> IPEndPoint::GetIpBytes()
	{
		return ip_bytes;
	}

	unsigned short IPEndPoint::GetPort()
	{
		return port;
	}
	sockaddr_in IPEndPoint::GetSockAddrIpv4()
	{
		sockaddr_in result = {};
		result.sin_family = AF_INET;
		result.sin_port = htons(port);
		memcpy(&result.sin_addr, &ip_bytes[0], 4);
		return result; 
	}
	void IPEndPoint::Print()
	{
		cout << "Port : " << this->GetPort() << endl;
		cout << "IP : " << this->GetHostName() << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << (int)this->GetIpBytes()[i] << endl;
		}
		cout << endl;
	}
}


