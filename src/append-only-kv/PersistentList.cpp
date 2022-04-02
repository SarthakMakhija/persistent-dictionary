#include "PersistentList.h"
#include "PersistentNode.h"
#include "PersistentPool.h"

namespace dictionary {
    namespace persistent {
        namespace kv {
            PersistentList::PersistentList() {
                auto pmpool = PersistentPool::getInstance()->getPmpool();
                transaction::run(pmpool, [&] {
                    this->head = make_persistent<PersistentNode>();
                    this->head.get()->put("", "");
                });
            }

            void PersistentList::write(std::string key, std::string value) {
                PersistentNode *current = this->head.get();
                while (current->next.get()) {
                    current = current->next.get();
                }

                auto pmpool = PersistentPool::getInstance()->getPmpool();
                transaction::run(pmpool, [&] {
                    persistent_ptr<PersistentNode> newNode = make_persistent<PersistentNode>();
                    current->next = newNode;
                    newNode.get()->put(key.data(), value.data());
                });
            }

            unsigned long PersistentList::countEntries() {
                PersistentNode *current = this->head.get();
                unsigned long count = 0;
                while (current->next.get()) {
                    current = current->next.get();
                    count = count + 1;
                }
                return count;
            }

            std::string PersistentList::lastKey() {
                PersistentNode *current = this->head.get();
                while (current->next.get()) {
                    current = current->next.get();
                }
                return current->key();
            }

            std::string PersistentList::lastValue() {
                PersistentNode *current = this->head.get();
                while (current->next.get()) {
                    current = current->next.get();
                }
                return current->value();
            }
        }
    }
}