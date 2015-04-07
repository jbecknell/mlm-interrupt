cmake_minimum_required (VERSION 2.6)
project (mlm-interrupt)

if(${WIN32})

set(COMPILER_FLAGS
    "/D ZMQ_STATIC"
    "/D LIBCZMQ_STATIC"
    "/D LIBMLM_STATIC"
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DZMQ_STATIC -DLIBCZMQ_STATIC -DLIBMLM_STATIC")

include_directories("${PROJECT_BINARY_DIR}" 
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/external/mlm-prefix/src/mlm/include
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/external/zmq-prefix/src/zmq/include
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/external/czmq-prefix/src/czmq/include
)
link_directories(
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/lib64/zmq/Debug
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/lib64/czmq/Debug
    D:/Projects/MemDB/Source/C++/master/memdb/build/VS2013\ x64/lib64/mlm/Debug
)
add_executable(mlm-interrupt src/mlm.cpp)
target_link_libraries(mlm-interrupt     
    rpcrt4
    ws2_32 
    libzmq-mt-gd-4_2_0.lib 
    libczmq-mt-gd-3_0_1.lib 
    libmlm-mt-gd-1_1_0.lib)

else()

include_directories("${PROJECT_BINARY_DIR}" /home/jbecknell/Projects/MemDB/github/malamute-core/include
    /home/jbecknell/Projects/MemDB/github/libzmq/include
    /home/jbecknell/Projects/MemDB/github/libczmq/include
)
link_directories(
    /home/jbecknell/Projects/MemDB/github/libzmq/src/.libs
    /home/jbecknell/Projects/MemDB/github/libczmq/src/.libs
    /home/jbecknell/Projects/MemDB/github/malamute-core/src/.libs
)
add_executable(mlm-interrupt src/mlm.cpp)
target_link_libraries(mlm-interrupt zmq czmq mlm)

endif()


