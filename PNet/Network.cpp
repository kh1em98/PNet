#pragma once
#include "Network.h"
#include <iostream>

namespace PNet
{
	bool Network::Initialize()
	{
		WSADATA wsaData; 
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
		{
			std::cout << "Khong the khoi tao ket noi" << std::endl; 
			return false; 
		}

		return true; 
	}
	bool Network::Shutdown()
	{
		WSACleanup();
		return true; 
	}
}