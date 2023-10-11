#include "Buttons.h"

Button::Button(std::string namefile, sf::Vector2f& size, sf::Vector2f& posicion)
{
	interactiveButton = std::make_unique<sf::RectangleShape>(size);
	textureButton = std::make_unique < sf::Texture>();
	textureButton->loadFromFile(namefile);
	interactiveButton->setTexture(textureButton.get());
	sf::Vector2f center(interactiveButton->getGeometricCenter().x , interactiveButton->getGeometricCenter().y);
	interactiveButton->setOrigin(center);
	interactiveButton->setPosition(posicion);
}

bool Button::buttonEvent(std::shared_ptr<sf::Event>& evento)
{

	if (evento->type == evento->MouseButtonPressed)
	{
		if (evento->mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mouse_position(evento->mouseButton.x, evento->mouseButton.y);

			sf::Vector2f mouse_position_f(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
			if (interactiveButton->getGlobalBounds().contains(mouse_position_f))
			{
				return true;
			}
		}
	}
	return false;
}