//
// Created by yuhanxun on 2018/6/15.
//


#include "JniHelper.h"

//JniHelper::JniHelper() {
//}

//JniHelper::JniHelper(JNIEnv *env) {
//    this->env = env;
//}
JniHelper::JniHelper(JavaVM *jvm) {
    this->jvm = jvm;
}

std::string JniHelper::jstring2string(jstring jstr) {
    /**
     *  dont do this like : return jstring2char_p(jstr);
     *  because jstring2char_p(jstr) will malloc char*,  return immediately will keep char* in memory
     *
     * when char* assign to string, C++ will copy data from char* to string
     * after the above, just free char* now and return string
     */
    char *temp = jstring2char_p(jstr);
    std::string ret = temp;
    free(temp);
    return ret;
}

char *JniHelper::jstring2char_p(jstring jstr) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    const char *str_src = env->GetStringUTFChars(jstr, NULL);
    char *ret = strcpyWrap(const_cast<char *>(str_src));
    env->ReleaseStringUTFChars(jstr, str_src);
    return ret;
}

jstring JniHelper::string2jstring(std::string str) {
    return char_p2jstring(const_cast<char *>(str.c_str()));
}

jstring JniHelper::char_p2jstring(char *char_p) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jstring ret = env->NewStringUTF(char_p);
    return ret;
}

void JniHelper::jbyteArr2byteArr(jbyteArray jbyteArr, uint8_t *&byteArr, int32_t &len) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jbyte *jbyte1 = env->GetByteArrayElements(jbyteArr, NULL);
    len = env->GetArrayLength(jbyteArr);
    if (!byteArr) {
        byteArr = (uint8_t *) malloc(len);
    }
    memset(byteArr, 0, len);
    memcpy(byteArr, jbyte1, len);
    env->ReleaseByteArrayElements(jbyteArr, jbyte1, 0);//最后参数0,会释放jbyte1 所指向的内存的
}

jbyteArray JniHelper::byteArr2jbyteArr(uint8_t *byteArr, int32_t len) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jbyte *temp = (jbyte *) malloc(sizeof(jbyte) * len);
    for (int i = 0; i <= len; i++) {
        temp[i] = byteArr[i];
    }

    jbyteArray ret = env->NewByteArray(len);
    env->SetByteArrayRegion(ret, 0, len, temp);

    free(temp);
    return ret;
}


char *JniHelper::strcpyWrap(char *src) {
    char *dst = (char *) malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dst, src);
    return dst;
}

jobject JniHelper::createObject(char *classpath, char *constructorSignature, ...) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jclass myClass = env->FindClass(classpath);
    jmethodID constructorMid = env->GetMethodID(myClass, "<init>",
                                                constructorSignature);
    va_list args;
    va_start(args, constructorMid);
    jobject ret = env->functions->NewObjectV(env, myClass, constructorMid, args);
    va_end(args);

    env->DeleteLocalRef(myClass);
    return ret;
}

void JniHelper::invokeVoidMethod(jobject obj, char *methodName, char *methodSignature, ...) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jclass myClass = env->GetObjectClass(obj);
    jmethodID jmethodID1 = env->GetMethodID(myClass, methodName,
                                            methodSignature);
    va_list args;
    va_start(args, jmethodID1);
    env->functions->CallVoidMethodV(env, obj, jmethodID1, args);
    va_end(args);
    env->DeleteLocalRef(myClass);
}

void
JniHelper::invokeVoidStaticMethod(char *classpath, char *methodName, char *methodSignature, ...) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jclass myClass = env->FindClass(classpath);
    jmethodID jmethodID1 = env->GetStaticMethodID(myClass, methodName,
                                                  methodSignature);
    va_list args;
    va_start(args, jmethodID1);
    env->functions->CallStaticVoidMethodV(env, myClass, jmethodID1, args);
    va_end(args);
    env->DeleteLocalRef(myClass);
}

jfieldID JniHelper::getFieldID(jobject obj, const char *fieldName, const char *typeSignature) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jclass internalObjClass = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(internalObjClass, fieldName, typeSignature);
    env->DeleteLocalRef(internalObjClass);
    return fid;
}

