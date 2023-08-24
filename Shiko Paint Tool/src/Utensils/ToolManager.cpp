/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : ToolManager.cpp
Description : Implementation of drawing tools
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include <cmath>

#include "Utensils/ToolManager.h"

ToolManager::ToolManager(sf::RenderTexture* CanvasRef, sf::RenderWindow* WindowRef)
{
    MCurrentTool = ToolNone;

	MCanvasRef = CanvasRef;
	MWindowRef = WindowRef;

	MLineThickness = 0.0f; // Default to 0
	MOutlineSize = 0.0f; // Default to 0

	// Default fill colour grey
	MCurrentShapeColour.r = 89;
	MCurrentShapeColour.g = 89;
	MCurrentShapeColour.b = 89;

	MCurrentRect.setFillColor(MCurrentShapeColour);
	MCurrentEllipse.setFillColor(MCurrentShapeColour);
	MCurrentLine.setFillColor(MCurrentShapeColour);

	MCurrentRect.setOutlineColor(sf::Color::Black);
	MCurrentEllipse.setOutlineColor(sf::Color::Black);
	MCurrentLine.setOutlineColor(sf::Color::Black);

	MCurrentRect.setOutlineThickness(MOutlineSize);
	MCurrentEllipse.setOutlineThickness(MOutlineSize);
	MCurrentLine.setOutlineThickness(MOutlineSize);
}

ToolManager::~ToolManager() = default;

void ToolManager::initShape(const ToolOptions CurrentTool)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        MMouseStartPos = MWindowRef->mapPixelToCoords(sf::Mouse::getPosition(*MWindowRef));

        switch (CurrentTool)
        {
        case ToolRect:
            MCurrentRect.setPosition(MMouseStartPos);
            MIsDrawing = true;
            break;
        case ToolEllipse:
            MCurrentEllipse.setPosition(MMouseStartPos);
            MIsDrawing = true;
            break;
        case ToolLine:
            MCurrentLine.setPosition(MMouseStartPos);
            MIsDrawing = true;
            break;
		case ToolNone: 
            break;
		default: 
            break;
        }
    }
}

void ToolManager::drawRect()
{
    MCurrentMousePosf = MWindowRef->mapPixelToCoords(sf::Mouse::getPosition(*MWindowRef));
    const sf::Vector2f Distance = -(MMouseStartPos - MCurrentMousePosf);

    MCurrentRect.setSize(Distance);

    MWindowRef->draw(MCurrentRect);
}

void ToolManager::drawEllipse()
{
    MCurrentMousePosf = MWindowRef->mapPixelToCoords(sf::Mouse::getPosition(*MWindowRef));
    const sf::Vector2f Distance = MCurrentMousePosf - MMouseStartPos;

    const float RadiusX = std::abs(Distance.x) / 2.0f;
    const float RadiusY = std::abs(Distance.y) / 2.0f;
    MCurrentEllipse.setRadius(RadiusX); // Set radius to half of X distance
    MCurrentEllipse.setScale(1.0f, RadiusY / RadiusX); // Scale the Y axis based on aspect ratio

    // Calculate the center of the ellipse based on origin and current mouse position
    const sf::Vector2f Center = MMouseStartPos + Distance / 2.0f;
    MCurrentEllipse.setPosition(Center - sf::Vector2f(RadiusX, RadiusY));

    MWindowRef->draw(MCurrentEllipse);
}

void ToolManager::drawLine()
{
    MCurrentMousePosf = MWindowRef->mapPixelToCoords(sf::Mouse::getPosition(*MWindowRef));

    const sf::Vector2f Distance = MCurrentMousePosf - MMouseStartPos;

    const float Length = std::sqrt(Distance.x * Distance.x + Distance.y * Distance.y);
    const float Angle = std::atan2(Distance.y, Distance.x) * 180.0f / static_cast<float>(std::acos(-1.0)); // Use std::acos(-1.0) for pi

    MCurrentLine.setSize(sf::Vector2f(Length, MLineThickness));
    MCurrentLine.setRotation(Angle);
    MCurrentLine.setPosition(MMouseStartPos);

    MWindowRef->draw(MCurrentLine);
}

