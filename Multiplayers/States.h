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
		kLOGIN,
		kSIGNUP,
		kDISCONNECT,
		kCHAT,
		kMOUSESTATE,
		kLINE,
		kRECT,
		kCIRCLE,
		kNUM_MESSAGE_TYPE,
		kDELETE_SHAPE
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
	struct ShapeData
	{
		unsigned int IdShape;
		unsigned int IdClient;
		MESSAGE_TYPE_VAR MSGTYPE;
		Unit32 m_posInitialX;
		Unit32 m_posInitialY;
		Unit32 m_posFinalX;
		Unit32 m_posFinalY;
		sf::Color m_cTypeColor;
	}m_msgData;

	void fillCurrentShapeData(sf::Color& TypeColor, sf::Event& Evento, MESSAGE_TYPE::K typeMessage);
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
	struct MessageData
	{
		//string sMsgConecct = "CONNECT";
		unsigned int uiIdClient;
	}m_msgData;
	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
private:
	
};

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
		unsigned int IdClient;
		unsigned int IdShape;
	}m_msgData;
	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};

class MsgLogin : public NetworkMessage
{
public:
	MsgLogin() {
	}
	~MsgLogin() {
	}

	struct MessageData
	{
		string sUsser;
		string sPassword;
	}m_msgData;

	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
};

class MsgSignup : public NetworkMessage
{
public:
	MsgSignup() {
	}
	~MsgSignup() {
	}

	struct MessageData
	{
		string sUsser;
		string sPassword;
	}m_msgData;

	Package packData();
	static bool unPackData(void* pDestData, void* pScrData, size_t numBytes);
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
