//
// Created by wsyuhx on 2021/7/12.
//
#include <jni.h>
#include <string>
#include "stdio.h"
#include "android/log.h"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__)

#define  LOGD_TAG(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)
#define  LOGI_TAG(tag, ...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)
#define  LOGW_TAG(tag, ...)  __android_log_print(ANDROID_LOG_WARN,tag,__VA_ARGS__)
#define LOGE_TAG(tag, ...)  __android_log_print(ANDROID_LOG_ERROR,tag,__VA_ARGS__)
#define LOGF_TAG(tag, ...)  __android_log_print(ANDROID_LOG_FATAL,tag,__VA_ARGS__)

extern "C" {

//#include "libavcodec/avcodec.h"
//#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"
}

JNIEXPORT void JNICALL init
        (JNIEnv* env, jclass clazz, jstring modelBinPath, jstring modelParamPath) {

}

JNIEXPORT jfloat JNICALL process
        (JNIEnv* env, jclass clazz, jbyteArray dataArr, jint w, jint h) {

}


JNINativeMethod nativeMethod[] = {
        {"init", "(Ljava/lang/String;Ljava/lang/String;)V", (void *) init},
        {"init", "([BII)F", (void *) process},

};


std::string myClassName = "org/study/demo/libAlg/Jni";

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

    JNIEnv* env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass myClass = env->FindClass(myClassName.data());
    if (myClass == NULL) {
        printf("cannot get class:%s\n", myClassName.data());
        return -1;
    }
    if ((env)->RegisterNatives(myClass, nativeMethod, sizeof(nativeMethod) / sizeof(nativeMethod[0])
    ) < 0) {
        printf("register native method failed!\n");
        return -1;
    }
    LOGD_TAG("haha", "--------JNI_OnLoad-----");
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}