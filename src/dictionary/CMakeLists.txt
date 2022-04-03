find_path(LIBPMEMOBJ_INCLUDE_DIR libpmemobj.h)
find_path(LIBPMEM_INCLUDE_DIR libpmem.h)

find_library(LIBPMEM_LIBRARY NAMES pmem libpmem)
find_library(LIBPMEMOBJ_LIBRARY NAMES pmemobj libpmemobj)

add_library(PersistentDictionary
        Trie.cpp
        Trie.h
        TrieNode.h
        TriePool.cpp
        TriePool.h)

target_include_directories(PersistentDictionary
        PRIVATE
        ${LIBPMEMOBJ_INCLUDE_DIR}
        ${LIBPMEM_INCLUDE_DIR})

target_link_libraries(PersistentDictionary
        PRIVATE
        ${LIBPMEM_LIBRARY}
        ${LIBPMEMOBJ_LIBRARY})
