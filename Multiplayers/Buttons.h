#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
	std::unique_ptr<sf::RectangleShape> interactiveButton;
	Button(std::string namefile, sf::Vector2f& size, sf::Vector2f& posicion);
	bool buttonEvent(std::shared_ptr<sf::Event>& evento);
private:
	std::unique_ptr<sf::Texture> textureButton;
};
