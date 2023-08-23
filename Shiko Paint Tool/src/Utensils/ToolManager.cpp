#include "Utensils/ToolManager.h"
#include <cmath>

ToolManager::ToolManager(sf::RenderTexture* _CanvasRef, sf::RenderWindow* _WindowRef)
{
    m_CanvasRef = _CanvasRef;
    m_WindowRef = _WindowRef;

    m_LineThickness = 0.0f; // Set your desired line thickness
    m_OutlineSize = 0.0f; // Default to 0

    m_CurrentShapeColour.r = 89;
    m_CurrentShapeColour.g = 89;
    m_CurrentShapeColour.b = 89;

    m_CurrentRect.setFillColor(m_CurrentShapeColour);
    m_CurrentEllipse.setFillColor(m_CurrentShapeColour);
    m_CurrentLine.setFillColor(m_CurrentShapeColour); // Initialize line color

	m_CurrentRect.setOutlineColor(m_CurrentShapeColour);
    m_CurrentEllipse.setOutlineColor(m_CurrentShapeColour);
    m_CurrentLine.setOutlineColor(m_CurrentShapeColour); 

    m_CurrentRect.setOutlineThickness(m_OutlineSize);
    m_CurrentEllipse.setOutlineThickness(m_OutlineSize);
    m_CurrentLine.setOutlineThickness(m_OutlineSize);
    
}


ToolManager::~ToolManager()
{

}

void ToolManager::InitShape(ToolOptions currentTool)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_MouseStartPos = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));

        switch (currentTool)
        {
        case ToolOptions::Tool_Rect:
            m_CurrentRect.setPosition(m_MouseStartPos);
            m_IsDrawing = true;
            break;
        case ToolOptions::Tool_Ellipse:
            m_CurrentEllipse.setPosition(m_MouseStartPos);
            m_IsDrawing = true;
            break;
        case ToolOptions::Tool_Line:
            m_CurrentLine.setPosition(m_MouseStartPos);
            m_IsDrawing = true;
            break;
            // ... handle other tools
        }
    }
}

void ToolManager::DrawRect()
{
    m_CurrentMousePosf = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));
    sf::Vector2f Distance = -(m_MouseStartPos - m_CurrentMousePosf);

    m_CurrentRect.setSize(Distance);

    m_WindowRef->draw(m_CurrentRect);
}

void ToolManager::DrawEllipse()
{
    m_CurrentMousePosf = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));
    sf::Vector2f Distance = m_CurrentMousePosf - m_MouseStartPos;

    float radiusX = std::abs(Distance.x) / 2.0f;
    float radiusY = std::abs(Distance.y) / 2.0f;
    m_CurrentEllipse.setRadius(radiusX); // Set radius to half of X distance
    m_CurrentEllipse.setScale(1.0f, radiusY / radiusX); // Scale the Y axis based on aspect ratio

    // Calculate the center of the ellipse based on origin and current mouse position
    sf::Vector2f center = m_MouseStartPos + Distance / 2.0f;
    m_CurrentEllipse.setPosition(center - sf::Vector2f(radiusX, radiusY));

    m_WindowRef->draw(m_CurrentEllipse);
}

void ToolManager::DrawLine()
{
    m_CurrentMousePosf = m_WindowRef->mapPixelToCoords(sf::Mouse::getPosition(*m_WindowRef));

    sf::Vector2f distance = m_CurrentMousePosf - m_MouseStartPos;

    float length = std::sqrt(distance.x * distance.x + distance.y * distance.y);
    float angle = std::atan2(distance.y, distance.x) * 180.0f / static_cast<float>(std::acos(-1.0)); // Use std::acos(-1.0) for pi

    m_CurrentLine.setSize(sf::Vector2f(length, m_LineThickness));
    m_CurrentLine.setRotation(angle);
    m_CurrentLine.setPosition(m_MouseStartPos);

    m_WindowRef->draw(m_CurrentLine);
}

