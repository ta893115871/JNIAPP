//
// Created by Gu,Xiuzhong on 2020/10/13.
//
#include "common.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_jnilocalRef(JNIEnv *env, jobject instance) {

    // 局部引用

    jclass local_j_cls = env->FindClass("java/lang/String");

    // 调用public String(char[] value); 构造方法
    jmethodID j_mid = env->GetMethodID(local_j_cls, "<init>", "([C)V");
    // 局部引用
    jcharArray local_j_charArr = env->NewCharArray(8);
    // 局部引用
    jstring local_str = env->NewStringUTF("LocalRef");
    const jchar *j_char = env->GetStringChars(local_str, nullptr);

    env->SetCharArrayRegion(local_j_charArr, 0, 8, j_char);

    jstring j_str = (jstring) env->NewObject(local_j_cls, j_mid, local_j_charArr);

    // 释放局部引用，也可以不用调用在方法结束后jvm会自动回收，最好有良好的编码习惯
    env->DeleteLocalRef(local_j_cls);
    env->DeleteLocalRef(local_str);
    env->DeleteLocalRef(local_j_charArr);

    // 也可以通过NewLocalRef函数创建 (*env)->NewLocalRef(env,local_ref);这个方法一般很少用。
    // 函数返回后局部引用所引用的对象会被JVM自动释放，或调用DeleteLocalRef释放。(*env)->DeleteLocalRef(env,local_ref)

    // ReleaseStringChars和GetStringChars对应
    env->ReleaseStringChars(j_str, j_char);

    return j_str;
}

static jclass g_j_cls;  // 加static前缀 只对本源文件可见，对其它源文件隐藏
extern "C" JNIEXPORT jstring JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_jniGlobalRef(JNIEnv *env, jobject instance) {

    if (g_j_cls == nullptr) {
        jclass local_j_cls = env->FindClass("java/lang/String");
        // 将local_j_cls局部引用改为全局引用
        g_j_cls = (jclass) env->NewGlobalRef(local_j_cls);
    } else {
        LOG_D("g_j_cls else");
    }

    // 调用public String(String value); 构造
    jmethodID j_mid = env->GetMethodID(g_j_cls, "<init>", "(Ljava/lang/String;)V");

    jstring str = env->NewStringUTF("GlobalRef");
    jstring j_str = (jstring) env->NewObject(g_j_cls, j_mid, str);
    return j_str;
}

extern "C" JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_delGlobalRef(JNIEnv *env, jobject instance) {
    if (g_j_cls != nullptr) {
        // 释放某个全局引用
        LOG_D("DeleteGlobalRef");
        env->DeleteGlobalRef(g_j_cls);
    }
}

static jclass g_w_j_cls;
extern "C" JNIEXPORT jstring JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_jniWeakGlobalRef(JNIEnv *env, jobject instance) {

    if (g_w_j_cls == nullptr) {
        jclass local_j_cls = env->FindClass("java/lang/String");
        // 将local_j_clss局部引用改为弱全局引用
        g_w_j_cls = (jclass) env->NewWeakGlobalRef(local_j_cls);
    } else {
        LOG_D("g_w_j_cls else");
    }

    jmethodID j_mid = env->GetMethodID(g_w_j_cls, "<init>", "(Ljava/lang/String;)V");

    // 使用弱引用时，必须先检查缓存过的弱引用是指向活动的类对象，还是指向一个已经被GC的类对象
    // 检查弱引用是否活动，即引用的比较IsSameObject
    // 如果g_w_j_cls指向的引用已经被回收，会返回JNI_TRUE
    // 如果仍然指向一个活动对象，会返回JNI_FALSE
    jboolean isGC = env->IsSameObject(g_w_j_cls, nullptr);
    if (isGC) {
        LOG_D("weak reference has been gc");
        return env->NewStringUTF("weak reference has been gc");
    } else {
        jstring str = env->NewStringUTF("WeakGlobalRef");
        jstring j_str = (jstring) env->NewObject(g_w_j_cls, j_mid, str);
        return j_str;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_delWeakGlobalRef(JNIEnv *env, jobject instance) {
    if (g_w_j_cls != nullptr) {
        // 调用DeleteWeakGlobalRef来释放它，如果不手动调用这个函数来释放所指向的对象，JVM仍会回收弱引用所指向的对象，但弱引用本身在引用表中所占的内存永远也不会被回收。
        LOG_D("DeleteWeakGlobalRef");
        env->DeleteWeakGlobalRef(g_w_j_cls);
    }
}

// 测试局部引用溢出
extern "C" JNIEXPORT void  JNICALL
Java_com_bj_gxz_jniapp_ref_JNIRef_localRefOverflow(JNIEnv *env, jobject instance) {

    // https://android.googlesource.com/platform/art/+/android-8.0.0_r36/runtime/jni_internal.cc
    // https://android.googlesource.com/platform/art/+/android-8.0.0_r36/runtime/scoped_thread_state_change-inl.h

    LOG_D("localRefOverflow start");
    for (int i = 0; i < 512; i++) {
        jclass local_j_cls = env->FindClass("java/util/ArrayList");
        // 大量的循环使用局部引用的话，如果不手动释放局部引用，很有可能造成局部引用表溢出
        env->DeleteLocalRef(local_j_cls);
    }
    LOG_D("localRefOverflow end");
}