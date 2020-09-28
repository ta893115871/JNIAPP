#include "common.h"

void *writeFile(void *);

static JavaVM *gvm;
static jobject gCallBackObj;
static jmethodID gCallBackMid;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    gvm = vm;
    LOG_D("JNI_OnLoad Call");
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_cb_JNIThreadCallBack_nativeCallBack(JNIEnv *env, jobject thiz,
                                                           jobject call_back) {
    // 获取java中的对象
    jclass cls = env->GetObjectClass(call_back);
    // 获取回调方法的id
    jmethodID mid = env->GetMethodID(cls, "onCall", "()V");
    // 调用java中的方法
    env->CallVoidMethod(call_back, mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_cb_JNIThreadCallBack_nativeInThreadCallBack(JNIEnv *env, jobject thiz,
                                                                   jobject call_back) {
    // 创建一个jni中的全局引用，可以在线程里面用
    gCallBackObj = env->NewGlobalRef(call_back);
    jclass cls = env->GetObjectClass(call_back);
    gCallBackMid = env->GetMethodID(cls, "onSuccess", "(Ljava/lang/String;)V");
    // 创建一个线程
    pthread_t pthread;
    jint ret = pthread_create(&pthread, nullptr, writeFile, nullptr);
    LOG_D("pthread_create ret=%d", ret);
}


/**
 * 相当于java中线程的run方法
 * @return
 */
void *writeFile(void *args) {
    // 随机字符串写入
    FILE *file;
    if ((file = fopen("/sdcard/thread_cb", "a+")) == nullptr) {
        LOG_E("fopen filed");
        return nullptr;
    }
    for (int i = 0; i < 10; ++i) {
        fprintf(file, "test %d\n", i);
    }
    fflush(file);
    fclose(file);
    LOG_D("file write done");

    // https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/invocation.html
    // 调用的话，需要JNIEnv *env
    // JNIEnv *env 无法跨越线程，只有JavaVM才能跨越线程
    // 每个原生方法的 JNIEvn 接口指针在与方法调用相关的线程中也是有效的，但是它不能被其它线程缓存或使用。
    JNIEnv * env = nullptr; // 新的env
    // 将当前native的线程附加到Java虚拟机上，返回一个属于当前线程的JNIEnv指针env
    if (gvm->AttachCurrentThread(&env, nullptr) == 0) {
        jstring jstr = env->NewStringUTF("write success");
        // 回调到java层
        env->CallVoidMethod(gCallBackObj, gCallBackMid, jstr);
        // 删除jni中全局引用
        env->DeleteGlobalRef(gCallBackObj);
        // 从Java虚拟机上分离当前native线程, 解除 附加 到 JVM 的native线程
        gvm->DetachCurrentThread();
    }
    return nullptr;
}