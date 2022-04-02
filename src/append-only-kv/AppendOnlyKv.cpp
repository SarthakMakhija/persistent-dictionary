#include "AppendOnlyKv.h"

namespace dictionary {
    namespace persistent {
        namespace kv {
            AppendOnlyKv *AppendOnlyKv::open(const char *fileName, uint64_t fileSize) {
                auto *kv = new AppendOnlyKv();
                kv->persistentPool = ::dictionary::persistent::kv::PersistentPool::initialize(fileName, fileSize);
                kv->persistentList = new ::dictionary::persistent::kv::PersistentList();
                return kv;
            }

            void AppendOnlyKv::write(std::string key, std::string value) {
                this->persistentList->write(key, value);
            }

            unsigned long AppendOnlyKv::countEntries() {
                return this->persistentList->countEntries();
            }

            std::string AppendOnlyKv::lastKey() {
                return this->persistentList->lastKey();
            }

            std::string AppendOnlyKv::lastValue() {
                return this->persistentList->lastValue();
            }
        }
    }
}