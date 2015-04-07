cmake_minimum_required (VERSION 2.6)
project (mlm-interrupt)
include_directories("${PROJECT_BINARY_DIR}" /home/jbecknell/Projects/MemDB/github/malamute-core/include
	/home/jbecknell/Projects/MemDB/github/libzmq/include
	/home/jbecknell/Projects/MemDB/github/libczmq/include
)

link_directories(
	/home/jbecknell/Projects/MemDB/github/libzmq/src/.libs
 	/home/jbecknell/Projects/MemDB/github/libczmq/src/.libs
	/home/jbecknell/Projects/MemDB/github/malamute-core/src/.libs
)

# add the executable
add_executable(mlm-interrupt src/mlm.cpp)
target_link_libraries(mlm-interrupt zmq czmq mlm)
