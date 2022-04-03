#ifndef _DictionaryFixture_
#define _DictionaryFixture_

#include <gtest/gtest.h>
#include "../../src/dictionary/Trie.h"

using namespace dictionary::persistent;

class DictionaryFixture : public ::testing::Test {

private:
    ::dictionary::persistent::Trie *trie;
    const char *fileName = "./dictionary-tests.log";

public:
    void SetUp() {
        trie = ::dictionary::persistent::Trie::open(fileName, 8 * 1024 * 1028);
    }

    void TearDown() {
        remove(fileName);
    }

    ::dictionary::persistent::Trie *getDictionary() {
        return trie;
    }
};

#endif