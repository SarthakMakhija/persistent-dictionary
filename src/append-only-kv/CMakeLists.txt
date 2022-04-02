find_path(LIBPMEMOBJ_INCLUDE_DIR libpmemobj.h)
find_path(LIBPMEM_INCLUDE_DIR libpmem.h)

find_library(LIBPMEM_LIBRARY NAMES pmem libpmem)
find_library(LIBPMEMOBJ_LIBRARY NAMES pmemobj libpmemobj)

add_library(AppendOnlyKv
        AppendOnlyKv.cpp
        AppendOnlyKv.h
        PersistentList.cpp
        PersistentList.h
        PersistentNode.h
        PersistentPool.cpp
        PersistentPool.h)

target_include_directories(AppendOnlyKv
        PRIVATE
        ${LIBPMEMOBJ_INCLUDE_DIR}
        ${LIBPMEM_INCLUDE_DIR})

target_link_libraries(AppendOnlyKv
        PRIVATE
        ${LIBPMEM_LIBRARY}
        ${LIBPMEMOBJ_LIBRARY})
