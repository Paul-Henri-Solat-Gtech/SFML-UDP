#include "pch.h"
#include "Network.h"

Network::Network()
{
	m_socket = 0;
}

bool Network::InitSocket() 
{
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "Erreur creation socket : " << WSAGetLastError() << std::endl;
		return false;
	}
	else
	{
		return true;
	}

}

// Intialise DLL to use network
void Network::InitDLL() 
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
}

void Network::UninInitNetwork() 
{
	closesocket(m_socket);
	WSACleanup();
}

void Network::SendMsgTo(sockaddr_in& addrDestinataire)
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

bool Network::RecieveMsg()
{
	// Buffer
	sockaddr_in addrSender = { 0 };
	int addrClientLen = sizeof(addrSender);
	char data[1024];

	int nb = recvfrom(m_socket, data, sizeof(data), 0, reinterpret_cast<sockaddr*>(&addrSender), &addrClientLen);
	if (nb > 0) {
		// Keeping the senderAdress
		m_addressConnectedTo = addrSender;

		// Ajout du caractere nul a la fin du msg
		data[nb] = '\0';

		// Ip Sender
		char senderIp[INET6_ADDRSTRLEN];
		std::string clientAddress = inet_ntop(addrSender.sin_family, (void*)&(addrSender.sin_addr), senderIp, INET6_ADDRSTRLEN);
		//std::cout << "Connexion de " << clientAddress.c_str() << ":" << ntohs(addrSender.sin_port) << std::endl;

		// Recu du msg
		std::cout << "Message de " << clientAddress.c_str() << " : " << data << std::endl;

		// Optionnel : envoyer une réponse
		/*const char* response = "Message recus 5 sur 5 !";
		sendto(m_socket, response, strlen(response), 0, reinterpret_cast<sockaddr*>(&addrSender), sizeof(addrSender));*/
		return true;
	}
	else
	{
		std::cout << "Erreur reception des donnees : " << WSAGetLastError() << std::endl;
		return false;
	}
}

Adress::Adress() 
{
	m_adress.sin_port = 0;
	m_adress.sin_family = 0;
}
bool Adress::Init(USHORT port, ADDRESS_FAMILY addressFamily)
{
	m_adress.sin_port = port;
	m_adress.sin_family = addressFamily;

	return true;
}
bool Adress::Init(USHORT port, ADDRESS_FAMILY addressFamily, ULONG acceptedAdress)
{
	m_adress.sin_port = port; // Traduction du port en reseau
	m_adress.sin_family = addressFamily; // Notre socket est de type : TCP/UDP
	m_adress.sin_addr.s_addr = acceptedAdress; // Indique les sources seront acceptees

	return true;
}
