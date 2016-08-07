# Surveillance System
Provide basic motion detection and video recording capability. It is tested on Windows 10 and Raspberry Pi 2.
For RPi, please make sure NEON support is enabled when compiling OpenCV library.

## Requirement
1. cmake >= 2.8
2. Boost++ >= 1.60 (for Program options)
3. OpenCV >= 3.1
4. yaml-cpp (for reading configuration file)
  *[https://github.com/jbeder/yaml-cpp]
5. easyloggingpp
  *[https://github.com/easylogging/easyloggingpp]

## Build
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
         -DYAML_CPP_INCLUDEDIR=/usr/include/yaml-cpp
         -DYAML_CPP_LIBRARYDIR=/usr/lib
```

Note: you may need to define Boost_INCLUDE_DIR and Boost_LIBRARY_DIR

## Run
Change the parameters in sample/config.yaml according to your need.
Assume that you have the program and config.yaml in the same folder.
```bash
Nest -c config.yaml
```

## To-Do
1. Add unit test
2. Add validation on yaml file
3. Add multiple cameras support
4. Upload to cloud (Dropbox? maybe a seperated project)
5. Package it into Docker?