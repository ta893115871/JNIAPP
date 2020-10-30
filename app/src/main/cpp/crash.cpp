#include "common.h"
#include <malloc.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_bj_gxz_jniapp_crash_JNICrash_crash(JNIEnv *env, jobject thiz) {
//    int *p = static_cast<int *>(malloc(sizeof(int)));
    int *p;
    *p = 1;
    LOG_D("*P=%d", *p);
    free(p);
    p= nullptr;
}