//
// Created by wsyuhx on 2021/7/12.
//

#include "AlgSDK.h"

AlgSDK::AlgSDK() {

}

AlgSDK::~AlgSDK() {

}

int AlgSDK::initModel(const char* param_path, const char* model_path, int mNetInputSize) {

    int ret_load_param = mNet.load_param(param_path);
    int ret_load_model = mNet.load_model(model_path);

    if (ret_load_param != 0 || ret_load_model != 0) {
        return -1;
    }

    mNetInputSize = mNetInputSize;
    return 0;
}

float AlgSDK::process(cv::Mat &img, int image_type) {

    ncnn::Mat ncnn_img;
    ncnn_img = ncnn::Mat::from_pixels_resize((const unsigned char*) img.data, image_type, img.cols,
                                             img.rows, mNetInputSize, mNetInputSize);
//    ncnn_img.substract_mean_normalize(m_mean_value, 0);
    ncnn::Extractor ex = mNet.create_extractor();
    ex.input("data", ncnn_img);
    ncnn::Mat inference_out;
    ex.extract("prob", inference_out);

    float ret = 0L;
    ret = inference_out[0];
    return ret;
}
