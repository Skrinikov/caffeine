
add_subdirectory(Support)

file(
  GLOB_RECURSE sources
  CONFIGURE_DEPENDS
  *.cpp
  *.hpp
  *.h
)

file(
  GLOB_RECURSE headers
  CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/include/*.hpp"
  "${CMAKE_SOURCE_DIR}/include/*.h"
  "${CMAKE_SOURCE_DIR}/include/*.inl"
)

file(
  GLOB capnp_schemas
  CONFIGURE_DEPENDS
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/Protos/*.capnp"
)


set(CAPNPC_OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen/caffeine/")
file(MAKE_DIRECTORY ${CAPNPC_OUTPUT_DIR})

capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS "${capnp_schemas}")
list(APPEND sources ${CAPNP_SRCS})

add_library(caffeine ${sources} ${headers})

target_include_directories(caffeine PUBLIC "${CMAKE_BINARY_DIR}/gen/")

target_include_directories(caffeine
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
  PUBLIC "${CMAKE_SOURCE_DIR}/include"
)

# The SYSTEM should silence warnings within these headers
target_include_directories(caffeine SYSTEM
  PUBLIC "${LLVM_INCLUDE_DIRS}"
  PUBLIC "${Z3_INCLUDE_DIRS}"
  PUBLIC "${FMT_INCLUDE_DIRS}"
  PUBLIC "${Boost_INCLUDE_DIRS}"
)

target_link_options(caffeine PUBLIC ${LINK_FLAGS})
target_link_libraries(caffeine PUBLIC
  LLVMCore
  "${Z3_LIBRARIES}"
  fmt::fmt
  immer
  magic_enum::magic_enum
  CapnProto::capnp-rpc
)
