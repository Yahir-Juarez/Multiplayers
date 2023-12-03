#include "States.h"


//////////////////////////////////////////////////////////	CONNECTED ///////////////////////////////////////////////////////

//Package MsgConnected::packData()
//{
//	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCONNECTED;
//	std::vector<char> data;
//	data.resize(sizeof(m_msgData) + sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), &m_msgData, sizeof(m_msgData));
//
//	return data;
//}
//
//bool MsgConnected::unPackData(void* pDestData, void* pScrData, size_t numBytes)
//{
//	cout << numBytes << " " << sizeof(MessageData) << "comprobacion\n";
//	if (numBytes != sizeof(MessageData))
//	{
//		return false;
//	}
//	memcpy(pDestData, pScrData, numBytes);
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Package MsgUsser::packData()
//{
//	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCONNECT;
//	std::vector<char> data;
//	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());
//
//	return data;
//}
//
//Package MsgPass::packData()
//{
//	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kLOGIN;
//	std::vector<char> data;
//	data.resize(m_msgDATA.size() + sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgDATA.data(), m_msgDATA.size());
//
//	return data;
//}

Package MsgChat::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCHAT;
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

Package MsgDelete::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kDELETE_SHAPE;
	Package data;
	data.resize(sizeof(m_msgData) + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), &m_msgData, sizeof(m_msgData));

	return data;
}

//////////////////////////////////////////////////////////// Funcion Shapes //////////////////////////////////////////////////////////////////////////////////

void ShapesData::fillCurrentShapeData(sf::Color& TypeColor, sf::Event& Evento, TYPE_SHAPE::shapes typeMessage)
{
	if (Evento.mouseButton.button == sf::Mouse::Left)
	{

		m_msgData.m_posInitialX = Evento.mouseButton.x;
		m_msgData.m_posInitialY = Evento.mouseButton.y;
		m_msgData.m_cTypeColor = TypeColor;
		MSGTYPE = MESSAGE_TYPE::kSHAPE;
		m_msgData.typeShape = typeMessage;
		/*if (typeMessage == MESSAGE_TYPE::kRECT)
		{
			m_msgData.prueba = "sip rectangulo";
		}*/
	}
}

void ShapesData::fillCurrentShapeDataFinal(sf::Event& Evento)
{
	m_msgData.m_posFinalX = Evento.mouseButton.x;
	m_msgData.m_posFinalY = Evento.mouseButton.y;
}

Package ShapesData::packData()
{
	Package data;
	data.resize(sizeof(m_msgData) + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), &m_msgData, sizeof(m_msgData));

	return data;
}

bool ShapesData::unPackData(void* pDestData, void* pScrData, size_t numBytes)
{
	cout << numBytes << " " << sizeof(ShapeData) << "comprobacion\n";
	if (numBytes != sizeof(ShapeData))
	{
		return false;
	}
	memcpy(pDestData, pScrData, numBytes);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////	SIGNUP	//////////////////////////////////////////////////////////////////

//Package MsgSignup::packData()
//{
//	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCONNECT;
//	Package data;
//	data.resize(m_msgData.size() + sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
//	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgData.data(), m_msgData.size());
//
//	return data;
//}

//bool MsgSignup::unPackData(void* pDestData, void* pScrData, size_t numBytes)
//{
//	cout << numBytes << " " << m_msgData.size() << "comprobacion\n";
//	if (numBytes != m_msgData.size())
//	{
//		return false;
//	}
//	memcpy(pDestData, pScrData, numBytes);
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////	LOGIN	//////////////////////////////////////////////////////////////////

Package MsgConnect::packData()
{
	MESSAGE_TYPE_VAR MSGTYPE = MESSAGE_TYPE::kCONNECT;
	Package data;
	data.resize(m_msgData.size() + sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data(), &MSGTYPE, sizeof(MESSAGE_TYPE_VAR));
	memcpy(data.data() + sizeof(MESSAGE_TYPE_VAR), m_msgData.data(), m_msgData.size());

	return data;
}

//bool MsgConnect::unPackData(void* pDestData, void* pScrData, size_t numBytes)
//{
//	cout << numBytes << " " << sizeof(MessageData) << "comprobacion\n";
//	if (numBytes != sizeof(MessageData))
//	{
//		return false;
//	}
//	memcpy(pDestData, pScrData, numBytes);
//}

bool MsgDelete::unPackData(void* pDestData, void* pScrData, size_t numBytes)
{
	cout << numBytes << " " << sizeof(MessageData) << "comprobacion\n";
	if (numBytes != sizeof(MessageData))
	{
		return false;
	}
	memcpy(pDestData, pScrData, numBytes);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MsgUsser::unPackData(void* pDestData, void* pScrData, size_t numBytes)
{
	if (numBytes != sizeof(m_msgDATA))
	{
		return false;
	}
	memcpy(pDestData, pScrData, numBytes);
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
