#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "GUI/UIElement.h"
#include "GUI/Camera.h"
#include "GUI/Menu.h"
#include "Utensils/CanvasManager.h"
#include "Utensils/FileManager.h"

// ALWAYS BUILD IN RELEASE AT LEAST ONCE A DAY

int main()
{
    sf::Color ColourPickerColour;

    // Main window creation
    sf::RenderWindow MainRenderWindow(sf::VideoMode(1600, 900), "Shiko Paint Tool");
    MainRenderWindow.setFramerateLimit(60); // Sets to 60 fps

	FileManager g_FileManager(MainRenderWindow.getSystemHandle());

	// Colour Picker window creation
    sf::RenderWindow ColourPickerWindow(sf::VideoMode(400, 400), "Colour Picker");
    ColourPickerWindow.setVerticalSyncEnabled(true); // Sets to monitor refresh rate

    sf::RectangleShape OptionsShape;
    OptionsShape.setSize(sf::Vector2f(ColourPickerWindow.getSize().x, ColourPickerWindow.getSize().y));
    sf::Texture OptionsTexture;
    OptionsTexture.loadFromFile("Resources/Images/Colours.png");
    if (!OptionsTexture.loadFromFile("Resources/Images/Colours.png"))
    {
        std::cout << "Failed to load colour selection tool!" << std::endl;
    }

    OptionsShape.setTexture(&OptionsTexture);

    sf::Image ColourPickerImage;
    ColourPickerImage.loadFromFile("Resources/Images/Colours.png");
    //

    // Menu window creation
    sf::RenderWindow MenuRenderWindow(sf::VideoMode(400, 900), "Menu");
    MenuRenderWindow.setVerticalSyncEnabled(true);
    //
    


    Camera MainCamera(sf::Vector2f(MainRenderWindow.getSize().x / 2, MainRenderWindow.getSize().y / 2), sf::Vector2f(MainRenderWindow.getSize().x, MainRenderWindow.getSize().y));

    // Canvas stuff
    sf::RenderTexture* g_Canvas = new sf::RenderTexture();
    g_Canvas->create(MainRenderWindow.getSize().x, MainRenderWindow.getSize().y);
    g_Canvas->clear(sf::Color::White);

    sf::RectangleShape g_CanvasObject;
    g_CanvasObject.setSize(sf::Vector2f(MainRenderWindow.getSize().x, MainRenderWindow.getSize().y));
    g_CanvasObject.setTexture(&g_Canvas->getTexture());
    //

    // Canvas manager init
    CanvasManager g_CanvasManager(g_Canvas, &MainRenderWindow);
    //

    // Delta time stuff
    float DeltaTime = 0.0f;
    sf::Time CurrentTime;
    sf::Clock DeltaClock;

    //

    sf::Font* UIElementFont = new sf::Font;
    if (!UIElementFont->loadFromFile("Resources/Fonts/Inkfree.ttf"))
    {
        std::cout << "Error loading file" << std::endl;
    }

    std::vector <UIElement> UIElements;

    while (MenuRenderWindow.isOpen())
    {
        CurrentTime = DeltaClock.restart();
        DeltaTime = CurrentTime.asSeconds();

        sf::Event CanvasEvent;
        while (MainRenderWindow.pollEvent(CanvasEvent))
        {
            if (CanvasEvent.type == sf::Event::Closed)
            {
                MainRenderWindow.close();
            }

            if (CanvasEvent.type == sf::Event::MouseButtonPressed && CanvasEvent.mouseButton.button == sf::Mouse::Left)
            {
                g_CanvasManager.InitShape(g_CanvasManager.m_CurrentTool);
            }

            if (CanvasEvent.type == sf::Event::MouseButtonReleased && CanvasEvent.mouseButton.button == sf::Mouse::Left)
            {
                g_CanvasManager.EndDraw(g_CanvasManager.m_CurrentTool);
            }

            if (CanvasEvent.type == sf::Event::KeyPressed)
            {
	            if (CanvasEvent.key.code == sf::Keyboard::F5)
	            {
                    // Saving
                    g_Canvas->getTexture().copyToImage().saveToFile(g_FileManager.SaveFile() += ".png");
	            }

            	if (CanvasEvent.key.code == sf::Keyboard::F9)
	            {
                    // Loading
                    sf::Texture NewTexture;
                    NewTexture.loadFromFile(g_FileManager.OpenFile());

                    sf::RectangleShape NewShape;
                    NewShape.setSize(sf::Vector2f(NewTexture.getSize().x, NewTexture.getSize().y));
                    NewShape.setTexture(&NewTexture);

                    g_Canvas->draw(NewShape);
	            }
            }

            if (CanvasEvent.type == sf::Event::MouseWheelScrolled)
            {
                if (CanvasEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (CanvasEvent.mouseWheelScroll.delta < 0) // Scroll down to zoom out
                    {
                        MainCamera.m_CameraView.zoom(1.1f); // Adjust this value to control zoom speed
                    }
                    else if (CanvasEvent.mouseWheelScroll.delta > 0) // Scroll up to zoom in
                    {
                        MainCamera.m_CameraView.zoom(0.9f); // Adjust this value to control zoom speed
                    }
                }
            }
        }

        // Menu window event loop
        sf::Event MenuEvent;
        while (MenuRenderWindow.pollEvent(MenuEvent))
        {
            if (MenuEvent.type == sf::Event::Closed)
            {
                // Show confirmation dialog
                if (showConfirmationDialog(MenuRenderWindow)) // Call the function without any namespace prefix
                {
                    MenuRenderWindow.close();
                }
            }
        }
        //

        MainCamera.CameraMove(MainRenderWindow);
        
        // Set view
        MainRenderWindow.setView(MainCamera.m_CameraView);


        // Main window render loop
        MainRenderWindow.clear();

        g_CanvasManager.SwapTool();
        g_Canvas->display();

        MainRenderWindow.draw(g_CanvasObject);

        g_CanvasManager.DrawUpdate();

        if (!g_CanvasManager.m_IsDrawing)
        {
            g_CanvasManager.ShapeCleanup();
        }
        
        MainRenderWindow.display();
        //



        // Options window render loop
        ColourPickerWindow.clear(sf::Color::Blue); // Sets window colour

        // for (int i = 0; i < UIElements.size(); i++)
        // {
        //     UIElements[i].Draw(&OptionsWindow);
        // }


        ColourPickerWindow.draw(OptionsShape);

        ColourPickerWindow.display();
        //



        // Menu window render loop
        MenuRenderWindow.clear(sf::Color::Cyan); // Sets menu window color

        // Draw your menu UI elements here
        // ...

        MenuRenderWindow.display();
        //
    }

    return 0;
}