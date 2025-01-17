#include "pch.h"
#include "main.h"

#include "Network.h"

int main()
{
    std::cout << "Hello, Im Server!\n";

	Network::InitDLL();

    Network* server = new Network;

	if (server->InitSocket() != true)
	{
		std::cout << "Cannot create socket\n";
	}

	// Initialisation addresse du server (local)
	Adress* localAddr = new Adress;

	if (localAddr->Init(htons(1025), AF_INET, INADDR_ANY) != true)
	{
		std::cout << "Cannot create address\n";
	}

	// Assigne adresse local au socket
	int res = bind(server->GetSocket(), reinterpret_cast<sockaddr*>(&localAddr->GetAdress()), sizeof(localAddr->GetAdress()));

	// Verifie si lassociation a fonctionner
	if (res != 0) {
		std::cout << "Erreur initialisation bind" << std::endl;
		return false;
	}
	std::cout << "Serveur initialise et bind reussi !" << std::endl;
	std::cout << "En attente de connection entrante..." << std::endl;

	if (server->RecieveMsg()) 
	{
		server->SendMsgTo(server->GetAdressConnectedTo());
	}

	server->UninInitNetwork();

    return 0;
}