void ToolManager::endDraw(const ToolOptions CurrentTool)
{
    if (MIsDrawing)
    {
        switch (CurrentTool)
        {
        case ToolRect:
            MCanvasRef->draw(MCurrentRect);
            break;
        case ToolEllipse:
            MCanvasRef->draw(MCurrentEllipse);
            break;
        case ToolLine: 
            MCanvasRef->draw(MCurrentLine);
            break;
        case ToolNone:
            break;
		default: 
            break;
        }

        MCanvasRef->display();
        MIsDrawing = false;
    }
}

void ToolManager::shapeCleanup()
{
    MCurrentRect.setSize(sf::Vector2f(0.0f, 0.0f));
    MCurrentRect.setPosition(-10000, -10000);
    MCurrentEllipse.setRadius(0.0f); // Reset ellipse radius
    MCurrentEllipse.setPosition(-10000, -10000);
    MCurrentLine.setSize(sf::Vector2f(0.0f, 0.0f));
    MCurrentLine.setPosition(-10000, -10000);
}

void ToolManager::drawUpdate()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        MIsDrawing = false;
    }

    switch (MCurrentTool)
    {
    case ToolNone:
        break;
    case ToolRect:
        if (MIsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            drawRect();
        }
        break;
    case ToolEllipse:
        if (MIsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            drawEllipse();
        }
        break;
    case ToolLine:
        if (MIsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            drawLine();
        }
        break;
    default:
        break;
    }
}

void ToolManager::swapTool(const ButtonType& TypeInput)
{
    if (TypeInput == ButtonType::Pointer)
    {
        MCurrentTool = ToolNone;
    }
    if (TypeInput == ButtonType::Box)
    {
        MCurrentTool = ToolRect;
    }
    if (TypeInput == ButtonType::Ellipse)
    {
        MCurrentTool = ToolEllipse;
    }
    if (TypeInput == ButtonType::Line)
    {
        MCurrentTool = ToolLine;
    }
}

void ToolManager::swapSize(const NumButtons& NumInput)
{
    if (NumInput == NumButtons::Number0)
    {
        MOutlineSize = 0;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number1)
    {
        MOutlineSize = 1;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number2)
    {
        MOutlineSize = 2;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number3)
    {
        MOutlineSize = 3;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number4)
    {
        MOutlineSize = 4;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number5)
    {
        MOutlineSize = 5;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number6)
    {
        MOutlineSize = 6;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number7)
    {
        MOutlineSize = 7;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number8)
    {
        MOutlineSize = 8;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number9)
    {
        MOutlineSize = 9;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number10)
    {
        MOutlineSize = 10;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number11)
    {
        MOutlineSize = 11;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number12)
    {
        MOutlineSize = 12;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number13)
    {
        MOutlineSize = 13;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number14)
    {
        MOutlineSize = 14;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number15)
    {
        MOutlineSize = 15;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number16)
    {
        MOutlineSize = 16;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number17)
    {
        MOutlineSize = 17;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number18)
    {
        MOutlineSize = 18;
        updateOutlineSize();
    }
    if (NumInput == NumButtons::Number19)
    {
        MOutlineSize = 19;
        updateOutlineSize();
    }
}


void ToolManager::updateColourFill(const sf::Color NewColour)
{
    MCurrentRect.setFillColor(NewColour);
    MCurrentEllipse.setFillColor(NewColour);
    MCurrentLine.setFillColor(NewColour);
}

void ToolManager::updateColourOutline(const sf::Color NewColour)
{
    MCurrentRect.setOutlineColor(NewColour);
    MCurrentEllipse.setOutlineColor(NewColour);
    MCurrentLine.setOutlineColor(NewColour);
}

void ToolManager::updateOutlineSize()
{
    MCurrentRect.setOutlineThickness(MOutlineSize);
    MCurrentEllipse.setOutlineThickness(MOutlineSize);
    MCurrentLine.setOutlineThickness(MOutlineSize);
}
