#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>

namespace PNet
{
	class Network
	{
	public:
		// Khoi tao Winsock
		static bool Initialize(); 

		// Dong winsock 
		static bool Shutdown();
	};
}