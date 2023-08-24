/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : MenuOptions.cpp
Description : Implementation of any menu related options
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "GUI/MenuOptions.h"
#include <SFML/Graphics.hpp>

bool showConfirmationDialog(sf::RenderWindow& Window, sf::Font* Font)
{
    sf::RenderWindow ConfirmationWindow(sf::VideoMode(300, 150), "Confirm Quit");
    ConfirmationWindow.setVerticalSyncEnabled(true);

    sf::Text ConfirmationText;
    ConfirmationText.setFont(*Font);
    ConfirmationText.setString("Are you sure you want to quit?\nUnsaved changes will be lost.");
    ConfirmationText.setCharacterSize(20);
    ConfirmationText.setPosition(20, 20);

    sf::Text YesText;
    YesText.setFont(*Font);
    YesText.setString("Yes");
    YesText.setCharacterSize(20);
    YesText.setPosition(80, 100);

    sf::Text NoText;
    NoText.setFont(*Font);
    NoText.setString("No");
    NoText.setCharacterSize(20);
    NoText.setPosition(180, 100);

    bool ShouldCloseApplication = false;

    while (ConfirmationWindow.isOpen())
    {
        sf::Event ConfirmEvent{};
        while (ConfirmationWindow.pollEvent(ConfirmEvent))
        {
            if (ConfirmEvent.type == sf::Event::Closed)
            {
                ConfirmationWindow.close();
            }
            else if (ConfirmEvent.type == sf::Event::MouseButtonPressed)
            {
                if (ConfirmEvent.mouseButton.button == sf::Mouse::Left)
                {
                    bool UserChoiceMade = false;
                    if (YesText.getGlobalBounds().contains(ConfirmEvent.mouseButton.x, ConfirmEvent.mouseButton.y))
                    {
                        ShouldCloseApplication = true;
                        UserChoiceMade = true;
                        ConfirmationWindow.close();
                    }
                    else if (NoText.getGlobalBounds().contains(ConfirmEvent.mouseButton.x, ConfirmEvent.mouseButton.y))
                    {
                        UserChoiceMade = true;
                        ConfirmationWindow.close();
                    }
                }
            }
        }

        ConfirmationWindow.clear();
        ConfirmationWindow.draw(ConfirmationText);
        ConfirmationWindow.draw(YesText);
        ConfirmationWindow.draw(NoText);
        ConfirmationWindow.display();
    }

    return ShouldCloseApplication;
}
