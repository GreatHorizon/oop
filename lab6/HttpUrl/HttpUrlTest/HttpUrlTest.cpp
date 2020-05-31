#include "stdafx.h"
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"
#include <string>
#include <map>
#include <regex>
#include <math.h>


using namespace std;

enum class Protocol;

template <typename Ex, typename Fn>
void ExpectException(Fn&& fn, const std::string& expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
		});
}

template <typename Ex>
void ExpectConstructorFailure(std::string const& url, std::string const& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(url);
		}, expectedDescription);
}


BOOST_AUTO_TEST_SUITE(parsing_constructor_test)
	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_url_is_incorrect)
	{
		ExpectConstructorFailure<std::invalid_argument>("asdasd", "Invalid url\n");
	}
	
	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_port_is_incorrect)
	{
		ExpectConstructorFailure<std::invalid_argument>("fto://vk.com:1234567",
			"Invalid protocol\nIt should be http or https\n");
	}

	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_port_out_of_range)
	{
		ExpectConstructorFailure<std::invalid_argument>("http://vk.com:1234567",
			"Invalid port\nIt should be number from 1 to 65535\n");
		ExpectConstructorFailure<std::invalid_argument>("http://vk.com:0",
			"Invalid port\nIt should be number from 1 to 65535\n");
	}

	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_domain_contains_incorrect_symbols)
	{
		ExpectConstructorFailure<std::invalid_argument>("http://vk&^3.com:1234567",
			"Domain should contain only a-z, A-Z, 0-9, \'.\', \'-\'\n");
	}

	BOOST_AUTO_TEST_CASE(should_construct_object_when_url_is_correct)
	{
		CHttpUrl url("http://vk.com:339/news");

		BOOST_CHECK_EQUAL(url.GetDocument(), "news");
		BOOST_CHECK_EQUAL(url.GetPort(), 339);
		BOOST_CHECK_EQUAL(url.GetDomain(), "vk.com");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

	BOOST_AUTO_TEST_CASE(should_set_default_port_when_it_was_not_specified)
	{
		CHttpUrl url("https://vk.com/news");

		BOOST_CHECK_EQUAL(url.GetDocument(), "news");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetDomain(), "vk.com");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTPS);
	}
	
BOOST_AUTO_TEST_SUITE_END();


template <typename Ex>
void ExpectConstructorWithPartOfParsedElementsFailure(
	std::string const& domain, std::string const& document, Protocol protocol, std::string const& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(domain, document, protocol);
		}, expectedDescription);
}

BOOST_AUTO_TEST_SUITE(constructor_with_part_of_parsed_parameters_test)

	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_domain_contains_incorrect_symbols)
	{
		ExpectConstructorWithPartOfParsedElementsFailure<invalid_argument>(
		"vk.com^^^^", "news", Protocol::HTTP, "Domain should contain only a-z, A-Z, 0-9, \'.\', \'-\'\n");
		
		ExpectConstructorWithPartOfParsedElementsFailure<invalid_argument>(
		"фвфыв", "news", Protocol::HTTP, "Domain should contain only a-z, A-Z, 0-9, \'.\', \'-\'\n");
	}

	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_domain_is_empty)
	{
		ExpectConstructorWithPartOfParsedElementsFailure<invalid_argument>(
			"", "news", Protocol::HTTP, "Domain should not be empty\n");
	}

	BOOST_AUTO_TEST_CASE(should_construct_object_when_url_is_correct)
	{
		CHttpUrl url("vk.com", "news", Protocol::HTTP);

		BOOST_CHECK_EQUAL(url.GetDocument(), "/news");
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
		BOOST_CHECK_EQUAL(url.GetDomain(), "vk.com");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

	BOOST_AUTO_TEST_CASE(should_not_add_shash_to_document_if_it_was_added)
	{
		CHttpUrl url("vk.com", "/news", Protocol::HTTP);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/news");
	}

BOOST_AUTO_TEST_SUITE_END();

template <typename Ex>
void ExpectConstructorWithAlltOfParsedElementsFailure(
	std::string const& domain, std::string const& document, Protocol protocol, 
	unsigned short port, std::string const& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(domain, document, protocol, port);
		}, expectedDescription);
}

BOOST_AUTO_TEST_SUITE(constructor_with_all_of_parsed_parameters_test)
	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_domain_is_empty)
	{
		ExpectConstructorWithAlltOfParsedElementsFailure<invalid_argument>(
		"", "news", Protocol::HTTP, 999, "Domain should not be empty\n");
	}

	BOOST_AUTO_TEST_CASE(should_throw_exeption_when_domain_contains_incorrect_symbols)
	{
		ExpectConstructorWithPartOfParsedElementsFailure<invalid_argument>(
			"^^^^", "news", Protocol::HTTP, "Domain should contain only a-z, A-Z, 0-9, \'.\', \'-\'\n");
	}

	BOOST_AUTO_TEST_CASE(should_construct_object_when_url_is_correct)
	{
		CHttpUrl url("vk.com", "news", Protocol::HTTP, 339);

		BOOST_CHECK_EQUAL(url.GetDocument(), "/news");
		BOOST_CHECK_EQUAL(url.GetPort(), 339);
		BOOST_CHECK_EQUAL(url.GetDomain(), "vk.com");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(get_url_test)
	BOOST_AUTO_TEST_CASE(should_show_whole_url)
	{
		CHttpUrl urlWithDefaultPort("en.cppreference.com", "w/cpp/string/basic_string", Protocol::HTTPS, 124);
		std::string expectedString("https://en.cppreference.com:124/w/cpp/string/basic_string");
		BOOST_CHECK_EQUAL(urlWithDefaultPort.GetURL(), expectedString);
	}

	BOOST_AUTO_TEST_CASE(should_not_show_default_port)
	{
		CHttpUrl urlWithDefaultPort("en.cppreference.com", "w/cpp/string/basic_string", Protocol::HTTP);
		std::string expectedString("http://en.cppreference.com/w/cpp/string/basic_string");
		BOOST_CHECK_EQUAL(urlWithDefaultPort.GetURL(), expectedString);
	}
	
	BOOST_AUTO_TEST_CASE(should_show_url_without_document_was_not_specified)
	{
		CHttpUrl urlWithDefaultPort("en.cppreference.com", "", Protocol::HTTPS);
		std::string expectedString("https://en.cppreference.com/");
		BOOST_CHECK_EQUAL(urlWithDefaultPort.GetURL(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END();
