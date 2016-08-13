# Library Configuration

add_library (Configuration Settings.cpp OptionsParser.cpp)
target_include_directories (Configuration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})