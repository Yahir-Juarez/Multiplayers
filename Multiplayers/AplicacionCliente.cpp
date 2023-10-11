#include "AplicacionCliente.h"

App::App()
{
	Vector2u medidaVentana(window_x, window_y);
	ventana = std::make_shared<sf::RenderWindow>(VideoMode(medidaVentana), "Aplicacion Cliente");
	eventos = make_shared<Event>();

	relojTeclado = make_shared<Clock>();
	Vector2f posicion(window_x/2, window_y/2);
	Vector2f size(300, 300);
	inicioSesion = make_unique<Button>("Textures/InicioSesion.png", size, posicion);

	relojButtons = make_shared<Clock>();
	Vector2f posicionTeclado(window_x - 75, window_y - 50);
	Vector2f sizeTeclado(100, 50);
	keyboardOn = make_unique<Button>("Textures/TecladoEncendido.png", sizeTeclado, posicionTeclado);
	keyboardOff = make_unique<Button>("Textures/TecladoApagado.png", sizeTeclado, posicionTeclado);
	
	
	//unsigned int characterSize = 30;
	//font = make_shared<Font>();
	//text = make_shared<Text>();
	/*
	if (!font->loadFromFile("ASMAN.ttf")) {
		// Si no se puede cargar la fuente, muestra un error
	}

	
	text->setFont(*font);
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
	buttonPressed();
	teclado();
}

void App::buttonPressed()
{
	Time tiempo;
	tiempo = relojButtons->getElapsedTime();
	float tiempoButtons = tiempo.asSeconds();

	if (tiempoButtons > .5)
	{
		if (inicioSesion->buttonEvent(eventos))
		{
			if (usuario.conexion() == true)
			{
				estado = InicioUser;
			}
			else
			{
				cout << "No se pudo conectar al servidor" << endl;
			}
			relojButtons->restart();
		}
		if (keyboardOn->buttonEvent(eventos) && tecladoActivo == true)
		{
			tecladoActivo = false;
			relojButtons->restart();
		}
		else if (keyboardOff->buttonEvent(eventos) && tecladoActivo == false)
		{
			tecladoActivo = true;
			relojButtons->restart();
		}
	}
}

void App::update()
{
	const unsigned short puerto = 50001;
	//usuario.UdpClient(puerto);
}

void App::render()
{
	Color rgb(184, 184, 184);
	ventana->clear(Color(rgb));
	if (estado == Inicio)
	{
		ventana->draw(*inicioSesion->interactiveButton);
	}
	else if (estado == InicioUser)
	{
		if (tecladoActivo == true)
		{
			ventana->draw(*keyboardOn->interactiveButton);
		}
		else
		{
			ventana->draw(*keyboardOff->interactiveButton);
		}
	}
	//ventana->draw(*text);
	ventana->display();
}

void App::teclado()
{

	if (tecladoActivo == true)
	{
		Time tiempo;
		tiempo = relojTeclado->getElapsedTime();
		float tiempoTecla = tiempo.asSeconds();
		if (tiempoTecla > .18)
		{
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				entradaString += "Q";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::W))
			{
				entradaString += "W";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::E))
			{
				entradaString += "E";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::R))
			{
				entradaString += "R";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::T))
			{
				entradaString += "T";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Y))
			{
				entradaString += "Y";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::U))
			{
				entradaString += "U";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::I))
			{
				entradaString += "I";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::O))
			{
				entradaString += "O";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::P))
			{
				entradaString += "P";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				entradaString += "A";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				entradaString += "S";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				entradaString += "D";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::F))
			{
				entradaString += "F";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::G))
			{
				entradaString += "G";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::H))
			{
				entradaString += "H";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::J))
			{
				entradaString += "J";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::K))
			{
				entradaString += "K";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::L))
			{
				entradaString += "L";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Z))
			{
				entradaString += "Z";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::X))
			{
				entradaString += "X";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::C))
			{
				entradaString += "C";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::V))
			{
				entradaString += "V";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::B))
			{
				entradaString += "B";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::N))
			{
				entradaString += "N";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::M))
			{
				entradaString += "M";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				entradaString += " ";
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Backspace))
			{
				entradaString.pop_back();
				relojTeclado->restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				usuario.usuario(entradaString.c_str());
				cout << entradaString << "\n";
				entradaString.clear();
				relojTeclado->restart();
			}
		}
	}
}