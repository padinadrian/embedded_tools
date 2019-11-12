/**
 * Filename:    adrian_fixed_list_test.cpp
 * Author:      padin.adrian@gmail.com
 */

/* ===== Includes ===== */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "containers/adrian_fixed_list.hpp"

using namespace adrian;

/* ===== Tests ===== */

// Size and Capacity
TEST(AdrianFixedList, SizeCapacity)
{
    FixedList<int, 3> list;
    EXPECT_EQ(list.Size(), 0);
    EXPECT_EQ(list.Capacity(), 3);
}

// Front and Back
TEST(AdrianFixedList, FrontBack)
{
    FixedList<int, 1> list;
    auto iter = list.InsertFront(100);
    EXPECT_EQ(*iter, 100);
    iter = list.Front();
    EXPECT_EQ(*iter, 100);
    iter = list.Back();
    EXPECT_EQ(*iter, 100);
}

// InsertFront
TEST(AdrianFixedList, InsertFront1)
{
    FixedList<int, 3> list;
    EXPECT_EQ(list.Size(), 0);

    auto iter = list.InsertFront(1);
    EXPECT_EQ(list.Size(), 1);
    EXPECT_EQ(*iter, 1);

    iter = list.InsertFront(2);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_EQ(*iter, 2);

    iter = list.InsertFront(100);
    EXPECT_EQ(list.Size(), 3);
    EXPECT_EQ(*iter, 100);
}

// InsertBack
TEST(AdrianFixedList, InsertBack1)
{
    FixedList<std::string, 1> strlist;
    EXPECT_EQ(strlist.Size(), 0);

    auto iter = strlist.InsertBack("hello");
    EXPECT_EQ(*iter, std::string("hello"));

    EXPECT_EQ(strlist.Front(), iter);
    EXPECT_EQ(strlist.Back(), iter);

    EXPECT_EQ(*strlist.Front(), std::string("hello"));
    EXPECT_EQ(*strlist.Back(), std::string("hello"));
}

// Iterating the list.
TEST(AdrianFixedList, IterateForward)
{
    FixedList<int, 100> list;

    for (size_t i = 1; i < 101; i++)
    {
        list.InsertBack(i);
    }
    EXPECT_EQ(list.Size(), 100);
    EXPECT_EQ(list.InsertBack(101), list.End());

    size_t sum = 0;
    for (auto iter = list.Begin(); iter != list.End(); iter++)
    {
        sum += *iter;
    }

    EXPECT_EQ(sum, 5050);
}

// Iterating the list backwards.
TEST(AdrianFixedList, IterateBackward)
{
    FixedList<int, 100> list;

    for (size_t i = 1; i < 101; i++)
    {
        list.InsertFront(i);
    }
    EXPECT_EQ(list.Size(), 100);
    EXPECT_EQ(list.InsertBack(101), list.End());

    size_t sum = 0;
    for (auto iter = list.Back(); iter != list.End(); iter--)
    {
        sum += *iter;
    }

    EXPECT_EQ(sum, 5050);
}

// Inserting and erasing.
TEST(AdrianFixedList, InsertErase)
{
    FixedList<int, 6> list;

    for (size_t i = 1; i < 7; i++)
    {
        list.InsertBack(i);
    }
    // list internals = [1, 2, 3, 4, 5, 6]

    EXPECT_EQ(list.Capacity(), 6);
    EXPECT_EQ(list.Size(), 6);
    EXPECT_EQ(list.InsertBack(101), list.End());

    auto iter = list.Begin();
    iter++;
    iter++;
    EXPECT_EQ(*iter, 3);

    list.Erase(iter++);
    list.Erase(iter++);
    // list internals = [1, 2, _, _, 5, 6]

    EXPECT_EQ(list.Capacity(), 6);
    EXPECT_EQ(list.Size(), 4);

    list.InsertBack(7);
    list.InsertBack(8);
    // list internals = [1, 2, 8, 7, 5, 6]

    EXPECT_EQ(list.Capacity(), 6);
    EXPECT_EQ(list.Size(), 6);

    iter = list.Begin();
    EXPECT_EQ(*(iter++), 1);
    EXPECT_EQ(*(iter++), 2);
    EXPECT_EQ(*(iter++), 5);
    EXPECT_EQ(*(iter++), 6);
    EXPECT_EQ(*(iter++), 7);
    EXPECT_EQ(*(iter++), 8);
}
