#ifndef _TrieNode_
#define _TrieNode_

#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj/pool_base.h>
#include <string>

using pmem::obj::make_persistent;
using pmem::obj::persistent_ptr;
using pmem::obj::p;
using pmem::obj::pool;
using pmem::obj::transaction;

namespace dictionary {
    namespace persistent {

        struct TrieNode;

        struct Slot {
            persistent_ptr<TrieNode> next;

            void setNext(persistent_ptr<TrieNode> next_) {
                next = next_;
            }
        };

        struct TrieNode {
            p<Slot> slots[26];
            p<bool> endOfWord;

            void add(std::string word, pmem::obj::pool_base pmpool) {
                TrieNode *current = this;
                transaction::run(pmpool, [&] {
                    for (auto &ch: word) {
                        int index = ch - 'a';
                        if (!current->slots[index].get_ro().next) {
                            current->slots[index].get_rw().setNext(make_persistent<TrieNode>());
                        }
                        current = current->slots[index].get_rw().next.get();
                    }
                    current->endOfWord = true;
                });
            }

            bool contains(std::string word) {
                TrieNode *current = this;
                for (auto &ch: word) {
                    int index = ch - 'a';
                    if (!current->slots[index].get_ro().next) {
                        return false;
                    }
                    current = current->slots[index].get_ro().next.get();
                }
                return current->endOfWord;
            }

            bool containsPrefix(std::string prefix) {
                TrieNode *current = this;
                for (auto &ch: prefix) {
                    int index = ch - 'a';
                    if (!current->slots[index].get_ro().next) {
                        return false;
                    }
                    current = current->slots[index].get_ro().next.get();
                }
                return true;
            }
        };
    }
}
#endif