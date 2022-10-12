#include <gtest/gtest.h>
#include "logicalElement.h"




////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/* TEST (группа тестов, вид теста)
Утверждения, порождающие в случае их ложности критические отказы начинаются с ASSERT_
Утверждения, порождающие в случае их ложности некритические отказы начинаются с EXPECT_

Простейшие логические

ASSERT_TRUE(condition);
ASSERT_FALSE(condition);


Сравнение

ASSERT_EQ(expected, actual); — =
ASSERT_NE(val1, val2); — !=
ASSERT_LT(val1, val2); — <
ASSERT_LE(val1, val2); — <=
ASSERT_GT(val1, val2); — >
ASSERT_GE(val1, val2); — >=

Сравнение строк

ASSERT_STREQ(expected_str, actual_str);
ASSERT_STRNE(str1, str2);
ASSERT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
ASSERT_STRCASENE(str1, str2); — регистронезависимо

Проверка на исключения

ASSERT_THROW(statement, exception_type);
ASSERT_ANY_THROW(statement);
ASSERT_NO_THROW(statement);


Сравнение чисел с плавающей точкой

ASSERT_FLOAT_EQ(expected, actual); — неточное сравнение float
ASSERT_DOUBLE_EQ(expected, actual); — неточное сравнение double
ASSERT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает погрешность abs_error


Вызов отказа или успеха

SUCCEED();
FAIL();
ADD_FAILURE();
ADD_FAILURE_AT(«file_path», line_number);
 */