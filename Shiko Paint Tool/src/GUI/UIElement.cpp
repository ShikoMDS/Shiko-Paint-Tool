/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : UIElement.cpp
Description : Implementations for UI features
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include <iostream>

#include  "GUI/UIElement.h"

#include "Utensils/ToolManager.h"

UiElement::UiElement(const sf::Vector2f Position, const sf::Vector2f Size, const std::string& Id, const sf::Font* FontRef, ToolManager* ToolManager)
{
	CurrentButtonType = ButtonType::Pointer;
	CurrentSize = NumButtons::Number0;

	IsActive = false;

	MElementVisual.setPosition(Position);
	MElementVisual.setSize(Size);
	MElementVisual.setFillColor(sf::Color::Magenta);\

	MElementText.setFont(*FontRef);
	MElementText.setFillColor(sf::Color::Yellow);
	MElementText.setPosition((MElementVisual.getPosition()));
	MElementText.setCharacterSize(24);

	MElementId = Id;
	MElementText.setString(MElementId);

	ToolManagerRef = ToolManager;
}

UiElement::~UiElement() = default;

void UiElement::buttonReact()
{
	ToolManagerRef->swapTool(CurrentButtonType);
	IsActive = IsActive ? false : true;
	std::cout << std::string(MElementText.getString()) << std::endl;
}

void UiElement::draw(sf::RenderWindow* Window) const
{
	// Draw visual before text or text will be behind layer
	Window->draw(MElementVisual);
	Window->draw(MElementText);
}

void UiElement::outlineSizeButton()
{
	ToolManagerRef->swapSize(CurrentSize);
	IsActive = IsActive ? false : true;
	std::cout << std::string(MElementText.getString()) << std::endl;
}

