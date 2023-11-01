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