/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : Camera.h
Description : Declarations for camera related functions
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include "SFML/Graphics.hpp"

class Camera
{
public:
	Camera(sf::Vector2f CameraPosition, sf::Vector2f CameraSize);
	~Camera();

	void cameraMove(const sf::RenderWindow& Window);

	sf::View MCameraView;
	sf::Vector2f MCameraSpeed;

private:
	bool MIsDragging{};
	sf::Vector2i MPreviousMousePos;
};