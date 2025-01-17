#pragma once

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class Network
{
public:
	Network();
	void UninInitNetwork();

	static void InitDLL();

	bool InitSocket();

	void SendMsgTo(sockaddr_in& addrDestinataire);
	bool RecieveMsg();

	SOCKET GetSocket() { return m_socket; };
	sockaddr_in& GetAdressConnectedTo() { return m_addressConnectedTo; };

private:
	SOCKET m_socket;
	sockaddr_in m_addressConnectedTo;
};

class Adress
{
public:
	Adress();

	bool Init(USHORT port, ADDRESS_FAMILY addressFamily);
	bool Init(USHORT port, ADDRESS_FAMILY addressFamily, ULONG acceptedAdress);

	sockaddr_in& GetAdress() { return m_adress; };

private:
	sockaddr_in m_adress;

};
