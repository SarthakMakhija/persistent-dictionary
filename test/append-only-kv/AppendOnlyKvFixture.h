#ifndef _AppendOnlyKvFixture_
#define _AppendOnlyKvFixture_

#include <gtest/gtest.h>
#include "../../src/append-only-kv/AppendOnlyKv.h"

using namespace dictionary::persistent::kv;

class AppendOnlyKvFixture : public ::testing::Test {

private:
    AppendOnlyKv *kv;
    const char *fileName = "./append-only-kv-tests.log";

public:
    void SetUp() {
        kv = AppendOnlyKv::open(fileName, 8 * 1024 * 1028);
    }

    void TearDown() {
        remove(fileName);
    }

    AppendOnlyKv *getKv() {
        return kv;
    }
};

#endif