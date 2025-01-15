#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(int radius, float posX, float posY, sf::Color color);
	
	void Update();

	void Movement();
	void Collide();

	float GetPosX() { return m_posX; };
	float GetPosY() { return m_posY; };

	void SetSpeed(float value) { m_speedX = value, m_speedY = value; };
	void SetPosition(float x, float y) { m_shape.setPosition(x, y); };

	sf::CircleShape GetShape() { return m_shape; };

private:
	float m_speedX, m_speedY;
	float m_posX, m_posY;
	int m_radius;

	sf::CircleShape m_shape;
};

