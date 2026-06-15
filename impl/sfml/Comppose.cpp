#include <iostream>

#include <comppose/Comppose.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

namespace comppose
{
    void Row(Content content)
    {
        std::cout << "Row" << std::endl;
        content();
    }

    void Column(Content)
    {
        std::cout << "Column" << std::endl;
    }

    void Text(std::string &&text)
    {
        std::cout << "Text" << std::endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({320, 240}), "Pontino");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto &resize = event->getIf<sf::Event::Resized>())
            {
                const auto [width, height] = resize->size;
                window.setView(sf::View(sf::FloatRect({0, 0}, {(float)width, (float)height})));
            }
        }

        window.clear(sf::Color::Black);

        Comppose();

        window.display();
    }
}
