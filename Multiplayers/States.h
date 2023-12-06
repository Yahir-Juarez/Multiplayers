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

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();
};

class MsgPing : public NetworkMessage
{
public:
	MsgPing() {
	}
	~MsgPing() {
	}

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();
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

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
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

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();
};

class MsgChat : public NetworkMessage
{
public:
	MsgChat() {
	}
	~MsgChat() {
	}

	string m_msgData;

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();
};

class MsgError : public NetworkMessage
{
public:
	MsgError() {
	}
	~MsgError() {
	}

	string m_msgData;

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();
};

class MsgDisconnect : public NetworkMessage
{
public:
	MsgDisconnect() {
	}
	~MsgDisconnect() {
	}

	/////////////////////////////////////////////
	/// <summary>
	/// Package the messages
	/// </summary>
	/// <returns></Package>
	/////////////////////////////////////////////
	Package packData();

private:
	string m_msgData = "Disconnect";
};