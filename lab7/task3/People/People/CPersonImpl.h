#pragma once
#include "IPerson.h"

template <typename Base>
class CPersonImpl : public Base
{
public:
	std::string GetFirstName() const override;
	std::string GetLastName() const override;
	std::string GetPatronymic() const override;
	std::string GetAddress() const override;

	void SetFirstName(std::string const& firstName) override;
	void SetLastName(std::string const& lastName) override;
	void SetPatronymic(std::string const& patronymic) override;
	void SetAddress(std::string const& address) override;

	CPersonImpl() = default;
	CPersonImpl(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address);

private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_patronymic;
	std::string m_address;
};

template<typename Base>
inline std::string CPersonImpl<Base>::GetFirstName() const
{
	return m_firstName;
}

template<typename Base>
inline std::string CPersonImpl<Base>::GetLastName() const
{
	return m_lastName;
}

template<typename Base>
inline std::string CPersonImpl<Base>::GetPatronymic() const
{
	return m_patronymic;
}

template<typename Base>
inline std::string CPersonImpl<Base>::GetAddress() const
{
	return m_address;
}

template<typename Base>
inline void CPersonImpl<Base>::SetFirstName(std::string const& firstName)
{
	m_firstName = firstName;
}

template<typename Base>
inline void CPersonImpl<Base>::SetLastName(std::string const& lastName)
{
	m_lastName = lastName;
}

template<typename Base>
inline void CPersonImpl<Base>::SetPatronymic(std::string const& patronymic)
{
	m_patronymic = patronymic;
}

template<typename Base>
inline void CPersonImpl<Base>::SetAddress(std::string const& address)
{
	m_address = address;
}

template<typename Base>
inline CPersonImpl<Base>::CPersonImpl(std::string const& firstName,
	std::string const& lastName, std::string const& patronymic,
	std::string const& address)
	: m_firstName(firstName)
	, m_lastName(lastName)
	, m_patronymic(patronymic)
	, m_address(address)
{
};
