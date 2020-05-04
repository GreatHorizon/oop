#pragma once
#include <map>
#include <string>
#include <optional>

class CTVSet
{
public:
	void TurnOn();
	void TurnOff();
	bool IsTurnedOn() const;
	int GetChannel() const;
	int GetPreviousChannel() const;
	bool IsChannelInRange(int channel) const;
	bool SelectChannel(int channel);
	bool SelectChannel(const std::string& channelName);
	bool DeleteChannelName(const std::string& channelName);	
	bool SetChannelName(int channelNumber, const std::string& channelName);
	
	std::map<int, std::string> GetChannelMap() const;
	std::optional<int> GetChannelByName(const std::string& channelName) const;
	std::optional<std::string> GetChannelName(int channel) const;
	
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;
	std::map<int, std::string> m_channelMap = {};
	static const int m_maxChannel = 99;
	static const int m_minChannel = 1;
};

