#pragma once
#include "CPersonImpl.h"
#include "ITeacher.h"
class CTeacher final : public CPersonImpl<ITeacher>
{
public:
	CTeacher(std::string const& firstName, std::string const& lastName,
		std::string const& patronymic, std::string const& address, std::string const& lessonName);
	std::string GetLessonName() const override;
	void SetLessonName(std::string const& lessonName) override;
private:
	std::string m_lessonName;
};

