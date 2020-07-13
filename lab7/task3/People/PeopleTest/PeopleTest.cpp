#include "stdafx.h"
#include "../People/CPupil.h"
#include "../People/CStudent.h"
#include "../People/CTeacher.h"
#include "../People/CWorker.h"
#include "../People/CAdvancedStudent.h"

struct pupilFixture
{
	CPupil pupil;
	pupilFixture()
		: pupil("kolya", "vasin", "nikolaevich", "lebedeva 32", "¹5", "1b")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(CPupil_tests, pupilFixture)
	BOOST_AUTO_TEST_CASE(should_be_a_person)
	{
		BOOST_CHECK(static_cast<IPerson*>(&pupil));
	}
	
	BOOST_AUTO_TEST_CASE(values_can_be_set)
	{
		BOOST_CHECK_EQUAL(pupil.GetAddress(), "lebedeva 32");
		pupil.SetAddress("petrova 1");
		BOOST_CHECK_EQUAL(pupil.GetAddress(), "petrova 1");

		pupil.SetClassName("11a"); 
		BOOST_CHECK_EQUAL(pupil.GetClassName(), "11a");

		pupil.SetSchoolName("¹1");
		BOOST_CHECK_EQUAL(pupil.GetSchoolName(), "¹1");
	}
BOOST_AUTO_TEST_SUITE_END()

struct studentFixture
{
	CStudent student;
	studentFixture()
		: student("kolya", "vasin", "nikolaevich", "lebedeva 32", "112321", "kfu")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(CStudent_tests, studentFixture)
	BOOST_AUTO_TEST_CASE(should_be_a_person)
	{
		BOOST_CHECK(static_cast<IPerson*>(&student));
	}

	BOOST_AUTO_TEST_CASE(values_can_be_set)
	{
		BOOST_CHECK_EQUAL(student.GetAddress(), "lebedeva 32");
		student.SetAddress("petrova 1");
		BOOST_CHECK_EQUAL(student.GetAddress(), "petrova 1");

		student.SetUniversityName("mgu");
		BOOST_CHECK_EQUAL(student.GetUniversityName(), "mgu");

		student.SetStudentId("9877768");
		BOOST_CHECK_EQUAL(student.GetStudentId(), "9877768");
	}
BOOST_AUTO_TEST_SUITE_END()

struct teacherFixture
{
	CTeacher teacher;
	teacherFixture()
		: teacher("kolya", "vasin", "nikolaevich", "lebedeva 32", "math")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(CTeacher_tests, teacherFixture)
	BOOST_AUTO_TEST_CASE(should_be_a_person)
	{
		BOOST_CHECK(static_cast<IPerson*>(&teacher));
	}

	BOOST_AUTO_TEST_CASE(values_can_be_set)
	{
		BOOST_CHECK_EQUAL(teacher.GetAddress(), "lebedeva 32");
		teacher.SetAddress("petrova 1");
		BOOST_CHECK_EQUAL(teacher.GetAddress(), "petrova 1");

		teacher.SetLessonName("phycics");
		BOOST_CHECK_EQUAL(teacher.GetLessonName(), "phycics");
	}
BOOST_AUTO_TEST_SUITE_END()


struct workerFixture
{
	CWorker worker;
	workerFixture()
		: worker("kolya", "vasin", "nikolaevich", "lebedeva 32", "programming")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(CWorker_tests, workerFixture)
	BOOST_AUTO_TEST_CASE(should_be_a_person)
	{
		BOOST_CHECK(static_cast<IPerson*>(&worker));
	}

	BOOST_AUTO_TEST_CASE(values_can_be_set)
	{
		BOOST_CHECK_EQUAL(worker.GetFirstName(), "kolya");
		worker.SetFirstName("Vanya");
		BOOST_CHECK_EQUAL(worker.GetFirstName(), "Vanya");

		worker.SetLastName("Vanin");
		BOOST_CHECK_EQUAL(worker.GetLastName(), "Vanin");

		worker.SetPatronymic("petrovich");
		BOOST_CHECK_EQUAL(worker.GetPatronymic(), "petrovich");


		worker.SetSpecialisation("mechanic");
		BOOST_CHECK_EQUAL(worker.GetSpecialisation(), "mechanic");
	}
BOOST_AUTO_TEST_SUITE_END()


struct advancedStudentFixture
{
	CAdvancedStudent advancedStudent;
	advancedStudentFixture()
		: advancedStudent("kolya", "vasin", "nikolaevich", "lebedeva 32", "12312", "mgu", "math")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(CAdvancedStudent_tests, advancedStudentFixture)
	BOOST_AUTO_TEST_CASE(should_be_a_person)
	{
		BOOST_CHECK(static_cast<IPerson*>(&advancedStudent));
	}

	BOOST_AUTO_TEST_CASE(should_be_a_student)
	{
		BOOST_CHECK(static_cast<IStudent*>(&advancedStudent));
	}

BOOST_AUTO_TEST_CASE(values_can_be_set)
{
	advancedStudent.SetDissertationSubject("mechanic");
	BOOST_CHECK_EQUAL(advancedStudent.GetDissertationSubject(), "mechanic");
}
BOOST_AUTO_TEST_SUITE_END()