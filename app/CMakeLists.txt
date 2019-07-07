# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(src/main/cpp RootSrc)

add_library( native-lib SHARED ${RootSrc} )

find_library( log-lib log )


set(distribution_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
add_library( fmod SHARED IMPORTED )
#引用目标类库是本地类库位置在libs/armeabi-v7a/libHello.so
set_target_properties( fmod PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/libfmod.so )

add_library( fmodL SHARED IMPORTED )
set_target_properties( fmodL PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/libfmodL.so )

target_link_libraries( native-lib fmod fmodL ${log-lib} )


