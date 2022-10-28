#include <gtest/gtest.h>
#include "logicalElement.h"
//#define dynamic

/////////////////////////////constructors////////////////////

TEST(default_constructor, good) {
	logicalElement a;
	char s1 = a.getSignal(1);
	char s2 = a.getSignal(2);
	size_t c = a.getCurrsize();
	ASSERT_EQ('X', s1);
	ASSERT_EQ('X', s2);
	ASSERT_EQ(2, c);
}

TEST(nums_conctructor, good) {
	logicalElement a(2,2);
	char s1 = a.getSignal(1);
	char s2 = a.getSignal(2);
	char s3 = a.getSignal(3);
	char s4 = a.getSignal(4);
	size_t c = a.getCurrsize();
	ASSERT_EQ('X', s1);
	ASSERT_EQ('X', s2);
	ASSERT_EQ('X', s3);
	ASSERT_EQ('X', s4);
	ASSERT_EQ(4, c);
}
#ifndef dynamic
TEST(nums_conctructor, bad) {
	ASSERT_ANY_THROW(logicalElement a(6,6));
}

TEST(array_conctructor, bad) {
	clamp arr[15];
	ASSERT_ANY_THROW(logicalElement b(arr,15));
}
#endif

TEST(array_constructor, good) {
	clamp arr[5];
	logicalElement a(5, 0);
	logicalElement b(arr, 5);
	ASSERT_EQ(true, a==b);
}

TEST(copy_concstructor, good) {
    logicalElement a(2,2);
    logicalElement b(a);
    ASSERT_EQ(true, a==b);
    ASSERT_EQ(4, b.getCurrsize());
    clamp v1{true};
    clamp v2{false};
    ASSERT_EQ(true, v1==b[1]);
    ASSERT_EQ(true, v1==b[1]);
    ASSERT_EQ(true, v2==b[2]);
    ASSERT_EQ(true, v2==b[3]);
}

TEST(assign, good) {
    logicalElement a(2,2);
    logicalElement b;
    b = a;
    ASSERT_EQ(true, a==b);
}

#ifdef dynamic
TEST(move_constructor, good) {
    logicalElement a(2,2);
    logicalElement b(a);
    logicalElement c = std::move(a);
    ASSERT_EQ(true, c==b);
    ASSERT_EQ(0, a.getCurrsize());
}
#endif

///////////////////////setters//////////////////////////

TEST(setSignal1, good) {
	logicalElement a;
	ASSERT_NO_THROW(a.setSignal("10"));
}

TEST(setSignal1, bad) {
	logicalElement a;
	ASSERT_ANY_THROW(a.setSignal("hgkhjhk"));
}

TEST(setSignal2, good) {
	logicalElement a;
	ASSERT_NO_THROW(a.setSignal('1',1));
}

TEST(setSignal2, bad_num1) {
	logicalElement a;
	ASSERT_ANY_THROW(a.setSignal('1', 0));
}

TEST(setSignal2, bad_num2) {
	logicalElement a;
	ASSERT_ANY_THROW(a.setSignal('1', 5));
}

TEST(setSignal2, bad_value){
	logicalElement a;
	ASSERT_ANY_THROW(a.setSignal('3', 1));
}

TEST(getSignal, bad1) {
	logicalElement a;
	ASSERT_ANY_THROW(a.getSignal(5));
}

TEST(getSignal, bad2) {
	logicalElement a;
	ASSERT_ANY_THROW(a.getSignal(0));
}

////////////////////addConnections/////////////////////

TEST(addConnection, good) {
	logicalElement a;
	logicalElement b;
	a.setSignal('1', 1);
	ASSERT_NO_THROW(a.addConnection(b, true));
	ASSERT_EQ('1',b.getSignal(2));
}

TEST(addConnection, equalelements) {
	logicalElement a;
	ASSERT_ANY_THROW(a.addConnection(a,true));
}

//////////////////deleteConnection/////////////////////

TEST(deleteConnection, equalelements) {
	logicalElement a;
	ASSERT_ANY_THROW(a.deleteConnection(a));
}

TEST(deleteConnection, not_connected) {
	logicalElement a;
	logicalElement b;
	ASSERT_ANY_THROW(a.deleteConnection(b));
}

TEST(deleteConnection, good) {
	logicalElement a;
	logicalElement b;
	a.setSignal('1', 1);
	ASSERT_NO_THROW(a.addConnection(b, true));
	ASSERT_NO_THROW(a.deleteConnection(b));
	ASSERT_EQ('X',b.getSignal(1));
}

