#include "stdafx.h"
#include "../StringList/CStringList.h"


using namespace std;

struct EmptyStringList
{
	CStringList list;
};

class CStringList::CIterator;

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

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

		BOOST_AUTO_TEST_CASE(cant_delete_element)
		{
			auto it = list.begin();
			BOOST_CHECK_THROW(list.Delete(it), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(should_not_change_list_when_its_empty)
		{
			list.Clear();
			BOOST_CHECK_EQUAL(list.GetSize(), 0);
			BOOST_CHECK(list.begin() == list.end());
			BOOST_CHECK(list.back() == list.end());
		}		
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_elements_appending)

		BOOST_AUTO_TEST_CASE(should_not_be_empty)
		{
			size_t oldSize = list.GetSize();
			list.Append("Cat");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			BOOST_CHECK(!list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(should_increase_its_size_by_1)
		{
			size_t oldSize = list.GetSize();
			list.Append("Cat");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);

			oldSize = list.GetSize();
			list.Append("Dog");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("Cat");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "Cat");
			list.Append("Dog");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "Dog");
		}
		
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_last_element)
		{
			list.Append("Dog");
			BOOST_CHECK_EQUAL(addressof(*list.back()), addressof(list.GetBackElement()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_elements_prepending)
		BOOST_AUTO_TEST_CASE(should_not_be_empty)
		{	
			size_t oldSize = list.GetSize();
			list.Prepend("Cat");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);

			oldSize = list.GetSize();
			list.Prepend("Dog");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(should_increase_its_size_by_1)
		{
			size_t oldSize = list.GetSize();
			list.Prepend("Cat");

			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBeginElement_method)
		{
			list.Prepend("Cat");
			BOOST_CHECK_EQUAL(list.GetBeginElement(), "Cat");
			list.Prepend("Dog");
			BOOST_CHECK_EQUAL(list.GetBeginElement(), "Dog");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Prepend("Cat");
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.GetBeginElement()));
		}

	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(delete_element)

		BOOST_AUTO_TEST_CASE(cant_delete_element_with_empty_iterator)
		{
			list.Append("dog");
			auto it = list.end();

			BOOST_CHECK_THROW(list.Delete(it), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(can_delete_element_when_list_size_is_1)
		{
			list.Append("Fox");
			auto it = list.back();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 0);
			BOOST_CHECK(list.back() == list.end());
		}

		BOOST_AUTO_TEST_CASE(can_delete_last_element)
		{
			list.Append("Fox");
			list.Append("Cat");
			auto it = list.back();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			BOOST_CHECK_EQUAL(*list.back(), "Fox");
		}

		BOOST_AUTO_TEST_CASE(can_delete_first_element)
		{
			list.Append("Fox");
			list.Append("Cat");
			auto it = list.begin();
			list.Delete(it);

			BOOST_CHECK_EQUAL(list.GetSize(), 1);
			BOOST_CHECK_EQUAL(*list.begin(), "Cat");
		}

		BOOST_AUTO_TEST_CASE(can_delete_element_in_the_middle_of_list)
		{
			list.Append("Fox");
			list.Append("Apple");
			list.Append("Cat");
			auto it = list.begin();
			list.Delete(++it);

			BOOST_CHECK_EQUAL(list.GetSize(), 2);
			auto newIt = list.begin();
			++newIt;
			BOOST_CHECK_EQUAL(*newIt, "Cat");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(clear_list)
		BOOST_AUTO_TEST_CASE(should_delete_all_elements_from_list)
		{
			list.Prepend("Dog");
			list.Prepend("Rat");
			list.Prepend("Cat");
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			BOOST_CHECK_EQUAL(*list.begin(), "Cat");

			list.Clear();
			BOOST_CHECK_EQUAL(list.GetSize(), 0);
			BOOST_CHECK(list.begin() == list.end());
			BOOST_CHECK(list.back() == list.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(insert)
		BOOST_AUTO_TEST_CASE(cant_insert_when_it_is_empty_iterator)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(list.Insert(it, "Dog"), std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_first_element)
		{
			list.Append("Dog");
			list.Append("Cat");
			auto it = list.begin();
			list.Insert(it, "Frog");
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			BOOST_CHECK(*list.begin() == "Frog");
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_last_element)
		{
			list.Append("Dog");
			list.Append("Cat");
			auto it = list.back();
			list.Insert(it, "Frog");
			BOOST_CHECK_EQUAL(list.GetSize(), 3);
			BOOST_CHECK(*list.back() == "Frog");
		}

		BOOST_AUTO_TEST_CASE(can_insert_when_it_is_element_in_the_middle_of_list)
		{
			list.Append("Dog");
			list.Append("Cat");
			list.Append("Fox");
			auto it = list.back();
			--it;
			list.Insert(it, "Frog");
			BOOST_CHECK_EQUAL(list.GetSize(), 4);
			BOOST_CHECK(*++list.begin() == "Frog");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_elements_were_specified_ : EmptyStringList
	{
		when_elements_were_specified_()
		{
			list.Append("Dog");
			list.Append("Cat");
			list.Append("Frog");
			list.Append("Snake");
			list.Append("Turtle");
			list.Append("Mouse");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(itrators, when_elements_were_specified_)
		BOOST_AUTO_TEST_CASE(can_be_incremented)
		{
			auto it = list.begin();
			BOOST_CHECK_EQUAL(*it, "Dog");
			++it;
			BOOST_CHECK_EQUAL(*it, "Cat");
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
			BOOST_CHECK_EQUAL(*it, "Mouse");
			--it;
			BOOST_CHECK_EQUAL(*it, "Turtle");
		}
	
		BOOST_AUTO_TEST_CASE(cant_be_decremented_when_it_is_empty_iterator)
		{
			auto it = list.end();
			BOOST_CHECK_THROW(++it, std::runtime_error);
		}

		BOOST_AUTO_TEST_CASE(cant_be_incremented_when_it_is_empty_iterator)
		{
			auto it = list.end();
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
			std::vector<std::string> receivedList;
			std::vector<std::string> expectedList{ "Dog", "Cat","Frog", "Snake", "Turtle", "Mouse"};

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
				BOOST_CHECK_EQUAL(*list.rbegin(), "Mouse");
			}
			
			BOOST_AUTO_TEST_CASE(can_get_first_element_via_rbegin)
			{
				BOOST_CHECK_EQUAL(*list.rback(), "Dog");
			}

			BOOST_AUTO_TEST_CASE(can_be_incremented)
			{
				auto it = list.rbegin();
				BOOST_CHECK_EQUAL(*it, "Mouse");
				++it;
				BOOST_CHECK_EQUAL(*it, "Turtle");
			}

			BOOST_AUTO_TEST_CASE(can_be_decremented)
			{
				auto it = list.rback();
				BOOST_CHECK_EQUAL(*it, "Dog");
				--it;
				BOOST_CHECK_EQUAL(*it, "Cat");
			} 

			BOOST_AUTO_TEST_CASE(can_be_decremented_when_it_is_first_element)
			{
				auto it = list.begin();
				--it;
				BOOST_CHECK(it == list.rend());
			}

			BOOST_AUTO_TEST_CASE(cant_be_decremented_when_its_empty_iterator)
			{
				auto it = list.rend();
				BOOST_CHECK_THROW(--it, std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END();

