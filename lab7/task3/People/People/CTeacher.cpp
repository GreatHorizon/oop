#include "CTeacher.h"

CTeacher::CTeacher(std::string const& firstName, std::string const& lastName, 
	std::string const& patronymic, std::string const& address, std::string const& lessonName)
	: m_lessonName(lessonName)
	, CPersonImpl(firstName, lastName, patronymic, address)
{
}

std::string CTeacher::GetLessonName() const
{
	return m_lessonName;
}

void CTeacher::SetLessonName(std::string const& lessonName)
{
	m_lessonName = lessonName;
}
