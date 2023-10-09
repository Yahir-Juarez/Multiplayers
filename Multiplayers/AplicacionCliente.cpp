#include "AplicacionCliente.h"

App::App()
{
	Vector2u medidaVentana(window_x, window_y);
	ventana = std::make_shared<sf::RenderWindow>(VideoMode(medidaVentana), "Aplicacion Cliente");
	eventos = make_shared<Event>();

	/*
	if (!font.loadFromFile("arial.ttf")) {
		// Si no se puede cargar la fuente, muestra un error
	}

	
	Vector2f size(300, 350);
	text->setFont(font);
	text->setString("¡Hola, SFML!");
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::White);
	text->setPosition(size);
	*/

	mainloop();
}

App::~App()
{

}

void App::mainloop()
{
	while (ventana->isOpen())
	{
		entrada();
		update();
		render();
	}
}

void App::entrada()
{
	while (ventana->pollEvent(*eventos))
	{
		switch (eventos->type)
		{
		case Event::Closed:
			ventana->close();
			break;
		}
	}
}
void App::update()
{
	const unsigned short puerto = 50001;
	usuario.UdpClient(puerto);
}

void App::render()
{
	ventana->clear(Color::Black);
	//ventana->draw(*text);
	ventana->display();
}