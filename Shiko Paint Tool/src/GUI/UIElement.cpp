#include  "GUI/UIElement.h"
#include <iostream>
#include "Utensils/ToolManager.h"


UIElement::UIElement(sf::Vector2f _Position, sf::Vector2f _Size, std::string _ID, sf::Font* _FontRef, ToolManager* _ToolManager)
{
	IsActive = false;

	m_ElementVisual.setPosition(_Position);
	m_ElementVisual.setSize(_Size);
	m_ElementVisual.setFillColor(sf::Color::White);\

	m_ElementText.setFont(*_FontRef);
	m_ElementText.setFillColor(sf::Color::Black);
	m_ElementText.setPosition((m_ElementVisual.getPosition()));
	m_ElementText.setCharacterSize(24);

	m_ElementID = _ID;
	m_ElementText.setString(m_ElementID);

	ToolManagerRef = _ToolManager;
}

UIElement::~UIElement()
{

}

void UIElement::ButtonReact()
{
	ToolManagerRef->SwapTool(CurrentButtonType);
	IsActive = IsActive ? false : true;
	std::cout << std::string(m_ElementText.getString()) << std::endl;
}

void UIElement::Draw(sf::RenderWindow* _Window)
{
	// Draw visual before text or text will be behind layer
	_Window->draw(m_ElementVisual);
	_Window->draw(m_ElementText);
}

void UIElement::OutlineSizeButton(float& outlineSize)
{
	if (IsActive) 
	{
		outlineSize = static_cast<float>(CurrentButtonType);
	}
	else 
	{
		outlineSize = 0.0f;
	}
	std::cout << std::string(m_ElementText.getString()) << std::endl;
}

