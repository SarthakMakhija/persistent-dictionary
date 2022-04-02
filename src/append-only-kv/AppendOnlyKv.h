#ifndef _AppendOnlyKv_
#define _AppendOnlyKv_

#include "PersistentPool.h"
#include "PersistentList.h"

namespace dictionary {
    namespace persistent {
        namespace kv {

            class AppendOnlyKv {
            private:
                ::dictionary::persistent::kv::PersistentPool *persistentPool;
                ::dictionary::persistent::kv::PersistentList *persistentList;
            public:
                static AppendOnlyKv *open(const char *fileName, uint64_t fileSize);

                void write(std::string key, std::string value);

                unsigned long countEntries();

                std::string lastKey();

                std::string lastValue();
            };
        }
    }
}

#endif
