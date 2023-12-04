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
	oFLine.createButton("Textures/Line.png", sizeShapestype, posicionColor);
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
		interactiveKeyBord.inputKeyBoard(actualKeyboard, usuario, eventos);
	}
	buttonPressed(); 

	if (usuario.enuEstado == Aplicacion)
	{
		createShapes();
		commandsApp();
	}
}

void App::createShapes()
{
	Time tiempo;
	tiempo = relojShapes.getElapsedTime();
	float tiempoButtons = tiempo.asSeconds();
	if (eventos.mouseButton.button == sf::Mouse::Left && bTemporalPositionMouse == false && tiempoButtons > .1 && bPressButton == false)
	{
		posInicial = sf::Vector2f(eventos.mouseButton.x, eventos.mouseButton.y);
		posFinal = posInicial;
		bTemporalPositionMouse = true;
		temporalShapes.fillCurrentShapeData(cActualColor, eventos, eTypeMessageActual);
	}
	else if (eventos.type == sf::Event::MouseMoved && !(eTypeMessageActual == TYPE_SHAPE::shapes::FREEDRAW))
	{
		// Actualiza la posición final del punto mientras se arrastra
		if (bTemporalPositionMouse)
		{
			posFinal = sf::Vector2f(eventos.mouseMove.x, eventos.mouseMove.y);
			bMoveMouse = true;
		}
	}
	else if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left && bPressButton == false && bTemporalPositionMouse == true && bMoveMouse == true)
	{
		// Deja de arrastrar el punto y crea la figura
		bTemporalPositionMouse = false;
		bMoveMouse = false;
		relojShapes.restart();
		if ((eTypeMessageActual == TYPE_SHAPE::shapes::FREEDRAW))
		{
			return;
		}
		temporalShapes.fillCurrentShapeDataFinal(eventos);
		temporalShapes.m_msgData.IdClient = usuario.uiIdClient;
		auto connect = temporalShapes.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		usuario.usuario(finalPackage);
	}
	else if (eventos.type == sf::Event::MouseButtonReleased && eventos.mouseButton.button == sf::Mouse::Left && bMoveMouse == false)
	{
		bTemporalPositionMouse = false;
		bMoveMouse = false;
		relojShapes.restart();
	}
	else if (eTypeMessageActual == TYPE_SHAPE::shapes::FREEDRAW && eventos.type == sf::Event::MouseMoved)
	{
		if (bTemporalPositionMouse)
		{
			//temporalShapes.fillCurrentShapeDataFinal(eventos);
			posFinal = sf::Vector2f(eventos.mouseMove.x, eventos.mouseMove.y);
			temporalShapes.m_msgData.m_posFinalX = posFinal.x;
			temporalShapes.m_msgData.m_posFinalY = posFinal.y;
			temporalShapes.m_msgData.IdClient = usuario.uiIdClient;
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
				bPressButton = true;
			}
			else if (oColorBlue.buttonEvent(eventos))
			{
				cActualColor = Color::Blue;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oColorCyan.buttonEvent(eventos))
			{
				cActualColor = Color::Cyan;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oColorGreen.buttonEvent(eventos))
			{
				cActualColor = Color::Green;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oColorMagenta.buttonEvent(eventos))
			{
				cActualColor = Color::Magenta;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oColorRed.buttonEvent(eventos))
			{
				cActualColor = Color::Red;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oColorYellow.buttonEvent(eventos))
			{
				cActualColor = Color::Yellow;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oRectangle.buttonEvent(eventos))
			{
				eTypeMessageActual = TYPE_SHAPE::shapes::RECTANGLE;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oCircle.buttonEvent(eventos))
			{
				eTypeMessageActual = TYPE_SHAPE::shapes::CIRCLE;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oLine.buttonEvent(eventos))
			{
				eTypeMessageActual = TYPE_SHAPE::shapes::FREEDRAW;
				relojButtons.restart();
				bPressButton = true;
			}
			else if (oFLine.buttonEvent(eventos))
			{
				eTypeMessageActual = TYPE_SHAPE::shapes::LINE;
				relojButtons.restart();
				bPressButton = true;
			}
			else
			{
				bPressButton = false;
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
	Color rgbGrisAntracita(41, 49, 51);
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
		ventana.clear(Color(rgbGrisAntracita));
		
		drawShapes();
		drawTemporalShapes();

		if (activeKeyBoard == true)
		{
			keyboardOn.render(ventana);
			interactiveKeyBord.render(ventana, Vector2f((window_x * 1) / 40, (window_y * 36) / 40));
		}
		else
		{
			keyboardOff.render(ventana);
		}
		renderButtonsApp();
	}
	interactiveKeyBord.render(ventana, Vector2f((window_x * 1) / 40, (window_y * 32) / 40), usuario.msgActual);

	ventana.display();
}

void App::drawShapes()
{
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
		ventana.draw(usuario.vShapes[i].freeLine.data(), usuario.vShapes[i].freeLine.size(), sf::PrimitiveType::Lines);
	}
}
void App::drawTemporalShapes()
{
	if (bTemporalPositionMouse == true)
	{
		if (eTypeMessageActual == TYPE_SHAPE::shapes::RECTANGLE)
		{
			RectangleShape RectangleTemporal;
			sf::Vector2f size = posFinal - posInicial;
			RectangleTemporal.setSize(size);
			RectangleTemporal.setPosition(posInicial);
			RectangleTemporal.setFillColor(cActualColor);
			ventana.draw(RectangleTemporal);
		}
		if (eTypeMessageActual == TYPE_SHAPE::shapes::CIRCLE)
		{
			CircleShape CircleTemporal;
			float radio = DistanciaEntreDosPuntos2(posInicial, posFinal);
			CircleTemporal.setRadius(radio);
			CircleTemporal.setPosition(Vector2f(posInicial.x - radio, posInicial.y - radio));
			CircleTemporal.setFillColor(cActualColor);
			ventana.draw(CircleTemporal);
		}
		if (eTypeMessageActual == TYPE_SHAPE::shapes::LINE)
		{
			sf::Vertex vLinePt1 = posInicial;
			vLinePt1.color = cActualColor;
			sf::Vertex vLinePt2 = posFinal;
			vLinePt2.color = cActualColor;
			vector<sf::Vertex> Line;
			Line.push_back(vLinePt1);
			Line.push_back(vLinePt2);

			ventana.draw(Line.data(), 2, sf::PrimitiveType::Lines);
		}
	}
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

void App::commandsApp()
{
	if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Z) && bCtrlZActive == false)
	{
		bCtrlZActive = true;
		MsgDelete commandDelete;
		auto connect = commandDelete.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		usuario.usuario(finalPackage);
	}
	else if (Keyboard::isKeyPressed(Keyboard::RControl) && Keyboard::isKeyPressed(Keyboard::Z))
	{
		MsgDelete commandDelete;
		auto connect = commandDelete.packData();
		Package finalPackage = getPackage(connect.data(), connect.size());
		usuario.usuario(finalPackage);
	}
	else if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Z))
	{

	}
	else
	{
		bCtrlZActive = false;
	}
}
