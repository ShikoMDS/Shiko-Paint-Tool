/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : main.cpp
Description : Main entry for Shiko Paint Tool
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "GUI/UIElement.h"
#include "GUI/Camera.h"
#include "GUI/MenuOptions.h"

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

	FileManager GFileManager(CanvasWindow.getSystemHandle());
    Camera MainCamera(sf::Vector2f(CanvasWindow.getSize().x / 2, CanvasWindow.getSize().y / 2), sf::Vector2f(CanvasWindow.getSize().x, CanvasWindow.getSize().y));
    //

	//* Colour Picker window creation *//
    sf::RenderWindow FillColourWindow(sf::VideoMode(395, 390), "Fill Colour", sf::Style::Titlebar);
    sf::RenderWindow OutlineColourWindow(sf::VideoMode(395, 390), "Line Colour", sf::Style::Titlebar);
    FillColourWindow.setVerticalSyncEnabled(true);
    OutlineColourWindow.setVerticalSyncEnabled(true);

    sf::RectangleShape ColourShape;
    ColourShape.setSize(sf::Vector2f(FillColourWindow.getSize().x, FillColourWindow.getSize().y));
    ColourShape.setSize(sf::Vector2f(OutlineColourWindow.getSize().x, OutlineColourWindow.getSize().y));
    sf::Texture ColourTexture;
    ColourTexture.loadFromFile("resources/Images/Colours.png");
    if (!ColourTexture.loadFromFile("resources/Images/Colours.png"))
    {
        std::cout << "Failed to load colour selection tool!" << std::endl;
    }
    ColourShape.setTexture(&ColourTexture);
    sf::Image ColourPickerImage;
    ColourPickerImage.loadFromFile("resources/Images/Colours.png");
    //

    //* Menu window creation *//
    sf::RenderWindow MenuWindow(sf::VideoMode(375, 750), "Menu", sf::Style::Close);
    MenuWindow.setVerticalSyncEnabled(true);
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    


    // Canvas stuff ---------------------------------------------------------------------------------------
    sf::RenderTexture* GCanvas = new sf::RenderTexture();
    GCanvas->create(CanvasWindow.getSize().x, CanvasWindow.getSize().y);
    GCanvas->clear(sf::Color::White);

    sf::RectangleShape GCanvasObject;
    GCanvasObject.setSize(sf::Vector2f(CanvasWindow.getSize().x, CanvasWindow.getSize().y));
    GCanvasObject.setTexture(&GCanvas->getTexture());

    // Canvas manager init
    ToolManager GCanvasManager(GCanvas, &CanvasWindow);
    //

    // Delta time stuff
    sf::Time CurrentTime;
    sf::Clock DeltaClock;
    //----------------------------------------------------------------------------------------------------



    // Menu buttons ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    sf::Font* UiElementFont = new sf::Font;
    if (!UiElementFont->loadFromFile("resources/Fonts/Inkfree.ttf"))
    {
        std::cout << "Error loading file" << std::endl;
    }
    
    std::vector <UiElement> UiElements;

    std::map<ButtonType, std::string> ToolNames = {
        {ButtonType::Pointer, "\t Pointer"},
        {ButtonType::Box, "\t   Box"},
        {ButtonType::Ellipse, "\t Ellipse"},
        {ButtonType::Line, "\t   Line"},
    };

    for (int I = 0; I < 4; I++)
    {
        UiElement NewElement(sf::Vector2f(210, 65 + (I * 55)), sf::Vector2f(140, 35), ToolNames[static_cast<ButtonType>(I)], UiElementFont, &GCanvasManager);
        UiElements.push_back(NewElement);
        UiElements.back().CurrentButtonType = static_cast<ButtonType>(I);
        UiElements.at(0).IsActive = true;
    }

    std::vector<ButtonType>ButtonType = {
        ButtonType::Pointer,
        ButtonType::Box,
        ButtonType::Ellipse,
        ButtonType::Line,
    };
    
    for (int I = 0; I < UiElements.size(); I++)
    {
        UiElements.at(I).CurrentButtonType = ButtonType.at(I);
    }


    std::vector<UiElement> NumberButtons;

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

    for (int I = 0; I <= 9; I++) 
    {
        UiElement SizeElement(sf::Vector2f(30, 190 + (I * 55)), sf::Vector2f(40, 40), Size[static_cast<NumButtons>(I)], UiElementFont, &GCanvasManager);
    	NumberButtons.push_back(SizeElement);
        NumberButtons.back().CurrentSize = static_cast<NumButtons>(I);
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

    for (int I = 0; I < NumberButtons.size(); I++)
    {
        NumberButtons.at(I).CurrentSize = Button.at(I);
    }

    std::vector<UiElement> NumberButtons2;

    std::map<NumButtons, std::string> Size2 = {
        {NumButtons::Number0, " 10"},
        {NumButtons::Number1, " 11"},
        {NumButtons::Number2, " 12"},
        {NumButtons::Number3, " 13"},
        {NumButtons::Number4, " 14"},
        {NumButtons::Number5, " 15"},
        {NumButtons::Number6, " 16"},
        {NumButtons::Number7, " 17"},
        {NumButtons::Number8, " 18"},
        {NumButtons::Number9, " 19"},
    };

    for (int I = 0; I <= 9; I++)
    {
        UiElement SizeElement2(sf::Vector2f(100, 190 + (I * 55)), sf::Vector2f(40, 40), Size2[static_cast<NumButtons>(I)], UiElementFont, &GCanvasManager);
        NumberButtons.push_back(SizeElement2);
        NumberButtons.back().CurrentSize = static_cast<NumButtons>(I + 10);
    }


    std::vector<NumButtons>Button2 =
    {
        NumButtons::Number10,
        NumButtons::Number11,
        NumButtons::Number12,
        NumButtons::Number13,
        NumButtons::Number14,
        NumButtons::Number15,
        NumButtons::Number16,
        NumButtons::Number17,
        NumButtons::Number18,
        NumButtons::Number19
    };

    for (int I = 0; I < NumberButtons2.size(); I++)
    {
        NumberButtons2.at(I).CurrentSize = Button2.at(I);
    }


    // *Learn how to use arrays and vectors properly to not duplicate code and keep it concise*
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    while (MenuWindow.isOpen())
    {
	    float DeltaTime = 0.0f;
	    CurrentTime = DeltaClock.restart();
        DeltaTime = CurrentTime.asSeconds();

        sf::Event CanvasEvent{};
        while (CanvasWindow.pollEvent(CanvasEvent))
        {
            if (CanvasEvent.type == sf::Event::Closed)
            {
                if (showConfirmationDialog(CanvasWindow, UiElementFont))
                {
                    MenuWindow.close();
                    CanvasWindow.close();
                }
            }

            if (CanvasEvent.type == sf::Event::MouseWheelScrolled)
            {
                if (CanvasEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (CanvasEvent.mouseWheelScroll.delta < 0) // Scroll down to zoom out
                    {
                        MainCamera.MCameraView.zoom(1.1f); // Adjust this value to control zoom speed
                    }
                    else if (CanvasEvent.mouseWheelScroll.delta > 0) // Scroll up to zoom in
                    {
                        MainCamera.MCameraView.zoom(0.9f); // Adjust this value to control zoom speed
                    }
                }
            }

            if (CanvasEvent.type == sf::Event::MouseButtonPressed && CanvasEvent.mouseButton.button == sf::Mouse::Left)
            {
                GCanvasManager.initShape(GCanvasManager.MCurrentTool);
            }

            if (CanvasEvent.type == sf::Event::MouseButtonReleased && CanvasEvent.mouseButton.button == sf::Mouse::Left)
            {
                GCanvasManager.endDraw(GCanvasManager.MCurrentTool);
            }

            if (CanvasEvent.type == sf::Event::KeyPressed)
            {
	            if (CanvasEvent.key.code == sf::Keyboard::F5)
	            {
                    // Saving
                    std::cout << "Attempting to save..." << std::endl;
                    GCanvas->getTexture().copyToImage().saveToFile(GFileManager.saveFile() += ".png");
	            }

            	if (CanvasEvent.key.code == sf::Keyboard::F9)
	            {
                    // Loading
                    std::cout << "Attempting to load..." << std::endl;
                    sf::Texture NewTexture;
                    NewTexture.loadFromFile(GFileManager.openFile());

                    sf::RectangleShape NewShape;
                    NewShape.setSize(sf::Vector2f(NewTexture.getSize().x, NewTexture.getSize().y));
                    NewShape.setTexture(&NewTexture);

                    GCanvas->draw(NewShape);
	            }
            }
        }

        // Options window event loop
        sf::Event ColourEvent{};
        while (FillColourWindow.pollEvent(ColourEvent))
        {
            // Colour selection fill
            if (ColourEvent.type == sf::Event::MouseButtonPressed)
            {
                if (ColourEvent.mouseButton.button == sf::Mouse::Left)
                {
                    ColourPickerColour = ColourPickerImage.getPixel(sf::Mouse::getPosition(FillColourWindow).x, sf::Mouse::getPosition(FillColourWindow).y);

                    GCanvasManager.updateColourFill(ColourPickerColour);
                }
            }
        }

    	sf::Event OutlineEvent{};
        while (OutlineColourWindow.pollEvent(OutlineEvent))
        {
            // Colour selection ouline
            if (OutlineEvent.type == sf::Event::MouseButtonPressed)
            {
                if (OutlineEvent.mouseButton.button == sf::Mouse::Left)
                {
                    ColourPickerColour = ColourPickerImage.getPixel(sf::Mouse::getPosition(OutlineColourWindow).x, sf::Mouse::getPosition(OutlineColourWindow).y);

                    GCanvasManager.updateColourOutline(ColourPickerColour);
                }
            }
        }
        //


        sf::Text Save;
        Save.setFont(*UiElementFont);
        Save.setFillColor(sf::Color::Yellow);
        Save.setString("Save [F5]");
        Save.setCharacterSize(24);
        Save.setPosition(10, 60);

        sf::Text Load;
        Load.setFont(*UiElementFont);
        Load.setFillColor(sf::Color::Yellow);
        Load.setString("Load [F9]");
        Load.setCharacterSize(24);
        Load.setPosition(10, 100);

        // Menu window event loop
        sf::Event MenuEvent{};
        while (MenuWindow.pollEvent(MenuEvent))
        {
            if (MenuEvent.type == sf::Event::Closed)
            {
                if (showConfirmationDialog(MenuWindow, UiElementFont))
                {
                    MenuWindow.close();
                    CanvasWindow.close();
                }
            }

            if (MenuEvent.type == sf::Event::KeyPressed)
            {
                if (MenuEvent.key.code == sf::Keyboard::F5)
                {
                    // Saving
                    std::cout << "Attempting to save..." << std::endl;
                    GCanvas->getTexture().copyToImage().saveToFile(GFileManager.saveFile() += ".png");
                }

                if (MenuEvent.key.code == sf::Keyboard::F9)
                {
                    // Loading
                    std::cout << "Attempting to load..." << std::endl;
                    sf::Texture NewTexture;
                    NewTexture.loadFromFile(GFileManager.openFile());

                    sf::RectangleShape NewShape;
                    NewShape.setSize(sf::Vector2f(NewTexture.getSize().x, NewTexture.getSize().y));
                    NewShape.setTexture(&NewTexture);

                    GCanvas->draw(NewShape);
                }
            }

            if (MenuEvent.type == sf::Event::MouseButtonPressed)
            {
                if (MenuEvent.mouseButton.button == sf::Mouse::Left)
                {
                    for (int I = 0; I < UiElements.size(); I++)
                    {
                        if (UiElements[I].MElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                        {
                            for (auto& UiElement : UiElements)
                            {
                                UiElement.IsActive = false;
                            }

                            UiElements[I].buttonReact();
                        }
                    }
                }

                if (MenuEvent.mouseButton.button == sf::Mouse::Left)
                {
                    for (int I = 0; I < NumberButtons.size(); I++)
                    {
                        if (NumberButtons[I].MElementVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                        {
                            for (auto& NumberButton : NumberButtons)
                            {
                                NumberButton.IsActive = false;
                            }

                            NumberButtons[I].outlineSizeButton();
                        }
                    }
                }
            }

            if (MenuEvent.mouseButton.button == sf::Mouse::Left)
            {
                if (Save.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                {
                    // Saving
                    std::cout << "Attempting to save..." << std::endl;
                    GCanvas->getTexture().copyToImage().saveToFile(GFileManager.saveFile() += ".png");
                }
            }

            if (MenuEvent.mouseButton.button == sf::Mouse::Left)
            {
                if (Load.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(MenuWindow))))
                {
                    // Loading
                    std::cout << "Attempting to load..." << std::endl;
                    sf::Texture NewTexture;
                    NewTexture.loadFromFile(GFileManager.openFile());

                    sf::RectangleShape NewShape;
                    NewShape.setSize(sf::Vector2f(NewTexture.getSize().x, NewTexture.getSize().y));
                    NewShape.setTexture(&NewTexture);

                    GCanvas->draw(NewShape);
                }
            }
        }
        //

        MainCamera.cameraMove(CanvasWindow);
        
        // Set view
        CanvasWindow.setView(MainCamera.MCameraView);

        // Main window render loop
        CanvasWindow.clear();
        
        GCanvas->display();

        CanvasWindow.draw(GCanvasObject);

        GCanvasManager.drawUpdate();

        if (!GCanvasManager.MIsDrawing)
        {
            GCanvasManager.shapeCleanup();
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
        MenuWindow.clear(sf::Color::Black); // Sets menu window color

        //Draw menu buttons
        for (auto& UiElement : UiElements)
        {
	        UiElement.draw(&MenuWindow);
        }

        for (auto& NumberButton : NumberButtons)
        {
	        NumberButton.draw(&MenuWindow);
        }

        // Menu buttons colour update
        for (auto& UiElement : UiElements)
        {

            if (UiElement.IsActive)
            {
	            UiElement.MElementText.setFillColor(sf::Color::Cyan);
            }

            else
            {
	            UiElement.MElementText.setFillColor(sf::Color::Yellow);
            }
        }

        for (auto& NumberButton : NumberButtons)
        {

            if (NumberButton.IsActive)
            {
	            NumberButton.MElementText.setFillColor(sf::Color::Cyan);
            }

            else
            {
	            NumberButton.MElementText.setFillColor(sf::Color::Yellow);
            }
        }

        sf::Text File;
        File.setFont(*UiElementFont);
        File.setFillColor(sf::Color::Cyan);
        File.setString("File:");
        File.setCharacterSize(40);
        File.setPosition(10, 5);

    	sf::Text Tools;
        Tools.setFont(*UiElementFont);
        Tools.setFillColor(sf::Color::Cyan);
        Tools.setString("Tools:");
        Tools.setCharacterSize(40);
        Tools.setPosition(200, 5);

    	sf::Text Outline;
        Outline.setFont(*UiElementFont);
        Outline.setFillColor(sf::Color::Cyan);
        Outline.setString("Line Size:");
        Outline.setCharacterSize(40);
        Outline.setPosition(10, 135);

        sf::Text Draw;
        Draw.setFont(*UiElementFont);
        Draw.setFillColor(sf::Color::Cyan);
        Draw.setString("Draw:");
        Draw.setCharacterSize(40);
        Draw.setPosition(200, 270);

        sf::Text DrawControl;
        DrawControl.setFont(*UiElementFont);
        DrawControl.setFillColor(sf::Color::Magenta);
        DrawControl.setString("\t[MB1]\n- Click and drag\nto draw\n\t[MB2]\n- Click to cancel\ndraw");
        DrawControl.setCharacterSize(24);
        DrawControl.setPosition(200, 315);

        sf::Text Camera;
        Camera.setFont(*UiElementFont);
        Camera.setFillColor(sf::Color::Cyan);
        Camera.setString("Camera:");
        Camera.setCharacterSize(40);
        Camera.setPosition(200, 490);

        sf::Text Controls;
        Controls.setFont(*UiElementFont);
        Controls.setFillColor(sf::Color::Magenta);
        Controls.setString("\t[MB3]\n- Scroll to zoom\n- Click and drag\nto move camera\nview");
        Controls.setCharacterSize(24);
        Controls.setPosition(200, 535);

        sf::Text Credits;
        Credits.setFont(*UiElementFont);
        Credits.setFillColor(sf::Color::Cyan);
        Credits.setString("Shikomisen (2023)");
        Credits.setCharacterSize(24);
        Credits.setPosition(160, 700);

        MenuWindow.draw(File);
        MenuWindow.draw(Save);
        MenuWindow.draw(Load);
        MenuWindow.draw(Tools);
        MenuWindow.draw(Outline);
        MenuWindow.draw(Draw);
        MenuWindow.draw(DrawControl);
        MenuWindow.draw(Camera);
        MenuWindow.draw(Controls);
        MenuWindow.draw(Credits);

        // *Next time make a text function for less lines*
        
        MenuWindow.display();
        //
    }

    return 0;
}