package org.study.demo.libAlg;

/**
 * author: wsyuhx
 * created on: 2021/7/12 16:46
 * description:
 */
public class Jni {

    public native void init(String modelBinPath,String modelParamPath);

    /***
     * 这里只是简单实现，固定传入rgb排列数据，jni接收时需对应
     * @param data
     * @param w
     * @param h
     * @return
     */
    public native float process(byte[] data,int w,int h);

}
