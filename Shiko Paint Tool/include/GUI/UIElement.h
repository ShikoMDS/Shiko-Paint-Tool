#pragma once

#include "SFML/Graphics.hpp"

enum class ButtonType
{
	Pointer,
	Box,
	Ellipse,
	Line
};

enum class NumButtons
{
	Number0,
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Number8,
	Number9
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

	void OutlineSizeButton();

	ButtonType CurrentButtonType;
	NumButtons CurrentSize;
	ToolManager* ToolManagerRef;
	bool IsActive;
};