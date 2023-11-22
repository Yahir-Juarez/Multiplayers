#include "AplicacionCliente.h"

App::App()
{
	Vector2u medidaVentana(window_x, window_y);
	ventana.create(VideoMode(medidaVentana), "Paint");

	Vector2f posicionInicio((window_x * 1)/ 3, window_y / 2);
	Vector2f sizeInicio(300, 300);
	inicioSesion.createButton("Textures/InicioSesion.png", sizeInicio, posicionInicio);
	posicionInicio.x = ((window_x * 2) / 3);
	oLogin.createButton("Textures/Signup.png", sizeInicio, posicionInicio);
	Vector2f posicionTeclado(window_x - 75, window_y - 50);
	Vector2f sizeTeclado(100, 50);
	keyboardOn.createButton("Textures/TecladoEncendido.png", sizeTeclado, posicionTeclado);
	keyboardOff.createButton("Textures/TecladoApagado.png", sizeTeclado, posicionTeclado);

	Vector2f posicionColor((window_x * 1) / 40, (window_y * 1) / 40);
	Vector2f sizeColor(20, 20);
	oColorBlack.createButton(Color::Black, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 1) / 40);
	oColorBlue.createButton(Color::Blue, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 1) / 40);
	posicionColor.y = ((window_y * 3) / 40);
	oColorCyan.createButton(Color::Cyan, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 3) / 40);
	oColorGreen.createButton(Color::Green, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 1) / 40);
	posicionColor.y = ((window_y * 5) / 40);
	oColorMagenta.createButton(Color::Magenta, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 5) / 40);
	oColorRed.createButton(Color::Red, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 1.5) / 40);
	posicionColor.y = ((window_y * 7) / 40);
	oColorYellow.createButton(Color::Yellow, sizeColor, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 10) / 40);
	Vector2f sizeShapestype(60, 60);
	oRectangle.createButton("Textures/cuadrado.png", sizeShapestype, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 14) / 40);
	oCircle.createButton("Textures/circle.png", sizeShapestype, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 18) / 40);
	oLine.createButton("Textures/FLine.png", sizeShapestype, posicionColor);
	posicionColor.x = ((window_x * 2) / 40);
	posicionColor.y = ((window_y * 22) / 40);
	oFLine.createButton("Textures/line.png", sizeShapestype, posicionColor);
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
		createShapes();
	}
}

