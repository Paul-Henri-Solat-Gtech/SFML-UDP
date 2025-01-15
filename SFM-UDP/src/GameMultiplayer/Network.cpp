#include "pch.h"
#include "Network.h"

Network::Network()
{
	// Intialise DLL
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "Erreur creation socket : " << WSAGetLastError() << std::endl;
		return;
	}
}

void Network::SendMsg(sockaddr_in& addrDestinataire)
{
	std::string text;
	std::cout << "Enter text to Send : ";
	std::cin >> text;
	const char* msg = text.c_str();

	int ret = sendto(m_socket, msg, strlen(msg), 0, reinterpret_cast<const sockaddr*>(&addrDestinataire), sizeof(addrDestinataire));
	if (ret < 0)
	{
		std::cout << "Impossible denvoyer : " << WSAGetLastError() << std::endl;
		return;
	}
	std::cout << "Envoie terminer ! " << std::endl;

	//SendMsg(mySocket, addrDestinataire);
}

Adress::Adress(USHORT port, ADDRESS_FAMILY addressFamily)
{
	m_adress.sin_port = port;
	m_adress.sin_family = addressFamily;

}
Adress::Adress(USHORT port, ADDRESS_FAMILY addressFamily, ULONG acceptedAdress)
{
	m_adress.sin_port = port;
	m_adress.sin_family = addressFamily;
	m_adress.sin_addr.s_addr = acceptedAdress;
}