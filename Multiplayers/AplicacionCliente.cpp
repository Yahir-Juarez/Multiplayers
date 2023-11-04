#include "AplicacionCliente.h"

App::App()
{
	Vector2u medidaVentana(window_x, window_y);
	ventana.create(VideoMode(medidaVentana), "Aplicacion Cliente");

	Vector2f posicionInicio(window_x / 2, window_y / 2);
	Vector2f sizeInicio(300, 300);
	inicioSesion.createButton("Textures/InicioSesion.png", sizeInicio, posicionInicio);

	Vector2f posicionTeclado(window_x - 75, window_y - 50);
	Vector2f sizeTeclado(100, 50);
	keyboardOn.createButton("Textures/TecladoEncendido.png", sizeTeclado, posicionTeclado);
	keyboardOff.createButton("Textures/TecladoApagado.png", sizeTeclado, posicionTeclado);

	mainloop();
}

App::~App()
{

}

void App::mainloop()
{
	while (ventana.isOpen())
	{
		entrada();
		update();
		render();
	}
}

void App::entrada()
{
	while (ventana.pollEvent(eventos))
	{
		switch (eventos.type)
		{
		case Event::Closed:
			ventana.close();
			break;
		}
	}
	if (activeKeyBoard == true)
	{
		interactiveKeyBord.inputKeyBoard(actualKeyboard, usuario);
	}
	buttonPressed(); 
	if (usuario.enuEstado == Aplicacion)
	{
		typesShapes();
		createShapes();
	}
}

void App::typesShapes()
{
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		colorShapes = Color::Black;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		colorShapes = Color::Magenta;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		colorShapes = Color::Red;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		colorShapes = Color::Blue;
	}
	
	else if (Keyboard::isKeyPressed(Keyboard::Num6))
	{
		stateShape = Rectangle;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num7))
	{
		stateShape = Circle;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num8))
	{
		stateShape = Line;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num9))
	{
		stateShape = FreeStroke;
	}
}

float DistanciaEntreDosPuntos(Vector2f& inicial, Vector2f & final)
{
	float distancia = ((pow((inicial.x - final.x), 2)) + (pow((inicial.y - final.y), 2)));
	distancia = sqrt(distancia);
	return distancia;
}

void App::createShapes()
{
	if (eventos.mouseButton.button == sf::Mouse::Left && bTemporalPositionMouse == false)
	{
		posInicial = sf::Vector2f(eventos.mouseButton.x, eventos.mouseButton.y);
		posFinal = posInicial;
		bTemporalPositionMouse = true;
		temporalShapes.fillCurrentShapeData(colorShapes, eventos);
		MsgMouseData posicion;
		posicion.fillCurrentMouseData();
		posicion.m_msgData;
	}
	else if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		// Deja de arrastrar el punto y crea el rect�ngulo
		bTemporalPositionMouse = false;
		temporalShapes.fillCurrentShapeDataFinal(eventos);
		cout << "si";
		auto connect = temporalShapes.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		usuario.usuario(finalPackage);
	}
	else if (eventos.type == sf::Event::MouseMoved)
	{
		// Actualiza la posici�n final del punto mientras se arrastra
		if (bTemporalPositionMouse)
		{
			posFinal = sf::Vector2f(eventos.mouseMove.x, eventos.mouseMove.y);
		}
	}
}

void App::buttonPressed()
{
	Time tiempo;
	tiempo = relojButtons.getElapsedTime();
	float tiempoButtons = tiempo.asSeconds();

	if (tiempoButtons > .5)
	{
		if (inicioSesion.buttonEvent(eventos))
		{
			usuario.conexion();
			relojButtons.restart();
		}
		if (keyboardOn.buttonEvent(eventos) && activeKeyBoard == true)
		{
			activeKeyBoard = false;
			relojButtons.restart();
		}
		else if (keyboardOff.buttonEvent(eventos) && activeKeyBoard == false)
		{
			activeKeyBoard = true;
			relojButtons.restart();
		}
	}
}

void App::update()
{
	usuario.UdpClient();
}

void App::render()
{
	Color rgbGris(184, 184, 184);
	if (usuario.enuEstado == Inicio)
	{
		ventana.clear(Color(rgbGris));
		inicioSesion.render(ventana);
	}
	else if (usuario.enuEstado == InicioUser)
	{
		ventana.clear(Color(rgbGris));
		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, window_x / (10/3), window_y / (10/4));
		}
		else
		{
			keyboardOff.render(ventana);
		}
	}
	else if (usuario.enuEstado == InicioPassword)
	{
		ventana.clear(Color(rgbGris));
		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, window_x / (10 / 3), window_y / (10 / 4));
		}
		else
		{
			keyboardOff.render(ventana);
		}
	}
	else if (usuario.enuEstado == Aplicacion)
	{
		ventana.clear(Color::White);
		/*
		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, window_x / (10 / 3), window_y / (10 / 4));
		}
		else
		{
			keyboardOff.render(ventana);
		}
		*/
		for (int i = 0; i < usuario.shapesTypes.size(); i++)
		{
			ventana.draw(usuario.shapesTypes[i]);
		}
		if (bTemporalPositionMouse == true)
		{
			RectangleShape RectangleTemporal;
			sf::Vector2f size = posFinal - posInicial;
			RectangleTemporal.setSize(sf::Vector2f(std::abs(size.x), std::abs(size.y)));
			RectangleTemporal.setPosition(posInicial);
			RectangleTemporal.setFillColor(colorShapes);
			ventana.draw(RectangleTemporal);
		}
	}

	ventana.display();
}