jint JniHelper::getIntField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID intFid = getFieldID(obj, fieldName, Jint);
    jint intNum = env->GetIntField(obj, intFid);
    return intNum;
}

jboolean JniHelper::getBooleanField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID fid = getFieldID(obj, fieldName, Jboolean);
    jboolean jboolean1 = env->GetBooleanField(obj, fid);
    return jboolean1;
}

jstring JniHelper::getStringField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, JString);
    jobject str = env->GetObjectField(obj, strFid);
    return static_cast<jstring>(str);
}

jlong JniHelper::getLongField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jlong);
    jlong ret = env->GetLongField(obj, strFid);
    return ret;
}

jfloat JniHelper::getFloatField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jfloat);
    jfloat ret = env->GetFloatField(obj, strFid);
    return ret;
}

jdouble JniHelper::getDoubleField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jdouble);
    jdouble ret = env->GetDoubleField(obj, strFid);
    return ret;
}

jbyte JniHelper::getByteField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jbyte);
    jbyte ret = env->GetByteField(obj, strFid);
    return ret;
}

jchar JniHelper::getCharField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jchar);
    jchar ret = env->GetCharField(obj, strFid);
    return ret;
}

jshort JniHelper::getShortField(jobject obj, const char *fieldName) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jshort);
    jshort ret = env->GetShortField(obj, strFid);
    return ret;
}

jobject JniHelper::getObjectField(jobject obj, const char *fieldName, const char *classpath) {
    if (!classpath) {
        classpath = JObject;
    }
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, classpath);
    jobject ret = env->GetObjectField(obj, strFid);
    return ret;
}

jobject JniHelper::getObjectField(jobject obj, const char *fieldName) {
    return getObjectField(obj, fieldName, NULL);
}

void JniHelper::setIntField(jobject obj, const char *fieldName, jint val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jint);
    env->SetIntField(obj, strFid, val);
}

void JniHelper::setLongField(jobject obj, const char *fieldName, jlong val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jlong);
    env->SetLongField(obj, strFid, val);
}

void JniHelper::setFloatField(jobject obj, const char *fieldName, jfloat val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jfloat);
    env->SetFloatField(obj, strFid, val);
}

void JniHelper::setDoubleField(jobject obj, const char *fieldName, jdouble val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jdouble);
    env->SetDoubleField(obj, strFid, val);
}

void JniHelper::setBooleanField(jobject obj, const char *fieldName, jboolean val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jboolean);
    env->SetBooleanField(obj, strFid, val);
}

void JniHelper::setStringField(jobject obj, const char *fieldName, jstring val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, JString);
    env->SetObjectField(obj, strFid, val);
}

void JniHelper::setByteField(jobject obj, const char *fieldName, jbyte val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jbyte);
    env->SetByteField(obj, strFid, val);
}

void JniHelper::setCharField(jobject obj, const char *fieldName, jchar val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jchar);
    env->SetCharField(obj, strFid, val);
}

void JniHelper::setShortField(jobject obj, const char *fieldName, jshort val) {
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, Jshort);
    env->SetShortField(obj, strFid, val);
}

void JniHelper::setObjectField(jobject obj, const char *fieldName,
                               const char *classpath, jobject val) {
    if (!classpath) {
        classpath = JObject;
    }
    JNIEnv *env = NULL;
    this->jvm->AttachCurrentThread(&env, NULL);
    jfieldID strFid = getFieldID(obj, fieldName, classpath);
    env->SetObjectField(obj, strFid, val);
}

void JniHelper::setObjectField(jobject obj, const char *fieldName, jobject val) {
    setObjectField(obj, fieldName, NULL, val);
}

int JniHelper::handleJNILoad(JavaVM *vm, void *reserved, std::string myClassName,
                             const JNINativeMethod *methods, int methodSize) {
    JNIEnv *env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
        return -1;
    jclass myClass = env->FindClass(myClassName.data());
    if (myClass == NULL) {
        printf("cannot get class:%s\n", myClassName.data());
        return -1;
    }
    if ((env)->RegisterNatives(myClass, methods, methodSize
    ) < 0) {
        printf("register native method failed!\n");
        return -1;
    }
    LOGD_TAG("haha", "--------JNI_OnLoad-----");
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}




