#include "Trie.h"
#include "TriePool.h"

namespace dictionary {
    namespace persistent {
        Trie *Trie::open(const char *fileName, uint64_t fileSize) {
            auto *trie = new Trie();
            TriePool::initialize(fileName, fileSize);

            auto pmpool = TriePool::getInstance()->getPmpool();
            transaction::run(pmpool, [&] {
                trie->root = make_persistent<TrieNode>();
            });
            return trie;
        }

        void Trie::add(std::string word) {
            this->root.get()->add(word, TriePool::getInstance()->getPmpool());
        }

        bool Trie::contains(std::string word) {
            return this->root.get()->contains(word);
        }

        bool Trie::containsPrefix(std::string prefix) {
            return this->root.get()->containsPrefix(prefix);
        }
    }
}