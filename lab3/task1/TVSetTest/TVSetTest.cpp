#include "stdafx.h"
#include "../TVSet/TVSet.h"
#include <optional>

struct TVSetFixture
{
	CTVSet tv;
};


BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), false);
	}

	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		tv.SelectChannel(87);	
		BOOST_REQUIRE_EQUAL(tv.GetChannel(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}


	BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
	{
		BOOST_REQUIRE_EQUAL(tv.GetChannel(), 0);
	}

	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
			BOOST_AUTO_TEST_CASE(displays_channel_1)
			{
				BOOST_REQUIRE_EQUAL(tv.GetChannel(), 1);
			}

			BOOST_AUTO_TEST_CASE(can_be_turned_off)
			{
				tv.TurnOff();
				BOOST_CHECK(!tv.IsTurnedOn());
			}

			BOOST_AUTO_TEST_SUITE(select_channel_test)
				BOOST_AUTO_TEST_CASE(can_be_selected_channel_from_1_to_99)
				{
					BOOST_CHECK(tv.SelectChannel(1));
					BOOST_REQUIRE_EQUAL(tv.GetChannel(), 1);

					BOOST_CHECK(tv.SelectChannel(91));
					BOOST_CHECK_EQUAL(tv.GetChannel(), 91);

					BOOST_CHECK(tv.SelectChannel(99));
					BOOST_CHECK_EQUAL(tv.GetChannel(), 99);
				}

				BOOST_AUTO_TEST_CASE(channel_out_of_range_could_not_be_selected)
				{
					BOOST_CHECK(!tv.SelectChannel(110));
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

					BOOST_CHECK(!tv.SelectChannel(0));
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(select_previous_channel_test)

				BOOST_AUTO_TEST_CASE(after_turning_on_previous_channel_should_be_1)
				{
					BOOST_CHECK_EQUAL(tv.GetPreviousChannel(), 1);
				}

				BOOST_AUTO_TEST_CASE(after_switching_channel_prev_channel_can_be_selected)
				{
					tv.SelectChannel(12);
					BOOST_CHECK_EQUAL(tv.GetChannel(), 12);
					tv.SelectChannel(tv.GetPreviousChannel());
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
				}

				BOOST_AUTO_TEST_CASE(multiply_selecting_prev_channel_should_switch_between_two_channels)
				{
					tv.SelectChannel(12);
					BOOST_CHECK_EQUAL(tv.GetChannel(), 12);
					tv.SelectChannel(tv.GetPreviousChannel());
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
					tv.SelectChannel(tv.GetPreviousChannel());
					BOOST_CHECK_EQUAL(tv.GetChannel(), 12);
					tv.SelectChannel(tv.GetPreviousChannel());
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
				}

			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(set_channel_name_test)
				BOOST_AUTO_TEST_CASE(set_name_for_correct_channel)
				{
					BOOST_CHECK(!tv.GetChannelName(35));
					tv.SetChannelName(35, "National Geographic");
					BOOST_CHECK_EQUAL(tv.GetChannelName(35).value(), "National Geographic");
				}

				BOOST_AUTO_TEST_CASE(set_name_for_incorrect_channel)
				{
					BOOST_CHECK(!tv.SetChannelName(325, "National Geographic"));
				}

				BOOST_AUTO_TEST_CASE(second_name_setting_should_replace_first_variant)
				{
					tv.SetChannelName(35, "National Geographic");
					BOOST_CHECK_EQUAL(tv.GetChannelName(35).value(), "National Geographic");

					tv.SetChannelName(35, "HBO");
					BOOST_CHECK_EQUAL(tv.GetChannelName(35).value(), "HBO");
				}

				BOOST_AUTO_TEST_CASE(erase_channel_name_when_this_name_setting_for_new_channel)
				{
					tv.SetChannelName(35, "HBO");
					BOOST_CHECK_EQUAL(tv.GetChannelByName("HBO").value(), 35);
					tv.SetChannelName(12, "HBO");
					BOOST_CHECK_EQUAL(tv.GetChannelByName("HBO").value(), 12);
				}
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(select_channel_by_name_test)
				BOOST_AUTO_TEST_CASE(channel_could_be_selected_by_existed_name)
				{	
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
					tv.SetChannelName(35, "National Geographic");
					tv.SelectChannel("National Geographic");
					BOOST_CHECK_EQUAL(tv.GetChannel(), 35);
				}

				BOOST_AUTO_TEST_CASE(channel_could_not_be_selected_by_nonexistent_name)
				{
					tv.SelectChannel("ABC");
					BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
				}

				BOOST_AUTO_TEST_CASE(channel_could_not_be_selected_by_empty_name)
				{
					BOOST_CHECK(!tv.SelectChannel(""));
				}

			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE(get_channel_by_name_test)
				BOOST_AUTO_TEST_CASE(can_get_channel_by_existed_name)
				{
					tv.SetChannelName(10, "HBO");
					BOOST_CHECK_EQUAL(tv.GetChannelByName("HBO").value(), 10);
				}

				BOOST_AUTO_TEST_CASE(cant_get_channel_by_nonexistent_name)
				{
					tv.SetChannelName(10, "National Geographic");
					BOOST_CHECK(!tv.GetChannelByName("HBO"));
				}
			BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE(delete_channel_name_test)
				BOOST_AUTO_TEST_CASE(existed_channel_name_could_be_deleted)
				{
					tv.SetChannelName(35, "National Geographic");
					BOOST_CHECK_EQUAL(tv.GetChannelName(35).value(), "National Geographic");
					tv.DeleteChannelName("National Geographic");
					BOOST_CHECK(!tv.GetChannelName(35));
				}

				BOOST_AUTO_TEST_CASE(nonexistent_channel_name_could_not_be_deleted)
				{
					BOOST_CHECK(!tv.DeleteChannelName("BBC"));
				}
				
			BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
				
	struct after_subsequent_turning_on_ : when_turned_on_
	{
		after_subsequent_turning_on_()
		{
			tv.SetChannelName(20, "FOX");
			tv.SelectChannel(20);
			tv.SelectChannel(33);
			tv.TurnOff();
			tv.TurnOn();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
		}

		BOOST_AUTO_TEST_CASE(should_save_previous_channel)
		{
			tv.SelectChannel(tv.GetPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 20);
		}

		BOOST_AUTO_TEST_CASE(should_save_channel_name)
		{
			tv.SelectChannel("FOX");
			BOOST_CHECK_EQUAL(tv.GetChannel(), 20);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

	


