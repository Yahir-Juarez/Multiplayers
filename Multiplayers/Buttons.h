#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
	Button();
	~Button();

	/// <summary>
	/// hola 2
	/// </summary>
	/// <param name="namefile"></param>
	/// <param name="size"></param>
	/// <param name="posicion"></param>
	void createButton(std::string namefile, sf::Vector2f& size, sf::Vector2f& posicion);

	void createButton(sf::Color colorShape, sf::Vector2f& size , sf::Vector2f& posicion);

	void createButton(std::string namefile, sf::Color colorFond, sf::Vector2f& size, sf::Vector2f& posicion);

	void setPositionButton(sf::Vector2f& posicion);

	void setSizeButton(sf::Vector2f& size);

	void setTextureButton(std::string& namefile);

	bool buttonEvent(sf::Event& evento);

	void render(sf::RenderWindow& windowDraw);

private:
	sf::RectangleShape interactiveButton;
	sf::Texture textureButton;
};
