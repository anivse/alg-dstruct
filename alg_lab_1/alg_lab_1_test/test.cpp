#include "pch.h"
#include "lab.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(DateCompareTest, date1_more_or_equally_to_date2) {
	person_t person1, person2;
	person2 = { "A",1,"January",2000 };
	person1 = { "A",2,"February",2002 };
	int n = DateCompare(person1, person2);
	EXPECT_TRUE(n == 1);
}

TEST(DateCompareTest, date1_less_to_date2) {
	person_t person1, person2;
	person1 = { "A",1,"January",2000 };
	person2 = { "A",2,"February",2002 };
	int n = DateCompare(person1, person2);
	EXPECT_TRUE(n == 0);
}


TEST(NumberMonthTest, return_number_of_month) {
	char month[] = "January";
	int n = NumberMonth(month);
	EXPECT_TRUE(n == 1);
}

TEST(NumberMonthTest, if_not_month_return_0) {
	char month[] = "J";
	int n = NumberMonth(month);
	EXPECT_TRUE(n == 0);
}


TEST(SearchPositionTest, search_position_is_true) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->person.fullName = "A A A"; 
	list->person.day = 1;
	list->person.month = "January";
	list->person.year = 2000;
	list->next = NULL;
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 2002;
	int n = SearchPosition(list, person);
	EXPECT_TRUE(n == 2);
}

TEST(AddPersonTest, if_list_null_create_list) {
	list_t* list = NULL;
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 2000;
	list_t* trueList = (list_t*)malloc(sizeof(list_t));
	trueList->person.fullName = "A A A";
	trueList->person.day = 1;
	trueList->person.month = "January";
	trueList->person.year = 2000;
	trueList->next = NULL;
	list = AddPerson(list, person);
	EXPECT_TRUE(strcmp(list->person.fullName, trueList->person.fullName) == 0);
	EXPECT_TRUE(strcmp(list->person.month, trueList->person.month) == 0);
	EXPECT_EQ(list->person.day, trueList->person.day);
	EXPECT_EQ(list->person.year, trueList->person.year);

}

TEST(AddPersonTest, if_position_is_1_add_in_begin_list) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->person.fullName = "A A A";
	list->person.day = 1;
	list->person.month = "January";
	list->person.year = 2000;
	list->next = NULL;
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 1999;
	list = AddPerson(list, person);
	EXPECT_TRUE(strcmp(list->person.fullName,person.fullName) == 0);
	EXPECT_TRUE(strcmp(list->person.month, person.month) == 0);
	EXPECT_EQ(list->person.day,person.day);
	EXPECT_EQ(list->person.year,person.year);
}

TEST(AddPersonTest, if_position_is_more_1_add_in_list) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->person.fullName = "A A A";
	list->person.day = 1;
	list->person.month = "January";
	list->person.year = 2000;
	list->next = NULL;
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 2001;
	list = AddPerson(list, person);
	EXPECT_TRUE(strcmp(list->next->person.fullName, person.fullName) == 0);
	EXPECT_TRUE(strcmp(list->next->person.month, person.month) == 0);
	EXPECT_EQ(list->next->person.day, person.day);
	EXPECT_EQ(list->next->person.year, person.year);
}

TEST(CheckPersonTest, if_this_date_is_eq_person_date_return_1) {
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 2000;
	int n = CheckPerson(person, 1, "January", 2000);
	EXPECT_TRUE(n == 1);
}

TEST(CheckPersonTest, if_this_date_is_no_eq_person_date_return_0) {
	person_t person;
	person.fullName = "A A A";
	person.day = 1;
	person.month = "January";
	person.year = 2000;
	int n = CheckPerson(person, 1, "February", 2000);
	EXPECT_TRUE(n == 0);
}

TEST(CheckListTest, if_this_date_is_in_list_return_number) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->person.fullName = "A A A";
	list->person.day = 1;
	list->person.month = "February";
	list->person.year = 2000;
	list->next = NULL;
	int n = CheckList(list, 1, "February", 2000);
	EXPECT_TRUE(n == 1);
}

TEST(CheckListTest, if_this_date_is_not_in_list_return_0) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->person.fullName = "A A A";
	list->person.day = 1;
	list->person.month = "February";
	list->person.year = 2000;
	list->next = NULL;
	list->next = NULL;
	int n = CheckList(list, 2, "February", 2000);
	EXPECT_TRUE(n == 0);
}
TEST(WithoutFirstTest, return_str_without_first_item) {
	char str[] = "abc\0";
	char* str1 = (char*)malloc(3 * sizeof(char));
	str1 = WithoutFirst(str);
	EXPECT_TRUE(strcmp(str1, "bc\0")==0);
}

TEST(StructureFromStringTest, structure_do_from_string) {
	char* str = "I I I January 1, 2000";
	person_t person;
	person = StructureFromString(str);
	EXPECT_TRUE(strcmp(person.fullName,"I I I")==0);
	EXPECT_TRUE(person.day == 1);
	EXPECT_TRUE(strcmp(person.month,"January")==0);
	EXPECT_TRUE(person.year == 2000);
}

TEST(StructureFromStringTest, if_not_correct_value_return_error_NULL_NULL_NULL_NULL) {
	char* str = "111";
	person_t person;
	person_t error = { NULL,NULL,NULL,NULL };
	person = StructureFromString(str);
	EXPECT_TRUE(person.day == error.day);
	EXPECT_TRUE(person.month == error.month);
	EXPECT_TRUE(person.fullName == error.fullName);
	EXPECT_TRUE(person.year == error.year);
}


TEST(ItsNameTest, if_its_name_return_1) {
	char fullName[] = "A A A";
	int n = ItsName(fullName);
	EXPECT_TRUE(n == 1);
}

TEST(ItsNameTest, if_not_name_return_0) {
	char fullName[] = "A0 A0 A0";
	int n = ItsName(fullName);
	EXPECT_TRUE(n == 0);
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::getchar(); // keep console window open until Return keystroke
}