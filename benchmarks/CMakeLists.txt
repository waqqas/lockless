project(benchmarks)

file(GLOB TEST_SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(benchmark REQUIRED)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
