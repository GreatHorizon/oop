#include "stdafx.h"
#include "../TVSet/RemoteControl.h"
#include "../TVSet/TVSet.h"
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const boost::optional<int>& expectedChannel, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.ProcessCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_CASE(can_turn_on_tv)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}
	
	BOOST_AUTO_TEST_CASE(can_turn_off_tv)
	{
		VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
	}

	BOOST_AUTO_TEST_SUITE(info_command_test)

		BOOST_AUTO_TEST_CASE(cant_show_info_when_turned_off)
		{
			VerifyCommandHandling("Info", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_show_info_when_turned_on)
		{
			tv.TurnOn();
			VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is 1\n");
		}

		BOOST_AUTO_TEST_CASE(can_show_info_and_channels_names_when_names_specified)
		{
			tv.TurnOn();
			tv.SetChannelName(91, "HBO");
			VerifyCommandHandling("Info", 1, 
				"TV is turned on\nChannel is 1\nChannel list:\nChannel 91 - \"HBO\"\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(set_channe_name_command_test)
		BOOST_AUTO_TEST_CASE(cant_set_channel_name_when_turned_off)
		{
			VerifyCommandHandling("SetChannelName 30 MTV", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_set_channel_name_when_turned_on)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 30 MTV", 1, "Name \"MTV\" has been set for channel 30\n");
			BOOST_CHECK_EQUAL(tv.GetChannelName(30).value(), "MTV");
		}

		BOOST_AUTO_TEST_CASE(cant_set_empty_channel_name)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 30", 1, "Channel name should not be empty\n");
			BOOST_CHECK(!tv.GetChannelName(30));
		}

		BOOST_AUTO_TEST_CASE(cant_set_channel_channel_name_containing_only_spaces)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 30        ", 1, "Channel name should not be empty\n");
			BOOST_CHECK(!tv.GetChannelName(30));
		}

		BOOST_AUTO_TEST_CASE(cant_set_name_for_incorrect_channel)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 30sasd HBO", 1, "Unknown channel\n");
			VerifyCommandHandling("SetChannelName 99999999999 HBO", 1, "Unknown channel\n");
		}

		BOOST_AUTO_TEST_CASE(can_set_channel_channel_name_ignoring_extra_spaces)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 30        HBO   ", 1,
				"Name \"HBO\" has been set for channel 30\n");
			BOOST_CHECK_EQUAL(tv.GetChannelName(30).value(), "HBO");
		}

		BOOST_AUTO_TEST_CASE(cant_set_name_for_out_of_range_channel)
		{
			tv.TurnOn();
			VerifyCommandHandling("SetChannelName 100 HBO", 1, 
				"Channel 100 is out of range 1-99\n");
		}	
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(select_channel_test)
		BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
		{
			VerifyCommandHandling("SelectChannel 10", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_select_chanel_by_number)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel 10", 10, "Channel selected\n");
		}

		BOOST_AUTO_TEST_CASE(can_select_chanel_by_name)
		{
			tv.TurnOn();
			tv.SetChannelName(10, "National Geographic");
			VerifyCommandHandling("SelectChannel National Geographic", 10, "Channel selected\n");
		}

		BOOST_AUTO_TEST_CASE(cant_select_chanel_by_nonexistent_name)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel National Geographic", 1, "Unknown channel\n");
		}

		BOOST_AUTO_TEST_CASE(cant_select_chanel_by_incorrect_number)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel aaa123", 1, "Unknown channel\n");
		}

		BOOST_AUTO_TEST_CASE(cant_select_chanel_out_of_range)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel 100", 1,
				"Channel 100 is out of range 1-99\n");
			VerifyCommandHandling("SelectChannel 0", 1,
				"Channel 0 is out of range 1-99\n");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(delete_channe_name_command_test)
		BOOST_AUTO_TEST_CASE(cant_delete_name_when_turned_off)
		{
			VerifyCommandHandling("DeleteChannelName National Geographic", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_delete_name_when_turned_on)
		{
			tv.TurnOn();
			tv.SetChannelName(10, "National Geographic");
			VerifyCommandHandling("DeleteChannelName National Geographic", 1, "Channel name was deleted\n");
		}

		BOOST_AUTO_TEST_CASE(cant_delete_non_existent_name)
		{
			tv.TurnOn();
			tv.SetChannelName(10, "ABC");
			VerifyCommandHandling("DeleteChannelName National Geographic", 1, "There is not channel with specified name\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(select_previous_channel_test)
		BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_turned_off)
		{
			VerifyCommandHandling("SelectPreviousChannel", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_select_previous_channel_when_turned_on)
		{
			tv.TurnOn();
			tv.SelectChannel(12);
			VerifyCommandHandling("SelectPreviousChannel", 1, 
				"Previous channel - \"1\" was selected\n");
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}

		BOOST_AUTO_TEST_CASE(can_select_previous_channel_after_subsequent_turning_on)
		{
			tv.TurnOn();
			tv.SelectChannel(12);
			tv.SelectChannel(30);
			tv.TurnOff();
			tv.TurnOn();
			VerifyCommandHandling("SelectPreviousChannel", 12,
				"Previous channel - \"12\" was selected\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(convert_digit_string_into_number_test)


	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


