#include "Socket.h"

namespace PNet
{
	Socket::Socket()
	{
		ipversion = IpVersion::Ipv4;
		handle = INVALID_SOCKET;
	}
	Socket::Socket(IpVersion ipversion, SOCKET handle)
	{
		ipversion = ipversion;
		handle = handle;
	}

	PResult Socket::SetSocketOption(SocketOption option, BOOL value)
	{
		if (handle == INVALID_SOCKET)
		{
			return PResult::P_Error;
		}
		int result; 
		switch (option)
		{
		// Huy nagle algorithm
		case TCP_NoDelay:
			result = setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
			break;
		default:
			return PResult::P_Error;
		}
		if (result == 0)
		{
			return PResult::P_Sucesss;
		}
		int error = WSAGetLastError();
		return PResult::P_Error;

	}

	PResult Socket::Create()
	{
		// Neu socket da duoc khoi tao, khong duoc khoi tao lai
		if (handle != INVALID_SOCKET)
		{
			return PResult::P_Error;
		}

		// Khoi tao socket
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Kiem tra loi khoi tao
		if (handle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return PResult::P_Error;
		}

		if (SetSocketOption(TCP_NoDelay, TRUE) == PResult::P_Error)
		{
			return PResult::P_Error;
		}

		return PResult::P_Sucesss;
	}

	PResult Socket::Close()
	{
		// Neu socket chua duoc khoi tao, khong the dong
		if (handle == INVALID_SOCKET)
		{
			return PResult::P_Error;
		}
		int result = closesocket(handle);
		handle = INVALID_SOCKET;
		if (result == 0)
		{
			return PResult::P_Sucesss;
		}
		int error = WSAGetLastError();
		return PResult::P_Error;
	}

	PResult Socket::Bind(IPEndPoint a)
	{
		sockaddr_in addr = a.GetSockAddrIpv4(); 
		int result = bind(handle, (sockaddr*)&addr, sizeof(addr));
		if (result != 0)
		{
			int error = WSAGetLastError(); 
			return PResult::P_Error;
		}
		return PResult::P_Sucesss;
	}

	PResult Socket::Listen(IPEndPoint a, int backlog)
	{
		if (Bind(a) == PResult::P_Error)
		{
			return PResult::P_Error;
		}
		int result = listen(handle, SOMAXCONN);
		if (result != 0)
		{
			int error = WSAGetLastError(); 
			return PResult::P_Error;
		}
		return PResult::P_Sucesss;
	}

	PResult Socket::Accept(Socket& outSocket)
	{
		sockaddr_in addr;
		int len = sizeof(sockaddr_in);

		SOCKET acceptHandle = accept(handle, (sockaddr*)&addr, (int*)&len);
		IPEndPoint infoConnectClient = IPEndPoint((sockaddr*)&addr);

		infoConnectClient.Print(); 

		if (acceptHandle == INVALID_SOCKET)
		{
			int error = WSAGetLastError(); 
			return PResult::P_Error;
		}
		outSocket = Socket(IpVersion::Ipv4, acceptHandle);
		return PResult::P_Sucesss;
	}

	PResult Socket::Connect(IPEndPoint hihi)
	{
		sockaddr_in addr = hihi.GetSockAddrIpv4();
		int result = connect(handle, (sockaddr*)&addr, sizeof(addr));
		if (result != 0)
		{
			int error = WSAGetLastError(); 
			return PResult::P_Error;
		}
		return PResult::P_Sucesss;
	}


	PResult Socket::Send(const void* data, int sizeOfBytes, int& sentBytes)
	{
		sentBytes = send(handle, (const char*)data, sizeOfBytes, NULL);
		if (sentBytes == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return PResult::P_Error;
		}
		return PResult::P_Sucesss;
	}

	PResult Socket::Recv(void* destination, int sizeOfBytes, int& recvBytes)
	{
		recvBytes = recv(handle, (char*)destination, sizeOfBytes, NULL);
		if (recvBytes == 0)
		{
			return PResult::P_Error;
		}
		if (recvBytes == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return PResult::P_Error;
		}
		return PResult::P_Sucesss;
	}


	SOCKET Socket::getHandle()
	{
		return handle; 
	}

	IpVersion Socket::getIpVersion()
	{
		return ipversion; 
	}

}

