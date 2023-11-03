#include "States.h"

Package MsgConnect::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCONNECT;
	std::vector<char> data;
	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());

	return data;
}

Package MsgUsser::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kUSSER;
	std::vector<char> data;
	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());

	return data;
}

Package MsgPass::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kPASS;
	std::vector<char> data;
	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());

	return data;
}

Package MsgChat::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kPASS;
	std::vector<char> data;
	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());

	return data;
}
Package MsgMouseData::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kMOUSESTATE;
	Package data;
	data.resize(sizeof(m_msgData) + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), &m_msgData, sizeof(m_msgData));

	return data;
}

void ShapesData::fillCurrentShapeData(sf::Color& TypeColor, sf::Event& Evento)
{
	if (Evento.mouseButton.button == sf::Mouse::Left)
	{
		m_msgData.m_posInitialX = Evento.mouseButton.x;
		m_msgData.m_posInitialY = Evento.mouseButton.y;
		m_msgData.m_TypeAndColorStates.Blue = 0;
		m_msgData.m_TypeAndColorStates.Red = 0;
		m_msgData.m_TypeAndColorStates.White = 0;
		m_msgData.m_TypeAndColorStates.Black = 0;
		if (TypeColor == sf::Color::Red){ m_msgData.m_TypeAndColorStates.Red = 1; }
		if (TypeColor == sf::Color::Blue) { m_msgData.m_TypeAndColorStates.Blue = 1; }
		if (TypeColor == sf::Color::White) { m_msgData.m_TypeAndColorStates.White = 1; }
		if (TypeColor == sf::Color::Black) { m_msgData.m_TypeAndColorStates.Black = 1; }
	}
}

void ShapesData::fillCurrentShapeDataFinal(sf::Event& Evento)
{
	m_msgData.m_posFinalX = Evento.mouseButton.x;
	m_msgData.m_posFinalY = Evento.mouseButton.y;
}

Package ShapesData::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kMOUSESTATE;
	Package data;
	data.resize(sizeof(m_msgData) + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), &m_msgData, sizeof(m_msgData));

	return data;
}

bool MsgMouseData::unPackData(void* pDestData, void* pScrData, size_t numBytes)
{
	cout << numBytes << " " << sizeof(MouseData) << "comprobacion\n";
	if (numBytes != sizeof(MouseData))
	{
		return false;
	}
	memcpy(pDestData, pScrData, numBytes);
}

void MsgMouseData::fillCurrentMouseData()
{
	m_msgData.m_posX = sf::Mouse::getPosition().x;
	m_msgData.m_posY = sf::Mouse::getPosition().y;
	m_msgData.m_buttonStates.left = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	m_msgData.m_buttonStates.right = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	m_msgData.m_buttonStates.middle = sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
	m_msgData.m_buttonStates.xButton1 = sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1);
	m_msgData.m_buttonStates.xButton2 = sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2);
}