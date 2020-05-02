#pragma once
#include <boost/noncopyable.hpp>
#include <optional>

class CTVSet;

class CRemoteControl : boost::noncopyable
{
public:
	bool HandleCommand();
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);

private:
	void PrintChannelList() const;
	std::optional<int> ConvertDigitStringIntoNumber(std::string& channelLine) const;
	bool Info(std::istream& args) const;

	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& args);
	bool SetChannelName(std::istream& args);
	bool DeleteChannelName(std::istream& args);
	
private:
	typedef std::function<bool(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;

	CTVSet& m_tv;
	std::istream& m_iStream;
	std::ostream& m_oStream;
	const ActionMap m_actionMap;
};

