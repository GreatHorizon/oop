#include "TVSet.h"
#include "stdafx.h"
#include "optional"

bool CTVSet::IsTurnedOn() const 
{
	return m_isOn;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

std::map<int, std::string> CTVSet::GetChannelMap() const
{
	return m_channelMap;
}

std::optional<std::string> CTVSet::GetChannelName(int channel) const
{
	if (m_isOn)
	{
		auto channelPosition = m_channelMap.find(channel);
		if (channelPosition != m_channelMap.end())
		{
			return channelPosition->second;
		}

	}

	return std::nullopt;
}

std::optional<int> CTVSet::GetChannelByName(const std::string& channelName) const
{
	if (m_isOn)
	{
		for (auto channel : m_channelMap)
		{
			if (channel.second == channelName)
			{
				return channel.first;
			}
		}

	}

	return std::nullopt;
}

int CTVSet::GetPreviousChannel() const
{
	return m_previousChannel;
}

bool CTVSet::SetPreviousChannel(int channel)
{
	if (m_isOn)
	{
		m_previousChannel = channel;	
		return true;
	}

	return false;
}

bool CTVSet::SetChannelName(int channelNumber, const std::string& channelName)
{
	if (m_isOn && IsChannelInRange(channelNumber))
	{
		for (auto channel : m_channelMap)
		{
			if (channel.second == channelName)
			{
				m_channelMap.erase(channel.first);
				break;
			}
		}

		auto channelPostion = m_channelMap.find(channelNumber);
		if (channelPostion != m_channelMap.end())
		{
			channelPostion->second = channelName;
		}
		else
		{
			m_channelMap.emplace(channelNumber, channelName);
		}

		return true;
	}
	
	return false;
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (m_isOn)
	{
		for (auto channel : m_channelMap)
		{
			if (channel.second == channelName)
			{
				m_channelMap.erase(channel.first);
				return true;
			}
		}
	}
	
	return false;
}

bool CTVSet::IsChannelInRange(int channel) const
{
	return (channel < m_minChannel || channel > m_maxChannel ) ? false : true;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

bool CTVSet::SelectChannel(int channel)
{
	if (m_isOn)
	{
		if (IsChannelInRange(channel) && m_isOn)
		{
			m_previousChannel = m_selectedChannel;
			m_selectedChannel = channel;
			return true;
		}
	}

	return false;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	if (m_isOn && !channelName.empty())
	{
		for (auto channel : m_channelMap)
		{
			if (channel.second == channelName)
			{
				m_previousChannel = m_selectedChannel;
				m_selectedChannel = channel.first;
				return true;
			}
		}
	}

	return false;
}