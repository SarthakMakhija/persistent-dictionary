#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "./AppendOnlyKvFixture.h"

using namespace dictionary::persistent::kv;

TEST_F(AppendOnlyKvFixture, AppendOnlyKv_AddsAKeyValue) {
    AppendOnlyKv* kv = AppendOnlyKvFixture::getKv();
    kv->write("A", "B");

    auto totalEntries = kv->countEntries();
    ASSERT_EQ(1, totalEntries);
}

TEST_F(AppendOnlyKvFixture, AppendOnlyKv_Adds2KeyValues) {
    AppendOnlyKv* kv = AppendOnlyKvFixture::getKv();
    kv->write("A", "B");
    kv->write("C", "D");

    auto totalEntries = kv->countEntries();
    ASSERT_EQ(2, totalEntries);
}

TEST_F(AppendOnlyKvFixture, AppendOnlyKv_GetsTheLastKey) {
    AppendOnlyKv* kv = AppendOnlyKvFixture::getKv();
    kv->write("A", "B");
    kv->write("C", "D");

    auto lastKey = kv->lastKey();
    ASSERT_EQ("C", lastKey);
}

TEST_F(AppendOnlyKvFixture, AppendOnlyKv_GetsTheLastValue) {
    AppendOnlyKv* kv = AppendOnlyKvFixture::getKv();
    kv->write("A", "B");
    kv->write("C", "D");

    auto lastValue = kv->lastValue();
    ASSERT_EQ("D", lastValue);
}