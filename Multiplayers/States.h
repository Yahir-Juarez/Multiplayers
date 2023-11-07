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
		kCONNECT,
		kUSSER,
		kPASS,
		kDISCONNECT,
		kCHAT,
		kMOUSESTATE,
		kLINE,
		kRECT,
		kCIRCLE,
		kNUM_MESSAGE_TYPE
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
	enum typesShapes
	{
		Rectangle = 0,
		Circle,
		Line,
		FreeStroke
	}typeShape;
	struct ShapeData
	{
		Unit32 m_posInitialX;
		Unit32 m_posInitialY;
		Unit32 m_posFinalX;
		Unit32 m_posFinalY;
		union
		{
			Unit32 TypeAndColor;
			struct
			{
				Unit32 Red : 1;
				Unit32 Blue : 1;
				Unit32 Magenta : 1;
				Unit32 Black : 1;
				Unit32 Rect : 1;
				Unit32 Circle : 1;
				Unit32 Line : 1;
				Unit32 FreeSroke : 1;
			};
		}m_TypeAndColorStates;
	}m_msgData;
	void fillCurrentShapeData(sf::Color& TypeColor, sf::Event& Evento);
	void fillCurrentShapeDataFinal(sf::Event& Evento);

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);

	Package packData();
};

class MsgConnect : public NetworkMessage
{
public:
	MsgConnect() {
	}
	~MsgConnect() {
	}
	Package packData();
private:
	string m_msgDATA = "CONNECT";
};

class MsgUsser : public NetworkMessage
{
public:
	MsgUsser() {
	}
	~MsgUsser() {
	}
	Package packData();

	string m_msgDATA;
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

class MsgLine : public ShapesData
{
public:
	Package packData() override;

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};

class MsgRect : public ShapesData
{
public:
	Package packData() override;

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};

class MsgCircle : public ShapesData
{
public:
	Package packData() override;

	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};
