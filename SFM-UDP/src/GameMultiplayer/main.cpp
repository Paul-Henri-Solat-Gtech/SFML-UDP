#include "pch.h"
#include "main.h"
#include <SFML/Graphics.hpp>

int main()
{
    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // Shapes
    sf::CircleShape newCircle(50.f);
    newCircle.setFillColor(sf::Color::Cyan);
    newCircle.setPosition(10, 10);

    // Boucle
    while (window.isOpen())
    {
        // Update
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear
        window.clear(sf::Color::Black);

        // Draw
        window.draw(newCircle);

        // End
        window.display();
    }

    return 0;
}