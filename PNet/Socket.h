#pragma once

#include <WinSock2.h>
#include "PResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndPoint.h"

namespace PNet
{
	class Socket
	{
	private:
		IpVersion ipversion = IpVersion::Ipv4;
		SOCKET handle = INVALID_SOCKET;
	public:
		Socket(); 
		Socket(IpVersion ipversion, SOCKET handle);
		PResult SetSocketOption(SocketOption option, BOOL value);
		PResult Create();
		PResult Close();
		PResult Bind(IPEndPoint a);
		PResult Listen(IPEndPoint a, int backlog = 5); 
		PResult Accept(Socket& outSocket);
		PResult Connect(IPEndPoint hihi);
		PResult Send(const void* data, int sizeOfBytes, int& sentBytes);
		PResult Recv(void* destination, int sizeOfBytes, int& recvBytes);
		SOCKET getHandle();
		IpVersion getIpVersion();
	};
}