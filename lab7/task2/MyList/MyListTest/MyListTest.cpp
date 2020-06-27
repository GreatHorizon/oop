#include "stdafx.h"
#include "../MyList/CMyList.h"


struct EmptyIntList
{
	CMyList<int> list;
};

BOOST_FIXTURE_TEST_SUITE(My_list, EmptyIntList)
	
	BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(should_be_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(cant_get_last)
		{
			BOOST_CHECK_THROW(list.GetBackElement(), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(cant_get_first_elementy)
		{
			BOOST_CHECK_THROW(list.GetBeginElement(), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(cant_delete_first_sentinel_node)
		{
			auto it = list.rend();
			BOOST_CHECK_THROW(list.Delete(it), std::runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_elements_appending)

		BOOST_AUTO_TEST_CASE(should_not_be_empty)
		{
			size_t oldSize = list.GetSize();
			list.Append(1);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			BOOST_CHECK(!list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(should_increase_its_size_by_1)
		{
			size_t oldSize = list.GetSize();
			list.Append(1);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);

			oldSize = list.GetSize();
			list.Append(1);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append(1);
			BOOST_CHECK_EQUAL(list.GetBackElement(), 1);
			list.Append(2);
			BOOST_CHECK_EQUAL(list.GetBackElement(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_elements_prepending)
		BOOST_AUTO_TEST_CASE(should_not_be_empty)
		{
			size_t oldSize = list.GetSize();
			list.Prepend(2);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);

			oldSize = list.GetSize();
			list.Prepend(1);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(should_increase_its_size_by_1)
		{
			size_t oldSize = list.GetSize();
			list.Prepend(1);

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBeginElement_method)
		{
			list.Prepend(1);
			BOOST_CHECK_EQUAL(list.GetBeginElement(), 1);
			list.Prepend(2);
			BOOST_CHECK_EQUAL(list.GetBeginElement(), 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(insert)
		BOOST_AUTO_TEST_CASE(cant_insert_before_first_sentinel_node)
		{
			auto it = list.rend();
			BOOST_CHECK_THROW(list.Insert(it, 12), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(can_insert_before_second_sentinel_node)
		{
			auto it = list.end();
			list.Insert(it, 12);
			BOOST_CHECK(*list.back() == 12);
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_first_element)
		{
			list.Append(1);
			list.Append(2);
			auto it = list.begin();
			list.Insert(it, 3);
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			BOOST_CHECK(*list.begin() == 3);
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_last_element)
		{
			list.Append(1);
			list.Append(2);
			auto it = list.back();
			list.Insert(it, 3);
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			BOOST_CHECK(*--list.back() == 3);
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_element_in_the_middle_of_list)
		{
			list.Append(1);
			list.Append(2);
			list.Append(3);
			auto it = list.back();
			--it;
			list.Insert(it, 4);
			BOOST_CHECK_EQUAL(list.GetSize(), 4);
			BOOST_CHECK(*++list.begin() == 4);
		}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(delete_element)

		BOOST_AUTO_TEST_CASE(cant_delete_first_sentinel_node)
		{
			list.Append(1);
			auto it = list.rend();
			BOOST_CHECK_THROW(list.Delete(it), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(cant_delete_second_sentinel_node)
		{
			list.Append(1);
			auto it = list.end();
			BOOST_CHECK_THROW(list.Delete(it), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(can_delete_element_when_list_size_is_1)
		{
			list.Append(1);
			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			auto it = list.back();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 0);
		}

		BOOST_AUTO_TEST_CASE(can_delete_last_element)
		{
			list.Append(1);
			list.Append(2);
			auto it = list.back();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			BOOST_CHECK_EQUAL(*list.back(), 1);
		}

		BOOST_AUTO_TEST_CASE(can_delete_first_element)
		{
			list.Append(1);
			list.Append(2);
			auto it = list.begin();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			BOOST_CHECK_EQUAL(*list.begin(), 2);
		}

		BOOST_AUTO_TEST_CASE(can_delete_element_in_the_middle_of_list)
		{
			list.Append(1);
			list.Append(2);
			list.Append(3);
			auto it = list.begin();
			list.Delete(++it);

			BOOST_CHECK_EQUAL(list.GetSize(), 2);
			auto newIt = list.begin();
			++newIt;
			BOOST_CHECK_EQUAL(*newIt, 3);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_elements_were_specified_ : EmptyIntList
	{
		when_elements_were_specified_()
		{
			list.Append(1);
			list.Append(2);
			list.Append(3);
			list.Append(4);
			list.Append(5);
			list.Append(6);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(copy_and_move, when_elements_were_specified_)
		BOOST_AUTO_TEST_CASE(can_copy_list)
		{
			CMyList secondList(list);
			BOOST_CHECK_EQUAL(secondList.GetSize(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBackElement(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBeginElement(), 1);
		}

		BOOST_AUTO_TEST_CASE(can_assign_list_to_other_list)
		{
			CMyList<int> secondList;
			secondList = list;

			BOOST_CHECK_EQUAL(secondList.GetSize(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBackElement(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBeginElement(), 1);
		}

		BOOST_AUTO_TEST_CASE(can_move_from_one_list_to_other_list)
		{
			CMyList<int> secondList;
			secondList = std::move(list);

			BOOST_CHECK_EQUAL(secondList.GetSize(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBackElement(), 6);
			BOOST_CHECK_EQUAL(secondList.GetBeginElement(), 1);

			BOOST_CHECK_EQUAL(list.GetSize(), 0);
			BOOST_CHECK_THROW(list.GetBackElement(), std::runtime_error);
			BOOST_CHECK_THROW(list.GetBeginElement(), std::runtime_error);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(itrators, when_elements_were_specified_)
		BOOST_AUTO_TEST_CASE(can_be_incremented)
	{
		auto it = list.begin();
		BOOST_CHECK_EQUAL(*it, 1);
		++it;
		BOOST_CHECK_EQUAL(*it, 2);
	}

	BOOST_AUTO_TEST_CASE(can_be_incrementing_when_it_is_last_element)
	{
		auto it = list.back();
		++it;
		BOOST_CHECK(it == list.end());
	}

	BOOST_AUTO_TEST_CASE(can_be_decremented)
	{
		auto it = list.back();
		BOOST_CHECK_EQUAL(*it, 6);
		--it;
		BOOST_CHECK_EQUAL(*it, 5);
	}

	BOOST_AUTO_TEST_CASE(cant_be_decremented_when_it_is_iterator_with_second_sentinel_node)
	{
		auto it = list.end();
		BOOST_CHECK_THROW(++it, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_be_incremented_when_it_is_iterator_with_second_sentinel_node)
	{
		auto it = list.end();
		--it;
		BOOST_CHECK_EQUAL(*it, 6);
	}

	BOOST_AUTO_TEST_CASE(cant_be_decremented_when_it_is_iterator_with_first_sentinel_node)
	{
		auto it = list.begin();
		--it;
		BOOST_CHECK_THROW(--it, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(cant_be_dereferensed_when_it_is_empty_iterator)
	{
		auto it = list.end();
		BOOST_CHECK_THROW(*it, std::runtime_error);
	}

	BOOST_AUTO_TEST_CASE(can_be_checked_for_equality)
	{
		auto it1 = list.begin();
		auto it2 = list.begin();
		BOOST_CHECK(it1 == it2);
	}

	BOOST_AUTO_TEST_CASE(can_be_checked_for_nequality)
	{
		auto it1 = list.begin();
		auto it2 = list.back();
		BOOST_CHECK(it1 != it2);
	}

	BOOST_AUTO_TEST_CASE(can_be_checked_for_equality_when_iterator_is_empty)
	{
		auto it1 = list.begin();
		auto it2 = list.end();
		BOOST_CHECK_EQUAL(it1 == it2, false);
	}

	BOOST_AUTO_TEST_CASE(can_be_used_with_range_based_for)
	{
		std::vector<int> receivedList;
		std::vector<int> expectedList{ 1, 2, 3, 4, 5, 6};

		for (auto it : list)
		{
			receivedList.push_back(it);
		}

		BOOST_CHECK_EQUAL_COLLECTIONS(receivedList.begin(), receivedList.end(),
			expectedList.begin(), expectedList.end());
	}

	BOOST_AUTO_TEST_SUITE(reversed_iterator)
		BOOST_AUTO_TEST_CASE(can_get_last_element_via_rbegin)
		{
			BOOST_CHECK_EQUAL(*list.rbegin(), 6);
		}

		BOOST_AUTO_TEST_CASE(can_get_first_element_via_rbegin)
		{
			BOOST_CHECK_EQUAL(*list.rback(), 1);
		}

		BOOST_AUTO_TEST_CASE(can_be_incremented)
		{
			auto it = list.rbegin();
			BOOST_CHECK_EQUAL(*it, 6);
			++it;
			BOOST_CHECK_EQUAL(*it, 5);
		}

		BOOST_AUTO_TEST_CASE(can_be_decremented)
		{
			auto it = list.rback();
			BOOST_CHECK_EQUAL(*it, 1);
			--it;
			BOOST_CHECK_EQUAL(*it, 2);
		}

		BOOST_AUTO_TEST_CASE(can_be_decremented_when_it_is_first_element)
		{
			auto it = list.rend();
			BOOST_CHECK_EQUAL(*--it, 1);
		}

		BOOST_AUTO_TEST_CASE(cant_be_incremented_when_its_iterator_with_first_sentinel_node)
		{
			auto it = list.rend();
			BOOST_CHECK_THROW(++it, std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(cant_be_decremented_when_its_iterator_with_second_sentinel_node)
		{
			auto it = list.rbegin();
			--it;
			BOOST_CHECK_THROW(--it, std::runtime_error);
		}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct StringList
{
	CMyList<std::string> list;
	StringList()
	{
		list.Append("1");
		list.Append("2");
		list.Append("3");
		list.Append("4");
		list.Append("5");
		list.Append("6");
	}
	
};

BOOST_FIXTURE_TEST_SUITE(My_string_list, StringList)
	BOOST_AUTO_TEST_SUITE(string_list_test)
		BOOST_AUTO_TEST_CASE(element_can_be_added_to_the_list)
		{
			list.Prepend("0");
			BOOST_CHECK_EQUAL(*list.begin(), "0");

			list.Append("7");
			BOOST_CHECK_EQUAL(*list.back(), "7");

			auto it = list.begin();
			++++it;

			list.Insert(it, "-1");
			BOOST_CHECK_EQUAL(*++++list.begin(), "-1");
		}

		BOOST_AUTO_TEST_CASE(can_get_first_and_last_elements)
		{
			BOOST_CHECK_EQUAL(list.GetBackElement(), "6");
			BOOST_CHECK_EQUAL(list.GetBeginElement(), "1");
		}

		BOOST_AUTO_TEST_CASE(can_delete_elements)
		{
			auto it = list.begin();
			list.Delete(it);
		
			BOOST_CHECK_EQUAL(*list.begin(), "2");

			it = list.back();
			list.Delete(it);
			BOOST_CHECK_EQUAL(*list.back(), "5");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()