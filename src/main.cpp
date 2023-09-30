#include <iostream>

#include "Board.h"
#include "Piece.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow win(sf::VideoMode(800, 800), "Chess", sf::Style::Titlebar | sf::Style::Close);
    win.setFramerateLimit(30);

    Theme theme
    {
        sf::Color(255, 255, 255),
        sf::Color(128, 128, 128)
    };

    Board board(theme);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int code = event.mouseButton.button;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                // Left click
                if (code == 0)
                {
                    auto moves = board.PossibleMoves();

                    int len = moves.size();
                    std::cout << len << std::endl;

                    for (int i = 0; i < len; i++)
                    {
                        auto move = moves[i];
                        std::cout << "(" << move.startX << ", " << move.startY << ")" << "-> (" << move.endX << ", " << move.endY << ")" << std::endl;
                    }
                }

                // Right click
                if (code == 1)
                {

                }
            }
        }

        win.clear();

        board.Draw(win);

        win.display();
    }

    return 0;
}
