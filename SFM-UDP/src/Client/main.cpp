#include "pch.h"
#include "main.h"

#include "Ball.h"
#include "Network.h"

// UDP NETWORK
DWORD WINAPI Static_Udp(void* pParam)
{
    std::cout << "Hello, Im Client!\n";

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

    client->UninInitNetwork();

    return 0;
}

// SFML RENDER
DWORD WINAPI Static_Sfml(void* pParam)
{
    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // Objects
    Ball* ball = new Ball(50, window.getSize().x / 2, window.getSize().y / 2, sf::Color::Magenta);
    Ball* centerBall = new Ball(10, 0, 0, sf::Color::White);

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

    return 0;
}

int main()
{
    // ------------------ THREADS
    // Tableau de ThreadId static
    const int numberOfThreads = 2;
    HANDLE ThreadHandles[numberOfThreads];
    DWORD threadId[numberOfThreads];

    //ThreadHandles[id] = CreateThread(nullptr, 0, fctnName, param, 0, &threadId[id]);
    
    // ------------------ UDP
    ThreadHandles[0] = CreateThread(nullptr, 0, Static_Udp, 0, 0, &threadId[0]);

    // ------------------ SFML
    ThreadHandles[1] = CreateThread(nullptr, 0, Static_Sfml, 0, 0, &threadId[1]);

    for (int i = 0; i < 2; i++)
    {
        if (ThreadHandles[i] == nullptr)
        {
            std::cerr << "Erreur pendant la creation du thread!" << std::endl;
            return 1;
        }
    }

    // Verifie si les threads on finis de sexecuter
    WaitForMultipleObjects(numberOfThreads, ThreadHandles, true, INFINITE);

    // Ferme les Threads apres execution de celles-ci
    for (int i = 0; i < numberOfThreads; i++)
    {
        CloseHandle(ThreadHandles[i]);
    }







   



    return 0;
}