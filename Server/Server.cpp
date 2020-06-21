#include <PNet/IncludeMe.h>
#include <iostream>

using namespace PNet;
using namespace std;


int main()
{
	if (Network::Initialize())
	{
		cout << "Network khoi tao thanh cong" << endl; 
		Socket cac;
		if (cac.Create() == PResult::P_Sucesss)
		{
			cout << "Khoi tao socket thanh cong" << endl; 
			IPEndPoint ip("127.0.0.1", 4777);
			int resultListen = cac.Listen(ip);
			if (resultListen == PResult::P_Sucesss)
			{
				cout << "Server dang lang nghe tai 4777" << endl; 
				Socket newConnection;

				if (cac.Accept(newConnection) == PResult::P_Sucesss)
				{
					cout << "Chap nhan ket noi moi" << endl; 
					char buffer[256];
					int bytesReceived = 0; 
					int result = PResult::P_Sucesss;
					while (result == PResult::P_Sucesss)
					{
						result = newConnection.Recv(buffer, 256, bytesReceived);
						if (result == PResult::P_Error)
						{
							break; 
						}
						cout << buffer << endl; 
					}
					newConnection.Close();
				}
			}
			
			cac.Close();
		}
		else
		{
			cout << "Khoi tao socket that bai" << endl; 
		}
	}
	Network::Shutdown();
	system("pause");
}