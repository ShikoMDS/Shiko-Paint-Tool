#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "GUI/UIElement.h"
#include "GUI/Camera.h"
#include "GUI/Menu.h"
#include "Utensils/ToolManager.h"
#include "Utensils/FileManager.h"

// ALWAYS BUILD IN RELEASE AT LEAST ONCE A DAY

int main()
{
    sf::Color ColourPickerColour;

    // Window renders ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //* Canvas window creation *//
    sf::RenderWindow CanvasWindow(sf::VideoMode(1600, 900), "Shiko Paint Tool");
    CanvasWindow.setFramerateLimit(60); // Sets to 60 fps

	FileManager g_FileManager(CanvasWindow.getSystemHandle());
    Camera MainCamera(sf::Vector2f(CanvasWindow.getSize().x / 2, CanvasWindow.getSize().y / 2), sf::Vector2f(CanvasWindow.getSize().x, CanvasWindow.getSize().y));
    //

	//* Colour Picker window creation *//
    sf::RenderWindow FillColourWindow(sf::VideoMode(395, 390), "Fill Colour", sf::Style::Titlebar);
    sf::RenderWindow OutlineColourWindow(sf::VideoMode(395, 390), "Outline Colour", sf::Style::Titlebar);
    FillColourWindow.setVerticalSyncEnabled(true);
    OutlineColourWindow.setVerticalSyncEnabled(true);

    sf::RectangleShape ColourShape;
    ColourShape.setSize(sf::Vector2f(FillColourWindow.getSize().x, FillColourWindow.getSize().y));
    ColourShape.setSize(sf::Vector2f(OutlineColourWindow.getSize().x, OutlineColourWindow.getSize().y));
    sf::Texture ColourTexture;
    ColourTexture.loadFromFile("Resources/Images/Colours.png");
    if (!ColourTexture.loadFromFile("Resources/Images/Colours.png"))
    {
        std::cout << "Failed to load colour selection tool!" << std::endl;
    }
    ColourShape.setTexture(&ColourTexture);
    sf::Image ColourPickerImage;
    ColourPickerImage.loadFromFile("Resources/Images/Colours.png");
    //
    

    //* Menu window creation *//
    sf::RenderWindow MenuWindow(sf::VideoMode(400, 900), "Menu", sf::Style::Close);
    MenuWindow.setVerticalSyncEnabled(true);
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    



    // Canvas stuff ---------------------------------------------------------------------------------------
    sf::RenderTexture* g_Canvas = new sf::RenderTexture();
    g_Canvas->create(CanvasWindow.getSize().x, CanvasWindow.getSize().y);
    g_Canvas->clear(sf::Color::White);

    sf::RectangleShape g_CanvasObject;
    g_CanvasObject.setSize(sf::Vector2f(CanvasWindow.getSize().x, CanvasWindow.getSize().y));
    g_CanvasObject.setTexture(&g_Canvas->getTexture());

    // Canvas manager init
    ToolManager g_CanvasManager(g_Canvas, &CanvasWindow);
    //

    // Delta time stuff
    sf::Time CurrentTime;
    sf::Clock DeltaClock;
    //----------------------------------------------------------------------------------------------------


    // Menu buttons ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    sf::Font* UIElementFont = new sf::Font;
    if (!UIElementFont->loadFromFile("Resources/Fonts/Inkfree.ttf"))
    {
        std::cout << "Error loading file" << std::endl;
    }
    
    std::vector <UIElement> UIElements;

    std::map<ButtonType, std::string> ToolNames = {
        {ButtonType::Pointer, "  Pointer "},
        {ButtonType::Box, "    Box "},
        {ButtonType::Ellipse, "   Ellipse "},
        {ButtonType::Line, "    Line "},
    };

    for (int i = 0; i < 4; i++)
    {
        UIElement NewElement(sf::Vector2f(20, 240 + (i * 55)), sf::Vector2f(140, 35), ToolNames[static_cast<ButtonType>(i)] + '(' + std::to_string(i + 1) + ')', UIElementFont, &g_CanvasManager);
        UIElements.push_back(NewElement);
        UIElements.back().CurrentButtonType = static_cast<ButtonType>(i);
        UIElements.at(0).IsActive = true;
    }

    std::vector<ButtonType>ButtonType = {
        ButtonType::Pointer,
        ButtonType::Box,
        ButtonType::Ellipse,
        ButtonType::Line,
    };
    
    for (int i = 0; i < UIElements.size(); i++)
    {
        UIElements.at(i).CurrentButtonType = ButtonType.at(i);
    }


    std::vector<UIElement> NumberButtons;

    std::map<NumButtons, std::string> Size = {
        {NumButtons::Number0, "  0"},
        {NumButtons::Number1, "  1"},
        {NumButtons::Number2, "  2"},
        {NumButtons::Number3, "  3"},
        {NumButtons::Number4, "  4"},
        {NumButtons::Number5, "  5"},
        {NumButtons::Number6, "  6"},
        {NumButtons::Number7, "  7"},
        {NumButtons::Number8, "  8"},
        {NumButtons::Number9, "  9"},
    };

    for (int i = 0; i <= 9; i++) 
    {
        UIElement SizeElement(sf::Vector2f(180, 70 + (i * 55)), sf::Vector2f(40, 40), Size[static_cast<NumButtons>(i)], UIElementFont, &g_CanvasManager);
    	NumberButtons.push_back(SizeElement);
        NumberButtons.back().CurrentSize = static_cast<NumButtons>(i);
        NumberButtons.at(0).IsActive = true;
    }


    std::vector<NumButtons>Button = 
    {
        NumButtons::Number0,
        NumButtons::Number1,
        NumButtons::Number2,
        NumButtons::Number3,
        NumButtons::Number4,
        NumButtons::Number5,
        NumButtons::Number6,
        NumButtons::Number7,
        NumButtons::Number8,
        NumButtons::Number9
    };

    for (int i = 0; i < NumberButtons.size(); i++)
    {
        NumberButtons.at(i).CurrentSize = Button.at(i);
    }

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    while (MenuWindow.isOpen())
    {
	    float DeltaTime = 0.0f;
	    CurrentTime = DeltaClock.restart();
        DeltaTime = CurrentTime.asSeconds();

        sf::Event CanvasEvent;
        while (CanvasWindow.pollEvent(CanvasEvent))
        {
            if (CanvasEvent.type == sf::Event::Closed)
            {
                if (showConfirmationDialog(CanvasWindow))
                {
                    CanvasWindow.close();
                    MenuWindow.close();
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
        }

        // Options window event loop
        sf::Event ColourEvent;
        while (FillColourWindow.pollEvent(ColourEvent))
        {
            // Colour selection fill
            if (ColourEvent.type == sf::Event::MouseButtonPressed)
            {
                if (ColourEvent.mouseButton.button == sf::Mouse::Left)
                {
                    ColourPickerColour = ColourPickerImage.getPixel(sf::Mouse::getPosition(FillColourWindow).x, sf::Mouse::getPosition(FillColourWindow).y);

                    g_CanvasManager.UpdateColourFill(ColourPickerColour);
                }
            }
        }

    	sf::Event OutlineEvent;
        while (OutlineColourWindow.pollEvent(OutlineEvent))
        {
            // Colour selection ouline
            if (OutlineEvent.type == sf::Event::MouseButtonPressed)
            {
                if (OutlineEvent.mouseButton.button == sf::Mouse::Left)
                {
                    ColourPickerColour = ColourPickerImage.getPixel(sf::Mouse::getPosition(OutlineColourWindow).x, sf::Mouse::getPosition(OutlineColourWindow).y);

                    g_CanvasManager.UpdateColourOutline(ColourPickerColour);
                }
            }
        }
        //


        // Menu window event loop
        sf::Event MenuEvent;
        while (MenuWindow.pollEvent(MenuEvent))
        {
            if (MenuEvent.type == sf::Event::Closed)
            {
                // Show confirmation dialog
                if (showConfirmationDialog(MenuWindow))
                {
                    MenuWindow.close();
                    CanvasWindow.close();
                }
            }
        }
        //

        MainCamera.CameraMove(CanvasWindow);
        
        // Set view
        CanvasWindow.setView(MainCamera.m_CameraView);


        // Main window render loop
        CanvasWindow.clear();

        g_CanvasManager.SwapTool();
        g_Canvas->display();

        CanvasWindow.draw(g_CanvasObject);

        g_CanvasManager.DrawUpdate();

        if (!g_CanvasManager.m_IsDrawing)
        {
            g_CanvasManager.ShapeCleanup();
        }
        
        CanvasWindow.display();
        //



        // Options window render loop
        FillColourWindow.clear(sf::Color::Black); // Sets window colour
        FillColourWindow.draw(ColourShape);
        FillColourWindow.display();


    	OutlineColourWindow.clear(sf::Color::Black); // Sets window colour
        OutlineColourWindow.draw(ColourShape);
        OutlineColourWindow.display();
        //



        // Menu window render loop
        MenuWindow.clear(sf::Color::Cyan); // Sets menu window color

        //Draw menu buttons
        for (int i = 0; i < UIElements.size(); i++)
        {
            UIElements[i].Draw(&MenuWindow);
        }

        for (int i = 0; i < NumberButtons.size(); i++)
        {
            NumberButtons[i].Draw(&MenuWindow);
        }
        
        if (MenuEvent.type == sf::Event::MouseButtonPressed)
        {
            if (MenuEvent.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < UIElements.size(); i++)
                {
                    if (UIElements[i].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                    {
                        for (int j = 0; j < UIElements.size(); j++)
                        {
                            UIElements.at(j).IsActive = false;
                        }

                        UIElements[i].ButtonReact();
                    }
                }
            }

            if (MenuEvent.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < NumberButtons.size(); i++)
                {
                    if (NumberButtons[i].m_ElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                    {
                        for (int j = 0; j < NumberButtons.size(); j++)
                        {
                            NumberButtons.at(j).IsActive = false;
                        }

                        NumberButtons[i].OutlineSizeButton();
                    }
                }
            }
        }
        // Menu buttons colour update
        for (int i = 0; i < UIElements.size(); i++)
        {

            if (UIElements.at(i).IsActive)
            {
                UIElements.at(i).m_ElementText.setFillColor(sf::Color::Red);
            }

            else
            {
                UIElements.at(i).m_ElementText.setFillColor(sf::Color::Black);
            }
        }

        for (int i = 0; i < NumberButtons.size(); i++)
        {

            if (NumberButtons.at(i).IsActive)
            {
                NumberButtons.at(i).m_ElementText.setFillColor(sf::Color::Red);
            }

            else
            {
                NumberButtons.at(i).m_ElementText.setFillColor(sf::Color::Black);
            }
        }

        sf::Text File;
        File.setFont(*UIElementFont);
        File.setFillColor(sf::Color::Black);
        File.setString("File:");
        File.setCharacterSize(40);
        File.setPosition(10, 5);

        sf::Text Save;
        Save.setFont(*UIElementFont);
        Save.setFillColor(sf::Color::Black);
        Save.setString("Save [F5]");
        Save.setCharacterSize(24);
        Save.setPosition(10, 60);

        sf::Text Load;
        Load.setFont(*UIElementFont);
        Load.setFillColor(sf::Color::Black);
        Load.setString("Load [F9]");
        Load.setCharacterSize(24);
        Load.setPosition(10, 100);

        if (MenuEvent.mouseButton.button == sf::Mouse::Left)
        {
            if (Save.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
            {
                // Saving
                g_Canvas->getTexture().copyToImage().saveToFile(g_FileManager.SaveFile() += ".png");
            }
        }

        if (MenuEvent.mouseButton.button == sf::Mouse::Left)
        {
            if (Load.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
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

    	sf::Text Tools;
        Tools.setFont(*UIElementFont);
        Tools.setFillColor(sf::Color::Black);
        Tools.setString("Tools:");
        Tools.setCharacterSize(40);
        Tools.setPosition(10, 175);

    	sf::Text Outline;
        Outline.setFont(*UIElementFont);
        Outline.setFillColor(sf::Color::Black);
        Outline.setString("Outline Size:");
        Outline.setCharacterSize(40);
        Outline.setPosition(180, 5);

        //65

        MenuWindow.draw(File);
        MenuWindow.draw(Save);
        MenuWindow.draw(Load);
        MenuWindow.draw(Tools);
        MenuWindow.draw(Outline);

        // Draw menu UI elements here
        
        MenuWindow.display();
        //
    }

    return 0;
}