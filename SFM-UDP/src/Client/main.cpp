#include "pch.h"
#include "main.h"

#include "Ball.h"
#include "Network.h"

int main()
{
    std::cout << "Hello, Im Client!\n";

    // ------------------ UDP

    Network::InitDLL();

    Network* client = new Network;

    if (client->InitSocket() != true) 
    {
        std::cout << "Cannot create socket\n";
    }

    Adress* servAddr = new Adress;

    if (servAddr->Init(htons(1025), AF_INET) != true)
    {
        std::cout << "Cannot create address\n";
    }

    if (inet_pton(AF_INET, "127.0.0.1", &servAddr->GetAdress().sin_addr) <= 0)
    {
        // impossible de déterminer l'adresse
        std::cout << "Erreur addresse destinataire : " << WSAGetLastError() << std::endl;
        closesocket(client->GetSocket());
        WSACleanup();
        return 1;
    }
    
    // add threads + while
    client->SendMsgTo(servAddr->GetAdress());
    client->RecieveMsg();

    // ------------------ SFML

    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // Objects
    Ball* ball = new Ball(50, window.getSize().x / 2, window.getSize().y / 2, sf::Color::Magenta);
    Ball* centerBall = new Ball(10,0,0, sf::Color::White);

    ball->SetSpeed(0.02f);
    //std::cout << "posxy:" << ball->GetPosX() << " " << ball->GetPosY();

    // Boucle
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

        }

        // Update
        ball->Update();
        centerBall->SetPosition(ball->GetPosX(), ball->GetPosY());
        
        // Clear
        window.clear(sf::Color::Black);

        // Draw
        window.draw(ball->GetShape());
        window.draw(centerBall->GetShape());

        // End
        window.display();
    }

    client->UninInitNetwork();

    return 0;
}