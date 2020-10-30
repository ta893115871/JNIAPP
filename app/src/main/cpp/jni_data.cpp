//
// Created by Gu,Xiuzhong on 2020/10/30.
//

#include "common.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_data_JNIData_data(JNIEnv *env, jobject thiz, jbyte b, jchar c,
                                         jboolean j_bool,
                                         jshort s, jint i, jfloat f, jdouble d, jlong l,
                                         jfloatArray floats) {
    LOG_D("byte=%d", b);
    LOG_D("jchar=%c", c);
    LOG_D("jboolean=%d", j_bool);
    LOG_D("jshort=%d", s);
    LOG_D("jint=%d", i);
    LOG_D("jfloat=%f", f);
    LOG_D("jdouble=%lf", d);
    LOG_D("jlong=%lld", l);


    jfloat *float_p = env->GetFloatArrayElements(floats, nullptr);
    jsize size = env->GetArrayLength(floats);
    for (int index = 0; index < size; index++) {
        LOG_D("floats[%d]=%lf", index, *(float_p++));
    }
    // mode:释放模式,通常使用 0。有三种
    // 0 将内容复制回来并释放原生数组
    // JNI_COMMIT 将内容复制回来但不释放原生数组，一般用于周期性更新数组
    // JNI_ABORT 释放原生数组但不将内容复制回来
    env->ReleaseFloatArrayElements(floats, float_p, 0);
}