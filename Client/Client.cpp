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
			IPEndPoint ip("127.0.0.1", 4777);
			if (cac.Connect(ip) == PResult::P_Sucesss)
			{
				cout << "Ket noi thanh cong toi server 4777" << endl; 
				char buffer[256];
				strcpy_s(buffer, "Hello from client\0");
				int bytesSent = 0; 
				int result = PResult::P_Sucesss;
				while (result == PResult::P_Sucesss)
				{
					result = cac.Send(buffer, 256, bytesSent);
					cout << "Dang gui data" << endl; 
					Sleep(500);
				}
			}
			else
			{
				cout << "Ket noi that bai" << endl; 
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