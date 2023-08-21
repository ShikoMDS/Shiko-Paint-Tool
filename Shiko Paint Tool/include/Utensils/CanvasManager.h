#pragma once
#include <SFML/Graphics.hpp>

enum ToolOptions
{
    Tool_None,
    Tool_Rect,
    Tool_Ellipse,
    Tool_Line,
};

class CanvasManager
{
public:
    CanvasManager(sf::RenderTexture* _CanvasRef, sf::RenderWindow* _WindowRef);
    ~CanvasManager();

    void InitShape(ToolOptions currentTool);
    void DrawRect();
    void DrawEllipse();
    void DrawLine(); // Add this function
    void DrawBrush();
    void EndDraw(ToolOptions _CurrentTool);

    void ShapeCleanup();

    void DrawUpdate();
    void SwapTool();

    void UpdateColour(sf::Color _NewColour);

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

};
