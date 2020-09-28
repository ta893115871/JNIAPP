//
// Created by Gu,Xiuzhong on 2020/9/23.
//
#include "common.h"

extern "C" JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_exception_JNIException_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {

    // jclass cls = env->GetObjectClass(thiz);

    // 这里我们构造一个java的对象实例，也可以GetObjectClass
    jclass cls = env->FindClass("com/bj/gxz/jniapp/exception/JNIException");
    jmethodID getStingLenMid = env->GetMethodID(cls, "getStingLen", "()I");

    jmethodID constructMid = env->GetMethodID(cls, "<init>", "()V");
    // new一个java对象
    jobject obj = env->NewObject(cls, constructMid);

    LOG_D("getStingLen start invoke");
    env->CallIntMethod(obj, getStingLenMid);
    LOG_D("getStingLen invoke done");

    // ExceptionOccurred作用和ExceptionCheck一样
    // jthrowable throwable = env->ExceptionOccurred();

    // 检查JNi调用是否发生了异常
    jboolean ret = env->ExceptionCheck();
    LOG_D("ExceptionCheck %d", ret);
    if (JNI_TRUE == ret) {
        // 打印Java层抛出的异常堆栈信息
        env->ExceptionDescribe();
        // 清除异常信息
        env->ExceptionClear();
        // ...这里可以处理异常发生逻辑，比如内存是否及合适的返回值
        return;
    }
    LOG_D("nativeInvokeJavaException exec end");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_exception_JNIException_nativeThrowException(JNIEnv *env, jobject thiz) {

    // ...这里省略业务逻辑
    jclass newExcCls = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(newExcCls, "throw exception from c++ code");

}