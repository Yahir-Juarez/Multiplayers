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
	Color rgb(184, 184, 184);
	ventana.clear(Color(rgb));
	if (usuario.enuEstado == Inicio)
	{
		inicioSesion.render(ventana);
	}
	else if (usuario.enuEstado == InicioUser)
	{
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

	ventana.display();
}
