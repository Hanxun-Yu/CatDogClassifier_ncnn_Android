#####prepare
```
sudo apt install python3-pip
pip3 install onnx-simplifier
```

#####onnx2ncnn
```
cd ncnn/build/tools/onnx
python3 -m onnxsim src.onnx simplify.onnx
onnx2ncnn simplify.onnx ~.param ~.bin
```