///////////////////////operation+////////////////////////

TEST(plus_logE, good) {
	logicalElement b;
	logicalElement c;
	logicalElement a;
	ASSERT_NO_THROW(a=b+c);
	logicalElement d(1,1);
	clamp clamp1{true};
	clamp clamp2{false};
	ASSERT_NO_THROW(d+=clamp1);
	ASSERT_NO_THROW(d+=clamp2);
	ASSERT_EQ(true, a==d);
}

#ifndef dynamic
TEST(plus_logE, bad) {
	logicalElement b(8,0);
	logicalElement a(8,0);
	logicalElement c;
	ASSERT_ANY_THROW(c = a+b);
}
#endif

TEST(plus_clamp, good) {
	logicalElement a;
	logicalElement b(2,1);
	clamp value(false);
	ASSERT_NO_THROW(a = b+value);
	logicalElement c(2,2);
	ASSERT_EQ(true, a==c);
}

#ifndef dynamic
TEST(plus_clamp, bad) {
	logicalElement a;
	logicalElement b(9,0);
	clamp value(true);
	ASSERT_ANY_THROW(a = b+value);
}
#endif

/////////////////////operation!////////////////////////

TEST(invert, good) {
	logicalElement a;
	logicalElement b;
	b.setSignal('0',1);
	b.setSignal('1',2);
	a.setSignal('1',1);
	a.setSignal('0',2);
	ASSERT_EQ(true, a!=b);
}

/////////////////////operation+=/////////////////////

TEST(pluseq_logE, good) {
	logicalElement b;
	logicalElement a;
	ASSERT_NO_THROW(a+=b);
	logicalElement d(1,1);
	clamp clamp1{true};
	clamp clamp2{false};
	ASSERT_NO_THROW(d+=clamp1);
	ASSERT_NO_THROW(d+=clamp2);
	ASSERT_EQ(true, a==d);
}

#ifndef dynamic
TEST(pluseq_logE, bad) {
	logicalElement b(8,0);
	logicalElement a(4,0);
	ASSERT_ANY_THROW(a+=b);
}
#endif

TEST(pluseq_clamp, good) {
	logicalElement a;
	clamp value(false);
	ASSERT_NO_THROW(a += value);
	logicalElement c(1,2);
	ASSERT_EQ(true, a==c);
}

#ifndef dynamic
TEST(pluseq_clamp, bad) {
	logicalElement a(9,0);
	clamp value(true);
	ASSERT_ANY_THROW(a += value);
}
#endif

////////////////////////////operator[]/////////////////

TEST(index, bad) {
	logicalElement a;
	ASSERT_ANY_THROW(a[3]);
}

TEST(index, good1) {
	logicalElement a;
	ASSERT_NO_THROW(a[1]);
	clamp value(true);
	ASSERT_EQ(value.signal,a[1].signal);
	ASSERT_EQ(value.currConnections, a[1].currConnections);
}

TEST(index, good2) {
    logicalElement a(2,2);
    logicalElement b(2,2);
    ASSERT_NO_THROW(a[1] = b[0]);
}

TEST(index_const, good) {
    const logicalElement a(2,2);
    ASSERT_NO_THROW(a[1]);
}

/////////////////////operation>><</////////////////////////

TEST(output, good) {
    logicalElement a{};
    std::stringstream os;
    os << a;
    ASSERT_EQ("The clamp #1:\ntype = input\nsignal = X\n\nThe clamp #2:\ntype = output\nsignal = X\n\n", os.str());
}

TEST(input, good) {
    logicalElement a{};
    std::stringstream is, os;
    is << "1010X";
    is >> a;
//    os << a;
//    ASSERT_EQ("The clamp #1:\ntype = input\nsignal = 1\n\nThe clamp #2:\ntype = input\nsignal = 0\n\nThe clamp #3:\ntype = input\nsignal = 1\n\nThe clamp #4:\ntype = input\nsignal = 0\n\nThe clamp #5:\ntype = input\nsignal = X\n\n", os.str());
    logicalElement b{}, c{};
    clamp v1{true};
    v1.signal = 'X';
    b += c;
    b[0].signal = '1';
    b[2].signal = '1';
    b += v1;
    b[1] = v1;
    b[1].signal = '0';
    b[3] = v1;
    b[3].signal = '0';
    ASSERT_EQ(true, a==b);

}
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