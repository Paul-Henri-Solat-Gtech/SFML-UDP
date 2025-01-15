#include "pch.h"
#include "Ball.h"

Ball::Ball(int radius, float posX, float posY, sf::Color color) : m_posX(posX), m_posY(posY), m_radius(radius)
{
	m_shape.setRadius(radius);
	m_shape.setPosition(m_posX, m_posY);
	m_shape.setFillColor(color);
	m_shape.setOrigin(sf::Vector2f(radius, radius));

}

void Ball::Update()
{
	Movement();
	Collide();
}

void Ball::Movement() 
{
	m_posX += m_speedX;
	m_posY += m_speedY;
	
	m_shape.setPosition(m_posX, m_posY);
}

void Ball::Collide() 
{
	if (m_posX + m_radius >= 800 || m_posX - m_radius <= 0)
	{
		m_speedX *= -1;
	}
	if (m_posY + m_radius>= 600 || m_posY - m_radius <= 0)
	{
		m_speedY *= -1;
	}
}