#include "GUI/Menu.h"
#include <SFML/Graphics.hpp>

bool showConfirmationDialog(sf::RenderWindow& window)
{
    sf::RenderWindow confirmationWindow(sf::VideoMode(300, 150), "Confirm Quit");
    confirmationWindow.setVerticalSyncEnabled(true);

    sf::Text confirmationText;
    sf::Font font;
    font.loadFromFile("Resources/Fonts/Inkfree.ttf"); // Replace with the path to your font file
    confirmationText.setFont(font);
    confirmationText.setString("Are you sure you want to quit?\nUnsaved changes will be lost.");
    confirmationText.setCharacterSize(20);
    confirmationText.setPosition(20, 20);

    sf::Text yesText;
    yesText.setFont(font);
    yesText.setString("Yes");
    yesText.setCharacterSize(20);
    yesText.setPosition(80, 100);

    sf::Text noText;
    noText.setFont(font);
    noText.setString("No");
    noText.setCharacterSize(20);
    noText.setPosition(180, 100);

    bool shouldCloseApplication = false;
    bool userChoiceMade = false;

    while (confirmationWindow.isOpen())
    {
        sf::Event confirmEvent;
        while (confirmationWindow.pollEvent(confirmEvent))
        {
            if (confirmEvent.type == sf::Event::Closed)
            {
                confirmationWindow.close();
            }
            else if (confirmEvent.type == sf::Event::MouseButtonPressed)
            {
                if (confirmEvent.mouseButton.button == sf::Mouse::Left)
                {
                    if (yesText.getGlobalBounds().contains(confirmEvent.mouseButton.x, confirmEvent.mouseButton.y))
                    {
                        shouldCloseApplication = true;
                        userChoiceMade = true;
                        confirmationWindow.close();
                    }
                    else if (noText.getGlobalBounds().contains(confirmEvent.mouseButton.x, confirmEvent.mouseButton.y))
                    {
                        userChoiceMade = true;
                        confirmationWindow.close();
                    }
                }
            }
        }

        confirmationWindow.clear();
        confirmationWindow.draw(confirmationText);
        confirmationWindow.draw(yesText);
        confirmationWindow.draw(noText);
        confirmationWindow.display();
    }

    return shouldCloseApplication;
}