void ToolManager::EndDraw(ToolOptions _CurrentTool)
{
    if (m_IsDrawing)
    {
        switch (_CurrentTool)
        {
        case ToolOptions::Tool_Rect:
            m_CanvasRef->draw(m_CurrentRect);
            break;
        case ToolOptions::Tool_Ellipse:
            m_CanvasRef->draw(m_CurrentEllipse);
            break;
        case ToolOptions::Tool_Line: // Add this case
            m_CanvasRef->draw(m_CurrentLine);
            break;
            // ... handle other tools
        }

        m_CanvasRef->display();
        m_IsDrawing = false;
    }
}

void ToolManager::ShapeCleanup()
{
    m_CurrentRect.setSize(sf::Vector2f(0.0f, 0.0f));
    m_CurrentRect.setPosition(-10000, -10000);
    m_CurrentEllipse.setRadius(0.0f); // Reset ellipse radius
    m_CurrentEllipse.setPosition(-10000, -10000);
    m_CurrentLine.setSize(sf::Vector2f(0.0f, 0.0f));
    m_CurrentLine.setPosition(-10000, -10000);
}

void ToolManager::DrawUpdate()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        m_IsDrawing = false;
    }

    switch (m_CurrentTool)
    {
    case Tool_None:
        break;
    case Tool_Rect:
        if (m_IsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            DrawRect();
        }
        break;
    case Tool_Ellipse:
        if (m_IsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            DrawEllipse();
        }
        break;
    case Tool_Line:
        if (m_IsDrawing && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            DrawLine();
        }
        break;
    default:
        break;
    }
}

void ToolManager::SwapTool()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        m_CurrentTool = ToolOptions::Tool_None;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        m_CurrentTool = ToolOptions::Tool_Rect;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        m_CurrentTool = ToolOptions::Tool_Ellipse;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) 
    {
        m_CurrentTool = ToolOptions::Tool_Line;
    }
}

void ToolManager::SwapTool(ButtonType& _TypeInput)
{
    if (_TypeInput == ButtonType::Pointer)
    {
        m_CurrentTool = ToolOptions::Tool_None;
    }
    if (_TypeInput == ButtonType::Box)
    {
        m_CurrentTool = ToolOptions::Tool_Rect;
    }
    if (_TypeInput == ButtonType::Ellipse)
    {
        m_CurrentTool = ToolOptions::Tool_Ellipse;
    }
    if (_TypeInput == ButtonType::Line)
    {
        m_CurrentTool = ToolOptions::Tool_Line;
    }
}

void ToolManager::SwapSize(NumButtons& _NumInput)
{
    if (_NumInput == NumButtons::Number0)
    {
        m_OutlineSize = 0;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number1)
    {
        m_OutlineSize = 1;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number2)
    {
        m_OutlineSize = 2;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number3)
    {
        m_OutlineSize = 3;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number4)
    {
        m_OutlineSize = 4;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number5)
    {
        m_OutlineSize = 5;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number6)
    {
        m_OutlineSize = 6;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number7)
    {
        m_OutlineSize = 7;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number8)
    {
        m_OutlineSize = 8;
        UpdateOutlineSize();
    }
    if (_NumInput == NumButtons::Number9)
    {
        m_OutlineSize = 9;
        UpdateOutlineSize();
    }
}


void ToolManager::UpdateColourFill(sf::Color _NewColour)
{
    m_CurrentRect.setFillColor(_NewColour);
    m_CurrentEllipse.setFillColor(_NewColour);
    m_CurrentLine.setFillColor(_NewColour);
}

void ToolManager::UpdateColourOutline(sf::Color _NewColour)
{
    m_CurrentRect.setOutlineColor(_NewColour);
    m_CurrentEllipse.setOutlineColor(_NewColour);
    m_CurrentLine.setOutlineColor(_NewColour);
}

void ToolManager::UpdateOutlineSize()
{
    m_CurrentRect.setOutlineThickness(m_OutlineSize);
    m_CurrentEllipse.setOutlineThickness(m_OutlineSize);
    m_CurrentLine.setOutlineThickness(m_OutlineSize);
}


// 2 buttons to increase and decrease size, change value by 1 (clamp value 0-10)
