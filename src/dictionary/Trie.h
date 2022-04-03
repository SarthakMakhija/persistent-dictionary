#ifndef _Trie_
#define _Trie_

#include <libpmemobj++/persistent_ptr.hpp>
#include <string>
#include "TrieNode.h"

using pmem::obj::persistent_ptr;

namespace dictionary {
    namespace persistent {
        class Trie {
        private:
            persistent_ptr<TrieNode> root;
        public:
            static Trie *open(const char *fileName, uint64_t fileSize);

            void add(std::string word);

            bool contains(std::string word);

            bool containsPrefix(std::string prefix);
        };
    }
}
#endif