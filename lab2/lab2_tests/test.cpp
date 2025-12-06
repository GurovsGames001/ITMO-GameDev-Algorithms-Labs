#include "pch.h"
#include "..\lab2\Array.h"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> a;
    EXPECT_EQ(a.size(), 0);
}

TEST(ArrayTest, ParamConstructor) {
    Array<int> a(5);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.getCapacity(), 5);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> a;
    a.insert(1);
    a.insert(2);

    Array<int> b(a);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[0], a[0]);
    EXPECT_EQ(b[1], a[1]);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> a;
    a.insert(1);

    EXPECT_EQ(a.isEmpty(), false);

    Array<int> b(std::move(a));

    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(a.isEmpty(), true);
}

TEST(ArrayTest, CopyAssignment) {
    Array<int> a;
    a.insert(1); 
    a.insert(2);

    Array<int> b;
    b = a;

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[0], a[0]);
    EXPECT_EQ(b[1], a[1]);
}

TEST(ArrayTest, MoveAssignment) {
    Array<int> a;
    a.insert(1);

    EXPECT_EQ(a.isEmpty(), false);

    Array<int> b;
    b = std::move(a);

    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(a.isEmpty(), true);
}

TEST(ArrayTest, OperatorIndex) {
    Array<std::string> a;
    a.insert("hello");

    EXPECT_EQ(a[0], "hello");

    a[0] = "world";

    EXPECT_EQ(a[0], "world");
}

TEST(ArrayTest, InsertEnd) {
    Array<int> a;
    a.insert(42);
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a[0], 42);
}

TEST(ArrayTest, InsertAtPosition) {
    Array<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(1, 100);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 100);
    EXPECT_EQ(a[2], 2);
}

TEST(ArrayTest, InsertMoreThanMaxCapacity) {
    Array<int> a(5);
    for (int i = 1; i <= 6; ++i) a.insert(i);
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.getCapacity(), 10);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[5], 6);
}

TEST(ArrayTest, InsertString)
{
    Array<std::string> a;
    a.insert("aaa");
    a.insert("bbb");
    a.insert("ccc");
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], "aaa");
    EXPECT_EQ(a[2], "ccc");
}

TEST(ArrayTest, InsertStringMoreThanMaxCapacity)
{
    Array<std::string> a(3);
    a.insert("aaa");
    a.insert("bbb");
    a.insert("ccc");
    a.insert("ddd");
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.getCapacity(), 6);
    EXPECT_EQ(a[0], "aaa");
    EXPECT_EQ(a[3], "ddd");
}

TEST(ArrayTest, Remove) {
    Array<int> a;
    for (int i = 1; i <= 5; ++i) a.insert(i);
    a.remove(2);
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 4);
    EXPECT_EQ(a[3], 5);
}

TEST(ArrayTest, RemoveString) {
    Array<std::string> a(3);
    a.insert("aaa");
    a.insert("bbb");
    a.insert("ccc");
    a.insert("ddd");
    a.remove(2);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], "aaa");
    EXPECT_EQ(a[1], "bbb");
    EXPECT_EQ(a[2], "ddd");
}

TEST(ArrayTest, IteratorForward) {
    Array<int> a;
    for (int i = 1; i <= 5; i++)
        a.insert(i);

    int expected = 1;
    for (auto it = a.iterator(); it.hasNext(); it.next()) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
}

TEST(ArrayTest, ConstIterator) {
    Array<int> a;
    a.insert(5);
    a.insert(6);

    const Array<int>& c = a;
    auto it = c.iterator();

    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 6);
}

TEST(ArrayTest, IteratorReverse) {
    Array<int> a;
    for (int i = 1; i <= 5; i++)
        a.insert(i);

    int expected = 5;

    for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
        EXPECT_EQ(*it, expected);
        expected--;
    }
}

TEST(ArrayTest, RangeFor) {
    Array<int> a;
    a.insert(10);
    a.insert(20);

    int sum = 0;
    for (int x : a) {
        sum += x;
    }

    EXPECT_EQ(sum, 30);
}