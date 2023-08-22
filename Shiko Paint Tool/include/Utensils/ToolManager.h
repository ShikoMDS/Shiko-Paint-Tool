#pragma once
#include <SFML/Graphics.hpp>

#include "GUI/UIElement.h"

enum ToolOptions
{
    Tool_None,
    Tool_Rect,
    Tool_Ellipse,
    Tool_Line,
};

class ToolManager
{
public:
    ToolManager(sf::RenderTexture* _CanvasRef, sf::RenderWindow* _WindowRef);
    ~ToolManager();

    void InitShape(ToolOptions currentTool);
    void DrawRect();
    void DrawEllipse();
    void DrawLine(); 
    void EndDraw(ToolOptions _CurrentTool);

    void ShapeCleanup();

    void DrawUpdate();
    void SwapTool();
    void SwapTool(ButtonType& _TypeInput);

    void UpdateColourFill(sf::Color _NewColour);
    void UpdateColourOutline(sf::Color _NewColour);
    void UpdateOutlineSize(float _Size);

    sf::Vector2f m_MouseStartPos;
    bool m_IsDrawing = false;

    sf::Color m_CurrentShapeColour;
    ToolOptions m_CurrentTool;

private:
    sf::RenderTexture* m_CanvasRef;
    sf::RenderWindow* m_WindowRef;

    sf::RectangleShape m_CurrentRect;
    sf::CircleShape m_CurrentEllipse;
    sf::RectangleShape m_CurrentLine;

    sf::Vector2f m_CurrentMousePosf;
    
    float m_LineThickness;
    float m_OutlineSize;
};
