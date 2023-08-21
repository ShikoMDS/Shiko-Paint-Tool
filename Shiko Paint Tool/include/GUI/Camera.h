#pragma once
#include "SFML/Graphics.hpp"

class Camera
{
public:
	sf::View m_CameraView;
	sf::Vector2f m_CameraSpeed;

	Camera(sf::Vector2f _CameraPosition, sf::Vector2f _CameraSize);
	~Camera();

	void CameraMove(sf::RenderWindow& _Window);

private:
	bool m_IsDragging;
	sf::Vector2i m_PreviousMousePos;
};