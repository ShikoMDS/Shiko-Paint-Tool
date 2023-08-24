/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : Camera.cpp
Description : Implementations for camera functions
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "GUI/Camera.h"

Camera::Camera(const sf::Vector2f CameraPosition, const sf::Vector2f CameraSize)
{
	MCameraView.setCenter(CameraPosition);
	MCameraView.setSize(CameraSize);
}

Camera::~Camera() = default;

void Camera::cameraMove(const sf::RenderWindow& Window)
{
    MCameraSpeed = sf::Vector2f(0, 0);

    // Start dragging when the middle mouse button is pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !MIsDragging)
    {
        MIsDragging = true;
        MPreviousMousePos = sf::Mouse::getPosition(Window);
    }
    // Stop dragging when the middle mouse button is released
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        MIsDragging = false;
    }

    // Calculate camera movement based on mouse drag
    if (MIsDragging)
    {
	    const sf::Vector2i CurrentMousePos = sf::Mouse::getPosition(Window);
	    const sf::Vector2i MouseDelta = CurrentMousePos - MPreviousMousePos;

        MCameraSpeed = -static_cast<sf::Vector2f>(MouseDelta) * 1.0f; // Negative sign for inverted drag
        MPreviousMousePos = CurrentMousePos;
    }

    MCameraView.move(MCameraSpeed);
}