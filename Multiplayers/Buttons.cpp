#include "Buttons.h"

Button::Button()
{

}

Button::~Button()
{

}

void Button::createButton(std::string namefile, sf::Vector2f& size, sf::Vector2f& posicion)
{
	setSizeButton(size);
	setPositionButton(posicion);
	setTextureButton(namefile);
}

void Button::setSizeButton(sf::Vector2f& size)
{
	interactiveButton.setSize(size);
}

void Button::setPositionButton(sf::Vector2f& posicion)
{
	interactiveButton.setPosition(posicion);
}

void Button::setTextureButton(std::string& namefile)
{
	sf::Vector2f center(interactiveButton.getGeometricCenter().x, interactiveButton.getGeometricCenter().y);
	interactiveButton.setOrigin(center);
	if (!textureButton.loadFromFile(namefile))
	{
		std::cout << "no se pudo cargar\n";
	}
	interactiveButton.setTexture(&textureButton);
}

void Button::render(sf::RenderWindow& windowDraw)
{
	windowDraw.draw(interactiveButton);
}

bool Button::buttonEvent(sf::Event& evento)
{

	if (evento.type == evento.MouseButtonPressed)
	{
		if (evento.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mouse_position(evento.mouseButton.x, evento.mouseButton.y);

			sf::Vector2f mouse_position_f(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
			if (interactiveButton.getGlobalBounds().contains(mouse_position_f))
			{
				return true;
			}
		}
	}
	return false;
}