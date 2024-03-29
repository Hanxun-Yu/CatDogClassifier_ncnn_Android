# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
set(SO_IMPORT_PATH ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI})
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
include_directories(
        src/main/cpp/
        src/main/cpp/include

)

message("SO_IMPORT_PATH ${SO_IMPORT_PATH}")



add_library( # Sets the name of the library.
        jni

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/JniHelper.cpp
        src/main/cpp/AlgSDK.cpp
        src/main/cpp/jni.cpp)

add_library( # Sets the name of the library.
        ncnn

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        IMPORTED)

set_target_properties(
        ncnn
        PROPERTIES IMPORTED_LOCATION
        ${SO_IMPORT_PATH}/libncnn.a)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

find_library( # Sets the name of the path variable.
        android-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        android)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        jni
        ncnn
        ${log-lib}
        ${android-lib}
        )