void App::createShapes()
{
	Time tiempo;
	tiempo = relojShapes.getElapsedTime();
	float tiempoButtons = tiempo.asSeconds();
	if (eventos.mouseButton.button == sf::Mouse::Left && bTemporalPositionMouse == false && tiempoButtons > .1)
	{
		posInicial = sf::Vector2f(eventos.mouseButton.x, eventos.mouseButton.y);
		posFinal = posInicial;
		bTemporalPositionMouse = true;
		temporalShapes.fillCurrentShapeData(cActualColor, eventos, eTypeMessageActual);
	}
	else if (eventos.type == sf::Event::MouseMoved && !(eTypeMessageActual == MESSAGE_TYPE::K::kLINE))
	{
		// Actualiza la posición final del punto mientras se arrastra
		if (bTemporalPositionMouse)
		{
			posFinal = sf::Vector2f(eventos.mouseMove.x, eventos.mouseMove.y);
		}
	}
	else if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left)
	{
		// Deja de arrastrar el punto y crea la figura
		bTemporalPositionMouse = false;
		relojShapes.restart();
		if ((eTypeMessageActual == MESSAGE_TYPE::K::kLINE))
		{
			return;
		}
		temporalShapes.fillCurrentShapeDataFinal(eventos);
		auto connect = temporalShapes.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		usuario.usuario(finalPackage);
	}
	else if (eTypeMessageActual == MESSAGE_TYPE::K::kLINE && eventos.type == sf::Event::MouseMoved)
	{
		if (bTemporalPositionMouse)
		{
			//temporalShapes.fillCurrentShapeDataFinal(eventos);
			posFinal = sf::Vector2f(eventos.mouseMove.x, eventos.mouseMove.y);
			temporalShapes.m_msgData.m_posFinalX = posFinal.x;
			temporalShapes.m_msgData.m_posFinalY = posFinal.y;
			auto connect = temporalShapes.packData();
			Package finalPackage = getPackage(connect.data(), connect.size());
			usuario.usuario(finalPackage);
			temporalShapes.m_msgData.m_posInitialX = temporalShapes.m_msgData.m_posFinalX;
			temporalShapes.m_msgData.m_posInitialY = temporalShapes.m_msgData.m_posFinalY;
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
		if (usuario.enuEstado == estadoApp::Inicio)
		{
			if (inicioSesion.buttonEvent(eventos))
			{
				usuario.bNewUsser = false;
				usuario.enuEstado = estadoApp::InicioUser;
				//usuario.conexion();
				relojButtons.restart();
			}
			if (oLogin.buttonEvent(eventos))
			{
				usuario.bNewUsser = true;
				usuario.enuEstado = estadoApp::InicioUser;
				//usuario.conexion();
				relojButtons.restart();
			}
		}
		else if (usuario.enuEstado == estadoApp::Aplicacion)
		{
			if (oColorBlack.buttonEvent(eventos))
			{
				cActualColor = Color::Black;
				relojButtons.restart();
			}
			else if (oColorBlue.buttonEvent(eventos))
			{
				cActualColor = Color::Blue;
				relojButtons.restart();
			}
			else if (oColorCyan.buttonEvent(eventos))
			{
				cActualColor = Color::Cyan;
				relojButtons.restart();
			}
			else if (oColorGreen.buttonEvent(eventos))
			{
				cActualColor = Color::Green;
				relojButtons.restart();
			}
			else if (oColorMagenta.buttonEvent(eventos))
			{
				cActualColor = Color::Magenta;
				relojButtons.restart();
			}
			else if (oColorRed.buttonEvent(eventos))
			{
				cActualColor = Color::Red;
				relojButtons.restart();
			}
			else if (oColorYellow.buttonEvent(eventos))
			{
				cActualColor = Color::Yellow;
				relojButtons.restart();
			}
			else if (oRectangle.buttonEvent(eventos))
			{
				eTypeMessageActual = MESSAGE_TYPE::K::kRECT;
				relojButtons.restart();
			}
			else if (oCircle.buttonEvent(eventos))
			{
				eTypeMessageActual = MESSAGE_TYPE::K::kCIRCLE;
				relojButtons.restart();
			}
			else if (oLine.buttonEvent(eventos))
			{
				eTypeMessageActual = MESSAGE_TYPE::K::kLINE;
				relojButtons.restart();
			}
			else if (oFLine.buttonEvent(eventos))
			{
				eTypeMessageActual = MESSAGE_TYPE::K::kLINE;
				relojButtons.restart();
			}
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

float DistanciaEntreDosPuntos2(Vector2f& inicial, Vector2f & final)
{
	float distancia = ((pow((inicial.x - final.x), 2)) + (pow((inicial.y - final.y), 2)));
	distancia = sqrt(distancia);
	return distancia;
}

void App::render()
{
	Vector2f vfTextPossUsserPass(300, 300);
	Vector2f vfTextMessage(500, 300);
	
	Color rgbGris(184, 184, 184);
	if (usuario.enuEstado == Inicio)
	{
		ventana.clear(Color(rgbGris));
		inicioSesion.render(ventana);
		oLogin.render(ventana);
	}
	else if (usuario.enuEstado == InicioUser)
	{
		ventana.clear(Color(rgbGris));
		RectangleShape rsUsserBox;
		rsUsserBox.setPosition(vfTextMessage);
		rsUsserBox.setSize(Vector2f(500, 50));
		rsUsserBox.setFillColor(Color::White);
		KbMessageForClient.render(ventana, vfTextPossUsserPass, "Usser");
		ventana.draw(rsUsserBox);
		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, vfTextMessage);
		}
		else
		{
			keyboardOff.render(ventana);
		}
	}
	else if (usuario.enuEstado == InicioPassword)
	{
		ventana.clear(Color(rgbGris));
		RectangleShape rsUsserBox;
		rsUsserBox.setPosition(vfTextMessage);
		rsUsserBox.setSize(Vector2f(500, 50));
		rsUsserBox.setFillColor(Color::White);
		KbMessageForClient.render(ventana, vfTextPossUsserPass, "Password");
		ventana.draw(rsUsserBox);
		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, vfTextMessage);
		}
		else
		{
			keyboardOff.render(ventana);
		}
	}
	else if (usuario.enuEstado == Aplicacion)
	{
		ventana.clear(Color::White);
		
		for (int i = 0; i < usuario.vShapes.size(); i++)
		{
			for (int j = 0; j < usuario.vShapes[i].shapesTypes.size(); j++)
			{
				ventana.draw(*usuario.vShapes[i].shapesTypes[j]);
			}
			for (int j = 0; j < usuario.vShapes[i].circleObjects.size(); j++)
			{
				ventana.draw(*usuario.vShapes[i].circleObjects[j]);
			}
		}
		if (bTemporalPositionMouse == true)
		{
			if (eTypeMessageActual == MESSAGE_TYPE::K::kRECT)
			{
				RectangleShape RectangleTemporal;
				sf::Vector2f size = posFinal - posInicial;
				RectangleTemporal.setSize(size);
				RectangleTemporal.setPosition(posInicial);
				RectangleTemporal.setFillColor(cActualColor);
				ventana.draw(RectangleTemporal);
			}
			if (eTypeMessageActual == MESSAGE_TYPE::K::kCIRCLE)
			{
				CircleShape CircleTemporal;
				float radio = DistanciaEntreDosPuntos2(posInicial, posFinal);
				CircleTemporal.setRadius(radio);
				CircleTemporal.setPosition(Vector2f(posInicial.x - radio, posInicial.y - radio));
				CircleTemporal.setFillColor(cActualColor);
				ventana.draw(CircleTemporal);
			}
		}

		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, Vector2f(window_x / (10 / 3), window_y / (10 / 4)));
		}
		else
		{
			keyboardOff.render(ventana);
		}

		ventana.draw(usuario.freeLine.data(), usuario.freeLine.size(), sf::PrimitiveType::Lines);
		renderButtonsApp();
	}

	ventana.display();
}

void App::renderButtonsApp()
{
	oRectangle.render(ventana);
	oCircle.render(ventana);
	oFLine.render(ventana);
	oLine.render(ventana);
	oColorBlack.render(ventana);
	oColorBlue.render(ventana);
	oColorCyan.render(ventana);
	oColorGreen.render(ventana);
	oColorMagenta.render(ventana);
	oColorRed.render(ventana);
	oColorYellow.render(ventana);
}
