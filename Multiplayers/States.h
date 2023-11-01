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

#define MESSAGE_TYPE_VAR unsigned short

class NetworkMessage
{
public:
	NetworkMessage() = default;
	virtual ~NetworkMessage() = default;
	virtual Package packData() = 0;
};

class MsgConnect : public NetworkMessage
{

};

class MsgUsser : public NetworkMessage
{

};

class MsgPass : public NetworkMessage
{

};

class MsgDisconnect : public NetworkMessage
{

};

class MsgChat : public NetworkMessage
{

};

class MsgMouseData : public NetworkMessage
{

};

class MsgLine : public NetworkMessage
{

};

class MsgRect : public NetworkMessage
{

};

class MsgCircle : public NetworkMessage
{

};
