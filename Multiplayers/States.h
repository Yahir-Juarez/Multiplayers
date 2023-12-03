#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Packages.h"

using String = std::string;

namespace MESSAGE_TYPE
{
	enum K
	{
		kERROR = 0,
		kPING,
		kCONNECT,
		kDISCONNECT,
		kCHAT,
		kSHAPE,
		kDELETE_SHAPE,
		kNUM_MESSAGE_TYPE,
		kMOUSESTATE
	};
}
namespace TYPE_SHAPE
{
	enum shapes
	{
		LINE = 0,
		RECTANGLE,
		CIRCLE,
		FREEDRAW
	};
}

class NetworkMessage
{
public:
	NetworkMessage() = default;
	virtual ~NetworkMessage() = default;
	virtual Package packData() = 0;
};

class ShapesData : public NetworkMessage
{
public:
	MESSAGE_TYPE_VAR MSGTYPE;
	struct ShapeData
	{
		TYPE_SHAPE::shapes typeShape;
		float m_posInitialX;
		float m_posInitialY;
		float m_posFinalX;
		float m_posFinalY;
		sf::Color m_cTypeColor;
		unsigned int IdShape;
		unsigned int IdClient;
	}m_msgData;

	void fillCurrentShapeData(sf::Color& TypeColor, sf::Event& Evento, TYPE_SHAPE::shapes typeMessage);
	void fillCurrentShapeDataFinal(sf::Event& Evento);

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);

	Package packData();
};

//class MsgConnected : public NetworkMessage
//{
//public:
//	MsgConnected() {
//	}
//	~MsgConnected() {
//	}
//	struct MessageData
//	{
//		//string sMsgConecct = "CONNECT";
//		//unsigned int uiIdClient;
//	}m_msgData;
//	Package packData();
//	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
//private:
//	
//};

class MsgUsser : public NetworkMessage
{
public:
	MsgUsser() {
	}
	~MsgUsser() {
	}
	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);

	string m_msgDATA;
};

class MsgDelete : public NetworkMessage
{
public:
	MsgDelete() {
	}
	~MsgDelete() {
	}
	struct MessageData
	{
		unsigned int IdShape;
	}m_msgData;
	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};

class MsgConnect : public NetworkMessage
{
public:
	MsgConnect() {
	}
	~MsgConnect() {
	}

	string m_msgData;

	Package packData();
};

class MsgPass : public NetworkMessage
{
public:
	MsgPass() {
	}
	~MsgPass() {
	}
	Package packData();

	string m_msgDATA;
};

class MsgDisconnect : public NetworkMessage
{
public:
	MsgDisconnect() {
	}
	~MsgDisconnect() {
	}
	Package packData();
private:
	string m_msgDATA = "Disconnect";
};

class MsgChat : public NetworkMessage
{
public:
	MsgChat() {
	}
	~MsgChat() {
	}
	Package packData();

	string m_msgDATA;
};

class MsgMouseData : public NetworkMessage
{
public:
	struct MouseData
	{
		Unit32 m_posX;
		Unit32 m_posY;
		union
		{
			Unit32 buttons;
			struct
			{
				Unit32 left : 1;
				Unit32 right : 1;
				Unit32 middle : 1;
				Unit32 xButton1 : 1;
				Unit32 xButton2 : 1;
			};
		}m_buttonStates;
	}m_msgData;
	Package packData() override;

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
	void fillCurrentMouseData();
};
