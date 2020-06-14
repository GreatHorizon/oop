#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"

struct Athlete
{
	Athlete(std::string name = "Ivan", float weight = 70, float height = 182)
		: m_name(name)
		, m_weight(weight)
		, m_height(height)
	{
	};

	std::string m_name;
	float m_weight;
	float m_height;
};

bool AthleteHeigthComparator(Athlete const& firstAthlete, Athlete const& secondAthlete)
{
	return std::max(firstAthlete.m_height, secondAthlete.m_height) == firstAthlete.m_height 
		? false : true;
}

bool AthleteWeigthComparator(Athlete const& firstAthlete, Athlete const& secondAthlete)
{
	return std::max(firstAthlete.m_weight, secondAthlete.m_weight) == firstAthlete.m_height
		? false : true;
}

BOOST_AUTO_TEST_SUITE(find_max_test)
	BOOST_AUTO_TEST_CASE(cant_find_max_value_when_vector_is_empty)
	{
		std::vector<int> intArray;
		int maxElement = 0;
		BOOST_CHECK(!FindMax(intArray, maxElement, std::less<int>()));
		BOOST_CHECK_EQUAL(maxElement, 0);
	}

	BOOST_AUTO_TEST_CASE(should_find_max_value_in_integer_vector)
	{
		std::vector<int> intArray {1, 9, 66, -20};
		auto maxElement = 0;
		BOOST_CHECK(FindMax(intArray, maxElement, std::less<int>()));
		BOOST_CHECK_EQUAL(maxElement, 66);
	}

	BOOST_AUTO_TEST_CASE(should_find_max_value_in_double_vector)
	{
		std::vector<double> doubleArray{ 0.335, -221.3, 6.6, 20.395 };
		double maxElement = 0;
		BOOST_CHECK(FindMax(doubleArray, maxElement, std::less<double>()));
		BOOST_CHECK_EQUAL(maxElement, 20.395);
	}

	BOOST_AUTO_TEST_CASE(should_find_max_value_in_float_vector)
	{
		std::vector<float> doubleArray{ 0.335f, -221.3f, 6.6f, 20.395f };
		float maxElement = 0;
		BOOST_CHECK(FindMax(doubleArray, maxElement, std::less<float>()));
		BOOST_CHECK_EQUAL(maxElement, 20.395f);
	}

	BOOST_AUTO_TEST_CASE(should_find_max_value_in_string_vector)
	{
		std::vector<std::string> doubleArray{ "aaa", "bbbb", "ccc"};
		std::string maxElement;
		BOOST_CHECK(FindMax(doubleArray, maxElement, std::less<std::string>()));
		BOOST_CHECK_EQUAL(maxElement, "ccc");
	}

	BOOST_AUTO_TEST_CASE(should_find_max_value_in_vector_of_char_array)
	{
		std::vector<const char*> doubleArray{ "aaa", "bbbb", "ccc" };
		const char* maxElement;

		BOOST_CHECK(FindMax(doubleArray, maxElement, [](const char* leftValue, const char* rightValue)
			{
				return std::strcmp(leftValue, rightValue) < 0 ? true : false;
			}
		));

		BOOST_CHECK_EQUAL(maxElement, "ccc");
	}

	struct AthletesFixture
	{
		const std::vector<Athlete> athletsArray
		{
			Athlete("John", 70, 180),
			Athlete("Emma", 50, 175),
			Athlete("Rick", 75, 170)
		};

		Athlete athleteWithMaxValue = Athlete();
	};

	BOOST_FIXTURE_TEST_SUITE(array_with_students, AthletesFixture)
		BOOST_AUTO_TEST_CASE(find_student_with_max_height)
		{		
			BOOST_CHECK(FindMax(athletsArray, athleteWithMaxValue, AthleteHeigthComparator));
			BOOST_CHECK_EQUAL(athleteWithMaxValue.m_name, "John");
		}

		BOOST_AUTO_TEST_CASE(find_student_with_max_weight)
		{
			BOOST_CHECK(FindMax(athletsArray, athleteWithMaxValue, AthleteWeigthComparator));
			BOOST_CHECK_EQUAL(athleteWithMaxValue.m_name, "Rick");
		}

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()