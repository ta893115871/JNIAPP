#include "common.h"

#define  JAVA_CLASS "com/bj/gxz/jniapp/JNIMethodDynamic"

jstring getString(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF("Hello from C++");
}

jint add(JNIEnv *env, jobject thiz, jint x, jint y) {
    return x + y;
}

JNINativeMethod gMethods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) getString},
        {"sum",           "(II)I",                (void *) add}
};

jint
registerNativeMethods(JNIEnv *env, const char *clsName, JNINativeMethod *nativeMethod,
                      int numMethods) {
    jclass java_cls = env->FindClass(JAVA_CLASS);
    if (java_cls == nullptr) {
        return JNI_FALSE;
    }
    jint ret = env->RegisterNatives(java_cls, nativeMethod, numMethods);
    if (ret < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jint ret = registerNativeMethods(env, JAVA_CLASS, gMethods,
                                     sizeof(gMethods) / sizeof(JNINativeMethod));
    if (ret == JNI_FALSE) {
        return JNI_ERR;
    }
    LOG_D("JNI_OnLoad Call ret=%d", ret);
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    jclass java_cls = env->FindClass(JAVA_CLASS);
    if (java_cls != nullptr) {
        jint ret = env->UnregisterNatives(java_cls);
        LOG_D("JNI_OnUnload Call ret=%d=", ret);
    }
}


#if 0
extern "C" JNIEXPORT jstring JNICALL
Java_com_bj_gxz_jniapp_JNIMethodDynamic_stringFromJNI(
        JNIEnv *env,
        jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_bj_gxz_jniapp_JNIMethodDynamic_sum(JNIEnv *env, jobject thiz, jint x, jint y) {
    return x + y;
}
#else
#endif