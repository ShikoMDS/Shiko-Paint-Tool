/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : ToolManager.h
Description : Declaration of drawing tools
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>

#include "GUI/UIElement.h"

enum ToolOptions
{
    ToolNone,
    ToolRect,
    ToolEllipse,
    ToolLine,
};

class ToolManager
{
public:
    ToolManager(sf::RenderTexture* CanvasRef, sf::RenderWindow* WindowRef);
    ~ToolManager();

    void initShape(ToolOptions CurrentTool);
    void drawRect();
    void drawEllipse();
    void drawLine(); 
    void endDraw(ToolOptions CurrentTool);

    void shapeCleanup();
    void drawUpdate();

    void swapTool(const ButtonType& TypeInput);
    void swapSize(const NumButtons& NumInput);

    void updateColourFill(sf::Color NewColour);
    void updateColourOutline(sf::Color NewColour);
    void updateOutlineSize();

    sf::Vector2f MMouseStartPos;
    bool MIsDrawing = false;

    sf::Color MCurrentShapeColour;
    ToolOptions MCurrentTool;

private:
    sf::RenderTexture* MCanvasRef;
    sf::RenderWindow* MWindowRef;

    sf::RectangleShape MCurrentRect;
    sf::CircleShape MCurrentEllipse;
    sf::RectangleShape MCurrentLine;

    sf::Vector2f MCurrentMousePosf;
    
    float MLineThickness;
    float MOutlineSize;
};
