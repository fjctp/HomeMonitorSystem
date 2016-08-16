# add config file
configure_file( md_config.hpp.in ${CMAKE_BINARY_DIR}/generated/md_config.hpp )

# add dir
include_directories( ${CMAKE_BINARY_DIR}/generated/ )
include_directories("include")

# add mylibs
add_subdirectory("libs")

# Declare the executable target built from your sources
add_executable(Nest main.cpp Nest.cpp EagleEye.cpp FrameGrabber.cpp
  FrameWriter.cpp ImageProcessor.cpp Scheduler.cpp)

# Link with libraries
target_link_libraries(Nest Configuration)
target_link_libraries(Nest DateTime)
target_link_libraries(Nest Status)

# link with 3rd parties
target_link_libraries(Nest ${OpenCV_LIBS})


if(MSVC)
  target_link_libraries(Nest libyaml-cpp)
elseif(MINGW)
  target_link_libraries(Nest pthread)
  target_link_libraries(Nest boost_program_options-mgw54-mt-1_61)
  target_link_libraries(Nest yaml-cpp)
elseif(UNIX)
  target_link_libraries(Nest pthread)
  target_link_libraries(Nest boost_program_options)
  target_link_libraries(Nest yaml-cpp)
endif(MSVC)
