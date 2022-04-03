#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "./DictionaryFixture.h"

using namespace dictionary::persistent;

TEST_F(DictionaryFixture, Dictionary_ContainsAnAddedWord) {
    Trie* dictionary = DictionaryFixture::getDictionary();
    dictionary->add("meet");
    dictionary->add("memory");

    ASSERT_TRUE(dictionary -> contains("memory"));
}

TEST_F(DictionaryFixture, Dictionary_DoesNotContainAWord) {
    Trie* dictionary = DictionaryFixture::getDictionary();
    dictionary->add("meet");
    dictionary->add("memory");

    ASSERT_FALSE(dictionary -> contains("market"));
}


TEST_F(DictionaryFixture, Dictionary_ContainsAWordByPrefix) {
    Trie* dictionary = DictionaryFixture::getDictionary();
    dictionary->add("meet");
    dictionary->add("memory");

    ASSERT_TRUE(dictionary -> containsPrefix("me"));
}

TEST_F(DictionaryFixture, Dictionary_DoesNotContainAWordByPrefix) {
    Trie* dictionary = DictionaryFixture::getDictionary();
    dictionary->add("meet");
    dictionary->add("memory");

    ASSERT_FALSE(dictionary -> containsPrefix("met"));
}
