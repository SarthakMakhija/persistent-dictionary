#include "./PersistentPool.h"

namespace dictionary {
    namespace persistent {
        namespace kv {

            PersistentPool *PersistentPool::instance = nullptr;

            PersistentPool *PersistentPool::initialize(const char *filePath, uint64_t size) {
                if (instance == nullptr) {
                    instance = new PersistentPool(filePath, size);
                }
                return instance;
            }

            PersistentPool *PersistentPool::getInstance() {
                if (instance == nullptr) {
                    throw std::logic_error("Can not invoke getInstance without initializing PersistentPool");
                }
                return instance;
            }

            pmem::obj::pool_base PersistentPool::getPmpool() {
                return this->pmpool;
            }
        }
    }
}