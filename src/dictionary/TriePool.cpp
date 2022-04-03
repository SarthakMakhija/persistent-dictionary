#include "./TriePool.h"

namespace dictionary {
    namespace persistent {
        TriePool *TriePool::instance = nullptr;

        TriePool *TriePool::initialize(const char *filePath, uint64_t size) {
            if (instance == nullptr) {
                instance = new TriePool(filePath, size);
            }
            return instance;
        }

        TriePool *TriePool::getInstance() {
            if (instance == nullptr) {
                throw std::logic_error("Can not invoke getInstance without initializing TriePool");
            }
            return instance;
        }

        pmem::obj::pool_base TriePool::getPmpool() {
            return this->pmpool;
        }
    }
}