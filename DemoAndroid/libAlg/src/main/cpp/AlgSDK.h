//
// Created by wsyuhx on 2021/7/12.
//

#ifndef DEMOANDROID_ALGSDK_H
#define DEMOANDROID_ALGSDK_H

#include <include/ncnn/net.h>
#include "ncnn/simpleocv.h"

class AlgSDK {

//    const float m_mean_value[3] = { MEAN_VALUE_B, MEAN_VALUE_G, MEAN_VALUE_R };
//    const float m_norm_value[3] = { NORM_VALUE_B_CLASSIFY, NORM_VALUE_G_CLASSIFY, NORM_VALUE_R_CLASSIFY };
    ncnn::Net mNet;
    int mNetInputSize;

    AlgSDK();
    ~AlgSDK();
    int initModel(const char* param_path, const char* model_path, int mNetInputSize);
    float process(cv::Mat &img, int image_type);

};


#endif //DEMOANDROID_ALGSDK_H
