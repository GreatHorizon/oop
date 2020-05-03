#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_iStream(input)
	, m_oStream(output)
	, m_actionMap(
		{
			{"TurnOn", bind(&CRemoteControl::TurnOn, this, _1)},
			{"TurnOff", bind(&CRemoteControl::TurnOff, this, _1)},
			{"Info", bind(&CRemoteControl::Info, this, _1)},
			{"SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1)},
			{"SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1)},
			{"SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1)},
			{"DeleteChannelName", bind(&CRemoteControl::DeleteChannelName, this, _1)},
		})
{	
}

bool CRemoteControl::HandleCommand()
{
	string consoleLine;
	getline(m_iStream, consoleLine);
	istringstream sStream(consoleLine);

	string action;
	sStream >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(sStream);
	}

	return false;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	if (m_tv.IsTurnedOn())
	{
		string channelLine;
		getline(args, channelLine);
		boost::trim_all(channelLine);

		std::optional channel = ConvertDigitStringIntoNumber(channelLine);
		if (channel)
		{
			m_tv.SelectChannel(channel.value()) ? m_oStream << "Channel selected\n"
				: m_oStream << "Channel " << channel.value() << " is out of range 1-99\n"; ;
		}
		else
		{
			m_tv.SelectChannel(channelLine) ? m_oStream << "Channel selected\n"
				: m_oStream << "Unknown channel\n";
		}	
	}
	else
	{
		m_oStream << "TV is turned off\n";
	}
	
	return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream& args)
{
	if (m_tv.IsTurnedOn())
	{	
		int currentChannel = m_tv.GetChannel();
		m_tv.SelectChannel(m_tv.GetPreviousChannel());
		m_oStream << "Previous channel - \"" << 
			to_string(m_tv.GetChannel()) << "\" was selected\n";
	}
	else
	{
		m_oStream << "TV is turned off\n";
	}

	return true;
}

bool CRemoteControl::SetChannelName(std::istream& args)
{
	if (m_tv.IsTurnedOn())
	{
		string channelName, channel;
		args >> channel;
		
		auto channelNumber = ConvertDigitStringIntoNumber(channel);

		if (!channelNumber)
		{
			m_oStream << "Unknown channel\n";
			return true;
		}

		if (!m_tv.IsChannelInRange(channelNumber.value()))
		{
			m_oStream << "Channel " << channelNumber.value() << " is out of range 1-99\n";
			return true;
		}

		getline(args, channelName);
		boost::trim_all(channelName);
		if (channelName.empty())
		{
			m_oStream << "Channel name should not be empty\n";
			return true;
		}

		m_tv.SetChannelName(channelNumber.value(), channelName);
		m_oStream << "Name \"" << channelName << "\" has been set for channel "<< channelNumber.value() << "\n";
		return true;
	}

	m_oStream << "TV is turned off\n";
	return true;
}

bool CRemoteControl::DeleteChannelName(std::istream& args)
{
	if (m_tv.IsTurnedOn())
	{
		string channelName;
		getline(args, channelName);

		if (channelName.empty())
		{
			m_oStream << "Channel name should not be empty\n";
			return true;
		}

		boost::trim(channelName);

		m_tv.DeleteChannelName(channelName) ? m_oStream << "Channel name was deleted\n"
			:m_oStream << "There is not channel with specified name\n";
	}
	else
	{
		m_oStream << "TV is turned off\n";
	}
	
	return true;
}

std::optional<int> CRemoteControl::
	ConvertDigitStringIntoNumber(const std::string& digitLine) const
{
	int channel = 0;
	size_t stoppedAt;
	try
	{
		channel = stoi(digitLine, &stoppedAt, 10);
	}
	catch (const std::exception&)
	{
		return std::nullopt;
	}

	if (digitLine[stoppedAt] != '\0')
	{
		return std::nullopt;
	}

	return channel;
}


bool CRemoteControl::TurnOn(std::istream& args)
{
	m_tv.TurnOn();
	m_oStream << "TV is turned on\n";
	return true;
}

bool CRemoteControl::TurnOff(std::istream& args)
{
	m_tv.TurnOff();
	m_oStream << "TV is turned off\n";
	return true;
}

void CRemoteControl::PrintChannelList() const
{
	auto channelMap = m_tv.GetChannelMap();

	if (!channelMap.empty())
	{
		m_oStream << "Channel list:\n";
		for (auto channel : channelMap)
		{
			m_oStream << "Channel " << channel.first << " - \"" << channel.second << "\"\n";
		}
	}
}

bool CRemoteControl::Info(std::istream& args) const
{
	if (m_tv.IsTurnedOn())
	{
		m_oStream << "TV is turned on\nChannel is " + to_string(m_tv.GetChannel()) + "\n";
		PrintChannelList();
	}
	else 
	{
		m_oStream << "TV is turned off\n";
	}
	return true;
}