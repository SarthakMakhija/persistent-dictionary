#ifndef _PersistentPool_
#define _PersistentPool_

#include <libpmemobj++/pool.hpp>
#include <string>
#include "PersistentNode.h"

namespace dictionary {
    namespace persistent {
        namespace kv {

            class PersistentPool {

            public:
                PersistentPool(PersistentPool &other) = delete;

                void operator=(const PersistentPool &) = delete;

                static PersistentPool *initialize(const char *filePath, uint64_t size);

                static PersistentPool *getInstance();

                pmem::obj::pool_base getPmpool();

                ~PersistentPool() {
                    try {
                        instance = nullptr;
                        pmpool.close();
                    } catch (const std::logic_error &e) {
                        std::terminate();
                    }
                }

            protected:
                struct Root {
                    pmem::obj::persistent_ptr<PersistentNode> ptr;
                };

                pmem::obj::pool_base pmpool;
                PMEMoid *root_oid;

            private:
                static PersistentPool *instance;

                PersistentPool(const char *filePath, uint64_t size = 8 * 1024 * 1024) {
                    bool openFailed = false;
                    std::string layout = "persistentList";

                    try {
                        pmpool = pmem::obj::pool<Root>::open(filePath, layout);
                    } catch (pmem::pool_invalid_argument &e) {
                        openFailed = true;
                    }

                    if (openFailed) {
                        pmpool = createOrFail(filePath, size, layout);
                    }
                    root_oid = static_cast<pmem::obj::pool<Root>>(pmpool).root()->ptr.raw_ptr();
                }

                pmem::obj::pool<Root>
                createOrFail(const char *path, const std::size_t size, const std::string &layout) {
                    try {
                        return pmem::obj::pool<Root>::create(path, layout, size);
                    } catch (pmem::pool_invalid_argument &e) {
                        throw std::invalid_argument(e.what());
                    }
                }
            };
        }
    }
}

#endif