#ifndef _PersistentNode_
#define _PersistentNode_

#include <libpmemobj++/make_persistent_array.hpp>
#include <libpmemobj++/persistent_ptr.hpp>

using pmem::obj::make_persistent;
using pmem::obj::persistent_ptr;

namespace dictionary {
    namespace persistent {
        namespace kv {

            struct PersistentNode {
                persistent_ptr<PersistentNode> next;
                persistent_ptr<char[]> keyValue;

                void setKeySize(char *p, uint32_t v) {
                    *((uint32_t *) (p)) = v;
                }

                void setValueSize(char *p, uint32_t v) {
                    *((uint32_t *) ((char *) (p) + sizeof(uint32_t))) = v;
                }

                void put(const char *key, const char *value) {
                    size_t ksize = strlen(key);
                    size_t vsize = strlen(value);
                    size_t size = ksize + vsize + sizeof(uint32_t) + sizeof(uint32_t) + 2;

                    keyValue = make_persistent<char[]>(size);

                    char *p = keyValue.get();
                    setKeySize(p, (uint32_t) ksize);
                    setValueSize(p, (uint32_t) vsize);

                    char *kvptr = p + sizeof(uint32_t) + sizeof(uint32_t);
                    memcpy(kvptr, key, ksize);
                    kvptr += ksize + 1;
                    memcpy(kvptr, value, vsize);
                }

                uint32_t keySize() const {
                    return *((uint32_t *) (keyValue.get()));
                }

                const char *key() const {
                    return ((char *) (keyValue.get()) + sizeof(uint32_t) + sizeof(uint32_t));
                }

                const char *value() const {
                    return ((char *) (keyValue.get()) + sizeof(uint32_t) + sizeof(uint32_t) + keySize() + 1);
                }
            };
        }
    }
}
#endif
