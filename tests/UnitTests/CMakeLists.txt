
# Test project name
project(UnitTests)

# Look for header and source files.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "code/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "code/include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
#target_include_directories(Math3DLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code/include)

# Link the RHI lib and glm for math.
target_link_libraries(${PROJECT_NAME}
	PRIVATE
	Math3DLib
	GTest::gtest_main
)

# Include google tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# Mark this project as a test project of the Math lib.
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})