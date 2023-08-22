#pragma once

#include "SFML/Graphics.hpp"

enum class ButtonType
{
	Pointer,
	Box,
	Ellipse,
	Line
};

class ToolManager;

class UIElement
{
public:
	sf::RectangleShape m_ElementVisual;
	std::string m_ElementID;

	sf::Text m_ElementText;

	UIElement(sf::Vector2f _Position, sf::Vector2f _Size, std::string _ID, sf::Font* _FontRef, ToolManager* _ToolManager);
	~UIElement();

	void ButtonReact();
	void Draw(sf::RenderWindow* _Window);

	void OutlineSizeButton(float& outlineSize);

	ButtonType CurrentButtonType;
	ToolManager* ToolManagerRef;
	bool IsActive;
};