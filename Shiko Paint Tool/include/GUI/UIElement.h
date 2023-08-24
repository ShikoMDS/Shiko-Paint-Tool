/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : UIElement.h
Description : Declaration of UI related features
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

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
	Number9,
	Number10,
	Number11,
	Number12,
	Number13,
	Number14,
	Number15,
	Number16,
	Number17,
	Number18,
	Number19
};

class ToolManager;

class UiElement
{
public:
	UiElement(sf::Vector2f Position, sf::Vector2f Size, const std::string& Id, const sf::Font* FontRef, ToolManager* ToolManager);
	~UiElement();

	void buttonReact();
	void draw(sf::RenderWindow* Window) const;
	void outlineSizeButton();

	sf::RectangleShape MElementVisual;
	std::string MElementId;
	sf::Text MElementText;

	ButtonType CurrentButtonType;
	NumButtons CurrentSize;
	ToolManager* ToolManagerRef;
	bool IsActive;
};