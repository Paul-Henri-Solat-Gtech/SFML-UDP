#pragma once

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class Network
{
public:
	Network();

	void SendMsg(sockaddr_in& addrDestinataire);

	SOCKET GetSocket() { return m_socket; };

private:
	SOCKET m_socket;
};

class Adress
{
public:
	Adress(USHORT port, ADDRESS_FAMILY addressFamily);
	Adress(USHORT port, ADDRESS_FAMILY addressFamily, ULONG acceptedAdress);

	sockaddr_in GetAdress() { return m_adress; };

private:
	sockaddr_in m_adress;

};
