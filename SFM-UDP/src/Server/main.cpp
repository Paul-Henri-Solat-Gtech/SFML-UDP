#include "pch.h"
#include "main.h"

#include "Network.h"

int main()
{
    std::cout << "Hello, Im Server!\n";

    Network* server = new Network;

	// Initialisation addresse du server (local)
	sockaddr_in adresseLocal;
	adresseLocal.sin_port = htons(1025); // Toujours traduire le port en reseau
	adresseLocal.sin_family = AF_INET; // Notre socket est TCP
	adresseLocal.sin_addr.s_addr = INADDR_ANY; // Indique que toutes les sources seront acceptees

	// Assigne adresse local au socket
	int res = bind(server->GetSocket(), reinterpret_cast<sockaddr*>(&adresseLocal), sizeof(adresseLocal));

	// Verifie si lassociation a fonctionner
	if (res != 0) {
		std::cout << "Erreur initialisation bind" << std::endl;
		return false;
	}
	std::cout << "Serveur initialise et bind reussi !" << std::endl;

	std::cout << "En attente de connection entrante..." << std::endl;

	// Connecte le client au serveur
	sockaddr_in addrClient = { 0 };
	int addrClientLen = sizeof(addrClient);

	// Boucle pour recuperer les datas du client
	while (true)
	{
		char data[1024];
		int nb = recvfrom(server->GetSocket(), data, sizeof(data), 0, reinterpret_cast<sockaddr*>(&addrClient), &addrClientLen);
		if (nb > 0) {
			// Ajout du caractere nul a la fin du msg
			data[nb] = '\0';

			// Ip Client
			char clientIp[INET6_ADDRSTRLEN];
			std::string clientAddress = inet_ntop(addrClient.sin_family, (void*)&(addrClient.sin_addr), clientIp, INET6_ADDRSTRLEN);
			std::cout << "Connexion de " << clientAddress.c_str() << ":" << ntohs(addrClient.sin_port) << std::endl;

			// Recu du msg
			std::cout << "Message de " << clientAddress.c_str() << " : " << data << std::endl;

			// Optionnel : envoyer une réponse
			const char* response = "Message recus 5 sur 5 !";
			sendto(server->GetSocket(), response, strlen(response), 0, reinterpret_cast<sockaddr*>(&addrClient), sizeof(addrClient));
		}
		else
		{
			std::cout << "Erreur reception des donnees : " << WSAGetLastError() << std::endl;
		}
	}


	closesocket(server->GetSocket());
	WSACleanup();

    return 0;
}