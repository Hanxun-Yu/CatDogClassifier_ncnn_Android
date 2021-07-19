//
// Created by wsyuhx on 2021/7/12.
//
#include <jni.h>
#include <string>
#include "stdio.h"
#include "AlgSDK.h"
#include "JniHelper.h"

extern "C" {

//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"
}


AlgSDK* alg;
JniHelper* jniHelper;

JNIEXPORT void JNICALL init
        (JNIEnv* env, jclass clazz, jstring modelBinPath, jstring modelParamPath) {

    alg = new AlgSDK();
    std::string str_modelBinPath = jniHelper->jstring2string(modelBinPath);
    std::string str_modelParamPath = jniHelper->jstring2string(modelParamPath);

    LOGD("init modelBinPath:%s modelParamPath:%s", str_modelBinPath.data(),str_modelParamPath.data());

    int ret = alg->initModel(str_modelBinPath.data(), str_modelParamPath.data(), 192);
    LOGD("init ret:%d", ret);

}

JNIEXPORT jfloat JNICALL process
        (JNIEnv* env, jclass clazz, jbyteArray dataArr, jint w, jint h) {

    uint8_t* byteArr = NULL;
    int len;
    jniHelper->jbyteArr2byteArr(dataArr, byteArr, len);
    LOGD("len:%d", len);


    float ret = alg->process(byteArr, w, h, ncnn::Mat::PIXEL_RGBA2RGB);



    return ret;
}


JNINativeMethod nativeMethod[] = {
        {"init",    "(Ljava/lang/String;Ljava/lang/String;)V", (void*) init},
        {"process", "([BII)F",                                 (void*) process},

};


std::string myClassName = "org/study/demo/libAlg/Jni";

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    jniHelper = new JniHelper(vm);

    return JniHelper::handleJNILoad(vm, reserved, myClassName, nativeMethod,
                                    sizeof(nativeMethod) / sizeof(nativeMethod[0]));
}