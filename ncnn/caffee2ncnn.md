#####这里需要注意检查caffe产生的prototxt，需改成ncnn标准的prototxt
######caffe产生的
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/clipboard2.png)

######改为ncnn标准的
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/clipboard.png)


```
cd ncnn/build/tools/caffe
./caffe2ncnn ~.prototxt ~.caffemodel output.param output.bin
```