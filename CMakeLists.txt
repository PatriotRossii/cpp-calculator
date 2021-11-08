project(calculator)

# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 20)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE /usr/local/lib/antlr-4.9.2-complete.jar)
set(ANTLR4_RUNTIME_LIBRARIES /usr/local/lib)
# add macros to generate ANTLR Cpp code from grammar

find_package(ANTLR REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


# Call macro to add lexer and grammar to your build dependencies.
antlr_target(MathLexer MathLexer.g4 LEXER)
antlr_target(MathParser MathParser.g4 PARSER
             DEPENDS_ANTLR MathLexer
             COMPILE_FLAGS -lib ${ANTLR_MathLexer_OUTPUT_DIR} VISITOR)

# include generated files in project environment
include_directories(${ANTLR_MathLexer_OUTPUT_DIR})
include_directories(${ANTLR_MathParser_OUTPUT_DIR})

add_executable(calculator src/main.cpp
               ${ANTLR_MathLexer_CXX_OUTPUTS}
               ${ANTLR_MathParser_CXX_OUTPUTS} ${SOURCE_FILES})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(calculator antlr4_static ${llvm_libs})
