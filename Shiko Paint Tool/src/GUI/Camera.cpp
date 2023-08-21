#include "GUI/Camera.h"

Camera::Camera(sf::Vector2f _CameraPosition, sf::Vector2f _CameraSize)
{
	m_CameraView.setCenter(_CameraPosition);
	m_CameraView.setSize(_CameraSize);
}

Camera::~Camera()
{

}

void Camera::CameraMove(sf::RenderWindow& window)
{
    m_CameraSpeed = sf::Vector2f(0, 0);

    // Start dragging when the middle mouse button is pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !m_IsDragging)
    {
        m_IsDragging = true;
        m_PreviousMousePos = sf::Mouse::getPosition(window);
    }
    // Stop dragging when the middle mouse button is released
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        m_IsDragging = false;
    }

    // Calculate camera movement based on mouse drag
    if (m_IsDragging)
    {
        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
        sf::Vector2i mouseDelta = currentMousePos - m_PreviousMousePos;

        m_CameraSpeed = -static_cast<sf::Vector2f>(mouseDelta) * 1.0f; // Notice the negative sign for inverted drag
        m_PreviousMousePos = currentMousePos;
    }

    m_CameraView.move(m_CameraSpeed);
}