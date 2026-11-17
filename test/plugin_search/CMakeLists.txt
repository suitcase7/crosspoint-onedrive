add_executable(PluginSearchTest PluginSearchTest.cpp)
target_include_directories(PluginSearchTest PRIVATE ${REPO_ROOT}/src/util)
target_link_libraries(PluginSearchTest PRIVATE crosspoint_test_common GTest::gtest_main)
gtest_discover_tests(PluginSearchTest)
