#pragma once
#include "IPerson.h"
class ITeacher : public IPerson
{
public:
	virtual std::string GetLessonName() const = 0;
	virtual void SetLessonName(std::string const& lessonName) = 0;
};

