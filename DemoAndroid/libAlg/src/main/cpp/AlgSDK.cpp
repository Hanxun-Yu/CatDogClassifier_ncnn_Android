//
// Created by wsyuhx on 2021/7/12.
//

#include "AlgSDK.h"
#include "JniHelper.h"

AlgSDK::AlgSDK() {

}

AlgSDK::~AlgSDK() {

}

int AlgSDK::initModel( const char* model_path,const char* param_path, int mNetInputSize) {

    int ret_load_param = mNet.load_param(param_path);
    int ret_load_model = mNet.load_model(model_path);
    LOGD("ret_load_model :%d", ret_load_model);
    LOGD("ret_load_param :%d", ret_load_param);

    if (ret_load_param != 0 || ret_load_model != 0) {
        return -1;
    }

    this->mNetInputSize = mNetInputSize;
    return 0;
}

float AlgSDK::process(cv::Mat &img, int image_type) {

    //https://zhuanlan.zhihu.com/p/231101125

//    ncnn::Mat ncnn_img;
//    ncnn_img = ncnn::Mat::from_pixels_resize((const unsigned char*) img.data, image_type, img.cols,
//                                             img.rows, mNetInputSize, mNetInputSize);
}

float AlgSDK::process(uint8_t* data ,int w,int h , int image_type) {

    //https://zhuanlan.zhihu.com/p/231101125
    LOGD("process: data:%p w:%d h:%d image_type:%d ", data,w,h,image_type);
    LOGD("process: mNetInputSize:%d", mNetInputSize);

    ncnn::Mat ncnn_img;
    LOGD("process: 1");

    ncnn_img = ncnn::Mat::from_pixels_resize(data, image_type, w,
                                             h, mNetInputSize, mNetInputSize);
    LOGD("process: 2");

//    ncnn_img.substract_mean_normalize(m_mean_value, 0);
    ncnn::Extractor ex = mNet.create_extractor();
    ex.input("input", ncnn_img);
    ncnn::Mat inference_out;
    ex.extract("out", inference_out);

    LOGD("process: 3");

    float ret = 0L;
    ret = inference_out[0];
    return ret;
}
