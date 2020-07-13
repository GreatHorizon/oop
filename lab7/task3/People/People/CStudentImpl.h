#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	std::string GetUniversityName() const override;
	std::string GetStudentId() const override;
	void SetUniversityName(std::string const& universityName);
	void SetStudentId(std::string const& studentId);
	CStudentImpl(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address, std::string const& studentId,
		std::string const& universityName);

private:
	std::string m_universityName;
	std::string m_studentId;
};

template<typename Base>
inline std::string CStudentImpl<Base>::GetUniversityName() const
{
	return m_universityName;
}

template<typename Base>
inline std::string CStudentImpl<Base>::GetStudentId() const
{
	return m_studentId;
}

template<typename Base>
inline void CStudentImpl<Base>::SetUniversityName(std::string const& universityName)
{
	m_universityName = universityName;
}

template<typename Base>
inline void CStudentImpl<Base>::SetStudentId(std::string const& studentId)
{
	m_studentId = studentId;
}

template<typename Base>
inline CStudentImpl<Base>::CStudentImpl(std::string const& firstName, std::string const& lastName,
	std::string const& patronymic, std::string const& address, std::string const& studentId,
	std::string const& universityName)
	: m_studentId(studentId)
	, m_universityName(universityName)
	, CPersonImpl<Base>(firstName, lastName, patronymic, address)
{
};
