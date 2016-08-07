# Library DateTime

add_library (DateTime Clock.cpp Timer.cpp)
target_include_directories (DateTime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})