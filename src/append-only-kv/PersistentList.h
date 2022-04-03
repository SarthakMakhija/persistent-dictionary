#ifndef _PersistentList_
#define _PersistentList_

#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj/pool_base.h>

using pmem::obj::persistent_ptr;
using pmem::obj::pool;
using pmem::obj::transaction;

#include <string>
#include "PersistentNode.h"

using pmem::obj::persistent_ptr;
using pmem::obj::make_persistent;

namespace dictionary {
    namespace persistent {
        namespace kv {

            class PersistentList {
            private:
                persistent_ptr<PersistentNode> head;
            public:
                PersistentList();

                void write(std::string key, std::string value);

                unsigned long countEntries();

                std::string lastKey();

                std::string lastValue();
            };
        }
    }
}
#endif
