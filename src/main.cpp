#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Theme.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow win(sf::VideoMode(800, 800), "Chess", sf::Style::Titlebar | sf::Style::Close);
    win.setFramerateLimit(30);

    Theme theme
    {
        sf::Color(255, 255, 255),
        sf::Color(128, 128, 128),
        sf::Color(255, 200, 000)
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

                if (!board.IsOver())
                {
                    if (code == 0)
                    {
                        auto moves = board.PossibleMoves();

                        int len = int(moves.size());
                        std::cout << len << std::endl;

                        int row = y / 100;
                        int col = x / 100;

                        board.LeftClick(row, col);
                    }
                }

                // Right click
                if (code == 1)
                {
                    int row = y / 100;
                    int col = x / 100;

                    board.RightClick(row, col);

                    board.Test(0, 0);
                }
            }
        }

        win.clear();

        board.Draw(win);

        win.display();
    }

    return 0;
}
