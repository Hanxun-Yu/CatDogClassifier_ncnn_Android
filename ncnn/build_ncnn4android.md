#####prepare
######完成build_ncnn
```
参考 build_ncnn.md
```

######安装AndroidNDK
[NDK Download](https://developer.android.google.cn/ndk/downloads/)  
下载Linux 64 位 (x86)  
下载完后解压到某个位置  
后续用<ndk_root>表示你解压ndk的根目录，<ncnn_root>表示ncnn源码根目录


####opecv
```
若需使用ncnn附带的opencv功能，需编辑<ncnn_root>/CMakeLists.txt  
找到下面这行，置为ON  
option(NCNN_SIMPLEOCV "minimal opencv structure emulation" ON)  
```
  
#####compile
######armeabi-v7a
```
cd <ncnn_root>
mkdir -p build-android-armv7
cd build-android-armv7

cmake -DCMAKE_TOOLCHAIN_FILE=<ndk_root>/build/cmake/android.toolchain.cmake \
-DANDROID_ABI="armeabi-v7a" \
-DANDROID_ARM_NEON=ON \
-DANDROID_PLATFORM=android-14 ..

make -j4
make install
```


######arm64-v8a
```
cd <ncnn_root>
mkdir -p build-android-arm64_v8a
cd build-android-arm64_v8a

cmake -DCMAKE_TOOLCHAIN_FILE=<ndk_root>/build/cmake/android.toolchain.cmake \
-DANDROID_ABI="arm64-v8a" \
-DANDROID_ARM_NEON=ON \
-DANDROID_PLATFORM=android-21 ..

make -j4
make install
```
