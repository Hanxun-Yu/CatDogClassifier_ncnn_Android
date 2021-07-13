[参考链接](https://zhuanlan.zhihu.com/p/68694581?from_voters_page=true)

#####prepare
```
sudo apt install  g++
sudo apt install cmake
sudo apt install protobuf-compiler libprotobuf-dev
sudo apt install libopencv-dev  
```

#####clone & compile
```
git clone https://github.com/Tencent/ncnn
cd ncnn
mkdir build && cd build
cmake ..
make -j4
make install
```
